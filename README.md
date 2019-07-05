# Blokus-Tile-Game

Play the popular tile game blokus!

Tiles are made up of asterisks (representing filled cells) and dots (representing empty space).

Commands:

quit - quits the game

reset - resets the game and destroys all tiles

create n - where n is any integer, creates a tile of n x n size. Enter the tile in row by row using asterisks for filled spaces and dots for empty ones. Be careful and stay within the size you entered or the program will deem the tile invalid and not create it

resize n - use this to show the current board state (board starts at 0x0) and to make the board bigger or smaller. If the board is made smaller tiles may fall off!

play (tile#) (row) (column) - each tile has an ID that will be shown to you when you create it (starting from 100). put in the tile ID, space, the row on the board you want to play it, space, the column on the board you want to play it. Make sure the board is big enough and that you aren't trying to play the tile over a previously played one, or the program will refuse to play the tile.

fliplr (tile#) - flips a tile over left to right

flipud (tile#) - flips a tile over up to down

show (tile#) - show a particular tile

show tiles - show all created tiles

rotate (tile#) - rotate a tile 90 degree counter-clockwise
