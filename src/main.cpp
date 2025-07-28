#include "rubiks/game/cli_game.h"
#include "rubiks/colored_numbered_tile.h"

int main() {
	rubiks::cli_game<rubiks::colored_numbered_tile> game(3);
	game.play();
}
