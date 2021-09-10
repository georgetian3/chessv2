#include "ability.hpp"
#include "piece.hpp"

void Ability::perform(Piece *piece) {
    piece->setStat(stat_, amount_);
}
