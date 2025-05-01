# AI Chess Engine

A C++ chess engine under development with support for full chess rules and an AI opponent. It implements move generation, position evaluation, and a minimax search with alpha-beta pruning to choose the best moves. This project is designed to be modular and extensible, making it easy for developers to understand and contribute to each component (board representation, move logic, search, etc.).

## 🎮 Watch Gameplay Demo(Click on the image)

[![Watch Gameplay](https://img.youtube.com/vi/n73XXekQ-fY/0.jpg)](https://youtu.be/n73XXekQ-fY)


## Key Features

- **Legal Move Generation:** Enumerates all legal chess moves for each piece, including special rules (castling, en passant, pawn promotion, etc.). For example, the engine generates pawn promotions by appending promotion designators like “QP”, “RP”, etc. when a pawn reaches the last rank. This ensures the move generator covers cases like promoting to Queen, Rook, Bishop, or Knight.

- **Static Evaluation Function:** Assigns a numerical score to a board position based on material and piece placement. Standard piece values are used (Pawn=100, Knight=320, Bishop=330, Rook=500, Queen=900), along with piece-square tables for finer positional nuance. The evaluation can be extended or tuned by adjusting values in `Evaluation.cpp` (e.g., piece-square tables and game-phase tables for midgame/endgame).

- **Minimax Search with Alpha-Beta Pruning:** Implements a depth-limited minimax algorithm to explore possible move sequences. Alpha-beta pruning is used to eliminate branches that cannot influence the final decision, speeding up the search. At depth 0 or when a checkmate/stalemate is detected, the search returns the static evaluation of the position. The search driver (`minimax_driver` in `Search.cpp`) orchestrates the turn-taking between the AI and opponent, ultimately choosing the best move for the AI.

- **Game State Detection:** Includes routines to detect check, checkmate, and stalemate via the `king_check` module. These are used to terminate the search (e.g., returning evaluation on checkmate) and to validate that moves do not leave the king in check. This ensures the AI makes only legal moves and can play a complete game according to standard chess rules.

- **UCI Protocol Support:** The engine can act as a UCI-compatible AI agent. It reads commands like `uci`, `isready`, `position`, and `go` from standard input, and outputs engine information (e.g., `id name`) and the best move in UCI format (`bestmove ...`). This allows integration with graphical interfaces or other tools that support UCI. In practice, sending `go` triggers a search (at a fixed depth by default) and the engine responds with its chosen move.

- **Zobrist Hashing (Planned/Implemented):** The code includes Zobrist hashing utilities (`hashing.cpp/h`), generating random hash keys for pieces, castling rights, en passant, and side-to-move. This prepares the engine for future transposition table integration to cache positions for faster search. (Currently, this is set up but not used in a full transposition table.)

- **Move Notation & Utilities:** Helper functions in `notations.cpp` convert between coordinate systems and UCI strings, facilitating input/output. The engine can parse moves like “e2e4” into board indices or vice versa. It also provides a basic text-based board display and welcoming message for console play.

- **Perft Testing (Validation):** The engine includes functions to run perft tests (depth-limited node counts) and comes with a perft suite (`perftsuite.epd`) and example results (`perft_results.txt`). These are used to verify that move generation is correct by comparing node counts to known good values.

## Build and Run

### Prerequisites

- A C++ compiler (e.g. **g++**) supporting C++11 or later.
- Standard C++ libraries (no external dependencies beyond the C++ Standard Library).

### Compilation

Clone the repository and compile the source files into an executable. For example, using g++:

```sh
git clone https://github.com/akshatkhatri/AI-chess-engine.git
cd AI-chess-engine
g++ -std=c++11 main.cpp movement.cpp king_check.cpp chessboard.cpp \
    legalmoves.cpp notations.cpp hashing.cpp Evaluation.cpp Search.cpp \
    -o chess_engine
```

This produces an executable (here named `chess_engine`). You can enable optimizations (e.g. `-O2`) for better search speed.

### Running the Engine

Run the compiled program from a terminal. By default, the engine waits for UCI commands on standard input. A typical usage sequence is:

1. Start the engine:
   ```
   ./chess_engine
   ```

2. Type `uci` and press Enter. The engine will identify itself (e.g. `id name MyCoolBot`) and respond `uciok`.

3. Type `isready` to ensure the engine is ready (`readyok` response).

4. Set up a position with `position startpos` (for the standard chess start) or using a FEN string with `position fen ...`.

5. Finally, type `go` to let the engine think. It will compute the best move at the preset search depth and output it as `bestmove e2e4` (for example).

*For Player vs Player (console) mode:* Uncomment the call to `start_game(chess_board, chess_pieces,'W');` in `main.cpp` (see comments around line 1020). This will enable a simple console loop where two players can enter moves in `row,col` format (0–7 indexing).

## Architecture & Module Design

The source code is organized into clear modules:

- **`chessboard.cpp/h`**: Manages the board data structure (an 8×8 `vector<vector<char>>`) and displays it. Also includes console UI (welcome message, instructions).
- **`movement.cpp/h`**: Contains the rules for how each piece moves without considering checks. For instance, it checks for clear paths of bishops/rooks/queens and legal knight jumps. It reports whether a given move is physically legal on the board.
- **`legalmoves.cpp/h`**: Builds on `movement` to generate all **legal** moves for a side. It iterates over pieces, generates candidate moves, and filters out those that would leave the king in check (using `king_check` functions). This produces a list of legal moves for use in the search.
- **`king_check.cpp/h`**: Implements check, checkmate, and stalemate detection. It includes functions to see if a king is under attack and whether any legal moves remain, which is used to detect game termination conditions.
- **`notations.cpp/h`**: Handles conversion between internal coordinate notation and standard chess notation (UCI strings). For example, it translates `"7,2"` coordinates to `"b1"` or `"b1"` to `"7,2"`.
- **`Evaluation.cpp/h`**: Defines the static evaluation of positions. It assigns values to pieces, applies piece-square tables (different values by square), and calculates a final score from White’s perspective. The engine assumes higher scores favor White, and the minimax search uses this score to choose moves.
- **`Search.cpp/h`**: Implements the AI search. Key functions are `minimax_driver` (sets up the search with a given depth) and `minimax` (the recursive alpha-beta search). These traverse the game tree, call move generators, apply moves on the board, and use the evaluator at leaf nodes or terminal positions.
- **`hashing.cpp/h`**: Implements Zobrist hashing functions. It generates random 64-bit keys for board pieces, castling rights, en passant squares, and side-to-move. The function `generate_hash_for_position` can compute a unique hash for any board state, laying groundwork for caching positions (transposition table) in future versions.
- **Other files:**
  - `main.cpp` contains the entry point. It initializes the board, piece mappings, and handles input/output loop (console and UCI commands).
  - `first_game.pgn` is an example PGN file.
  - `perft_*` files store test results for performance testing of move generation.

## Future Improvements

- **Enhanced AI:** Current depth is fixed and relatively shallow. Future versions could add iterative deepening, time control, or a more advanced evaluation (e.g. endgame tables).
- **Transposition Table:** With Zobrist hashing in place, implementing a transposition table would greatly speed up repeated position lookups during search.
- **Opening Book / Endgame Tablebases:** Incorporating opening move databases or endgame databases would improve play strength.
- **Graphical Interface / Frontend:** A GUI (possibly in another language) could be added for easier play. The code’s UCI support already allows use with external GUIs.
- **Move Ordering and Pruning Heuristics:** Improve move ordering (e.g. try captures first) and implement pruning heuristics (like null-move pruning) for performance.
- **Bug Fixes & Testing:** Continued testing (using perft tests and other means) to ensure correctness under all rule variants (castling rights, en-passant, promotions, etc.).
- **Performance:** As-is, the engine can handle a few plies quickly; deeper searches will be slower. Optimization (compiler flags, algorithmic improvements) can enhance speed.

The engine is released under the MIT License and welcomes contributions. See the [LICENSE](https://github.com/akshatkhatri/AI-chess-engine/blob/main/README.md) file for details.

