# Chess Game

A Chess Engine Under Development in C++, with plans to develop an AI-powered opponent.

## How to Run

1. Clone the repository.
2. Compile the C++ files:
   ```bash
   g++ main.cpp movement.cpp king_check.cpp chessboard.cpp legalmoves.cpp notations.cpp hashing.cpp Evaluation.cpp Search.cpp -o chess_game
   ```
3. Run the executable:
   ```bash
   ./chess_game
   ```

## Files

- **main.cpp** – Main entry point of the game, handling user input and game flow.
- **movement.cpp** – Implements logic for piece movement and move validation.
- **king_check.cpp** – Contains functions for detecting check, checkmate, and stalemate.
- **chessboard.cpp** – Manages board representation, piece placement, and display.
- **legalmoves.cpp** – Generates all possible legal moves for each piece.
- **notations.cpp** – Handles chess move notation conversion (e.g., algebraic notation).
- **hashing.cpp** - Implements Zobrish Hashing For Efficient Lookups
- **perft_results.txt** – Stores results of performance tests for move generation.
- **perftsuite.epd** – Test suite of chess positions for verifying move generation accuracy.


## Pending Updates

- AI engine enabling AI V/s AI or player V/s AI
- Frontend UI using JS

## License
MIT License
