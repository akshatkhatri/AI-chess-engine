#!/bin/bash

apt-get update
apt-get install -y g++ make libstdc++6
# Compile your C++ chess engine
g++ main.cpp movement.cpp king_check.cpp chessboard.cpp legalmoves.cpp notations.cpp hashing.cpp Evaluation.cpp Search.cpp -o chess_game

# Optional: Make it executable just in case
chmod +x chess_game

pip install -r requirements.txt

export FLASK_APP=app.py
export FLASK_ENV=production  # Set to 'development' for local testing

# Run the Flask app
flask run --host=0.0.0.0 --port=$PORT
