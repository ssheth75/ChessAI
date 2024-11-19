# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ChessAI VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(chessAI main.cpp Game.cpp Board.cpp Pawn.cpp Piece.cpp Rook.cpp Bishop.cpp King.cpp Queen.cpp Knight.cpp)

# Link SFML libraries to the executable
target_link_libraries(chessAI sfml-graphics sfml-window sfml-system)
