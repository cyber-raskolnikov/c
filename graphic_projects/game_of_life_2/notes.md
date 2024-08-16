# Conway's Game of Life

Picked up this project as a way to test Raylib and implement a long overdue project (never gotten around to it but wanted to implement this for some years now).

Settle for the implementation to always work on square environments

## INITIAL SCHEMA
- Initialization (have two matrices, one to keep the board state & the other one to use to calculate updates)
- Random state matrix init (0-player game!)
- LOOP over all elements
    - READ elem[i][j] state board
    - compute their next state according to their surrounding
    - store their next state in AUX matrix
- COPY aux matrix to state matrix
- PRINT MATRIX (value in each matrix slot is interpreted to alive/dead)

## BASIC RULES
- Any live cell with fewer than two live neighbours dies, as if by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.