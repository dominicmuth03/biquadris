#include "abstractboard.h"

AbstractBoard::AbstractBoard(std::unique_ptr<AbstractBoard> component) noexcept : component{move(component)} {}

AbstractBoard::~AbstractBoard() noexcept {}
