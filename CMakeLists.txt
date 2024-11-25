# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ChessAI VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)


# Add the SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(chessAI src/main.cpp src/Game.cpp src/Board.cpp src/Pawn.cpp src/Piece.cpp src/Rook.cpp src/Bishop.cpp src/King.cpp src/Queen.cpp src/Knight.cpp)

# Link SFML libraries to the executable
target_link_libraries(chessAI sfml-graphics sfml-window sfml-system)
