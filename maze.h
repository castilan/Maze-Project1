//
// Created by Angelina Castillo on 2/3/20.
//

#ifndef UNTITLED_MAZE_H
#define UNTITLED_MAZE_H

#endif //UNTITLED_MAZE_H

#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>

class Maze{
public:
    Maze(std::string inputFileName);
    int path_idx(std::tuple<int, int> c);
    std::vector<std::tuple<int, int>> solved_path();
    void print_solved_path(std::vector<std::tuple<int, int>> path);//takes a solved path vector and prints the maze
                                                                    // with the solved path shown with whitespace
    ~Maze();

private:
    std::vector<std::tuple<int, int>> cells;//represents all of the cells<row number, column number>
    std::vector<std::tuple<int, int>> path_cell;//holds all of the path cells
    std::vector<bool> used;//labels path cells in path_cell false if not used and true if already used

    std::tuple<int, int> start;
    std::tuple<int, int> end;

    std::vector<std::string> maze;//string of the maze
    int num_row;
    int num_column;
    int size;

    int is_adjacent_to(std::tuple<int, int> cell, int idx);



};
