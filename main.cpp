//
//Angelina Castillo
//project 1

#include <iostream>
#include <tuple>
#include "maze.h"

int main(int argc, char *argv[]) {
    if(argc != 2){
        std::cout << "usage:" <<argv[0] << "nameOfInputFile\n";
        exit(2);
    }

    Maze maze(argv[1]); //argument is input_maze.txt
    std::vector<std::tuple<int, int>> path = maze.solved_path();
    maze.print_solved_path(path);

    return 0;
}
