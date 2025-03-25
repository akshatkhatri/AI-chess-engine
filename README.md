# Chess Game

A console-based chess game implemented in C++.

## How to Run

1. Clone the repository.
2. Compile the C++ files:
   ```bash
   g++ main.cpp movement.cpp king_check.cpp chessboard.cpp legalmoves.cpp notations.cpp -o chess_game
   ```
3. Run the executable:
   ```bash
   ./chess_game
   ```

## Files

- `main.cpp`: Main entry point of the game.
- `movement.cpp`: Logic for moving the pieces and validating moves.
- `king_check.cpp`: Functions related to checking the king's status.
- `chessboard.cpp`: Display and manage the chessboard.

## Pending Updates

- AI engine enabling AI V/s AI or player V/s AI
- Frontend UI using JS

## License
MIT License
