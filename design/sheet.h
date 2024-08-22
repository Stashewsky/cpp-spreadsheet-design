#pragma once

#include "cell.h"
#include "common.h"

#include <functional>

class Sheet : public SheetInterface {
public:
    ~Sheet();

    void SetCell(Position pos, std::string text) override;

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;

    bool IsPositionInSheet(Position pos) const;
    // Можете дополнить ваш класс нужными полями и методами

private:
    // Можете дополнить ваш класс нужными полями и методами
    std::unordered_map<Position, std::unique_ptr<Cell>> sheet_;

};