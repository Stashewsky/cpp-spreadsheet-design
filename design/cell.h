#pragma once

#include "common.h"
#include "formula.h"
#include <set>

class Cell : public CellInterface {
public:
    Cell();
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

private:
    SheetInterface& sheet_;
    std::set<Cell*> ref_cells_;
    std::set<Cell*> depend_cells_;
    mutable std::optional<Value> cache_;

    void InvalidateCache();
    void RefreshCells();

    class Impl{
    public:
        virtual Value GetValue() const = 0;
        virtual std::string GetText() const = 0;
        virtual std::vector<Position> GetRefCells() const = 0;
        ~Impl() = default;
    };

    class EmptyImpl : public Impl{
    public:
        Value GetValue() const override;
        std::string GetText() const override;
    };

    class TextImpl : public Impl{
    public:
        TextImpl(std::string text);
        Value GetValue() const override;
        std::string GetText() const override;
    private:
        std::string text_;
    };

    class FormulaImpl : public Impl{
    public:
        FormulaImpl(std::string formula, const SheetInterface& sheet);
        Value GetValue() const override;
        std::string GetText() const override;
        std::vector<Position> GetRefCells() const override;
    private:
        std::unique_ptr<FormulaInterface> formula_;
    };

    std::unique_ptr<Impl> impl_;
    bool HasCircularDependency(Impl& impl);
};