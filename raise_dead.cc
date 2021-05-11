#include "raise_dead.h"
#include "board.h"

RaiseDead::RaiseDead():
        Spell{"Raise Dead", 1, 
             "Resurrect the top minion in your graveyard and set its defence to 1"} {}

void RaiseDead::cast(Board *b, playernum whoplayer) {
        try {
                b->pop_graveyards(whoplayer);
        } catch(Graveyard_empty &e) {
                throw CannotCast{"Cannot cast Rase Dead: the graveyard is empty. "};
        } catch(No_space &e) {
                throw CannotCast{"Cannot cast Raise Dead, since the board is full."};
        }
}
