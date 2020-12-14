//
// Created by Angelina Castillo on 2/3/20.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include "maze.h"
#include <tuple>

Maze::Maze(std::string inputFileName){
    std::ifstream inFile;
    inFile.open(inputFileName);
    std::string m;

    if(!inFile){
        std::cout<<"could not open file";
        exit(1);
    }

    while(inFile >> m){
        maze.push_back(m); // inputs input_maze.txt line by line into maze
        //std::cout<<m<<std::endl;//prints the maze without the solution. uncomment if you wish to see this.
    }
    num_row = maze.size(); //number of lines in the input file
    num_column = maze.at(num_row-1).length(); // measures number of cells in a single row

    for(int i = 0; i<num_row; i++){
        std::string s = maze.at(i);

        for(int j = 0; j<num_column; j++){
            cells.push_back(std::make_tuple(i, j));//populating cells with all coordinates

            if(s[j]=='0'){
                used.emplace_back(false);
                path_cell.push_back(std::make_tuple(i, j));//populating path_cell with only cells that are paths

                if(j == num_column-1 or i == num_row-1){
                    end = std::make_tuple(i, j);}//finding/populating end cell

                else if(j == 0 or i==0){
                    start = std::make_tuple(i, j);}//finding/populating start cell
            }
        }
    }
    size = num_column*num_row;
    inFile.close();

}
Maze::~Maze() {}



int Maze::path_idx(std::tuple<int, int> c) {
    for (int i = 0; i<path_cell.size();i++){
        if(c == path_cell.at(i)){return i;}
    }
    return path_cell.size();
}

int Maze::is_adjacent_to(std::tuple<int, int> cell, int idx) {
    int adjacent_idx = size;

    int c_row = std::get<0>(cell);
    int c_column = std::get<1>(cell);

    for(int i=idx;i<path_cell.size();i++){
        int row = std::get<0>(path_cell[i]);
        int column = std::get<1>(path_cell[i]);

        if(c_row == row and (c_column == column+1 or c_column == column-1)){
            adjacent_idx = i;
            return adjacent_idx;
        }
        else if(c_column == column and (c_row == row+1 or c_row == row-1)){
            adjacent_idx = i;
            return adjacent_idx;
        }

    }
    return adjacent_idx;
}

std::vector<std::tuple<int, int>> Maze::solved_path() {
    std::vector<std::tuple<int, int>> path;

    path.emplace_back(start);
    used[path_idx(start)] = true;
    int from_idx = 0;
    while(!path.empty()){
        int adjacent_idx = is_adjacent_to(path.back(), from_idx);
        if(adjacent_idx==size){
            from_idx=path_idx(path.back())+1;
            path.pop_back();
        }
        else if(used[adjacent_idx]){
            from_idx = adjacent_idx+1;
        }
        else if(!used[adjacent_idx]){
            path.emplace_back(path_cell.at(adjacent_idx));
            used[adjacent_idx] = true;
            from_idx = 0;
            if(path_cell[adjacent_idx]==end){break;}

        }

    }
    if(path.empty()){
        std::cout<<"There is no path in this maze"<<std::endl;
    }
    ///vvvshow the path with row and column numbers the cout shows the coordinates as (row, column)
    /*for(auto & i : path){
        std::cout << "("<<std::get<0>(i)<<", "<<std::get<1>(i)<<")"<<std::endl;

    }*/
    return path;
}

void Maze::print_solved_path(std::vector<std::tuple<int, int>> path){
    for(auto & i : path){
        int ro = std::get<0>(i);
        int colm = std::get<1>(i);
        maze[ro][colm]=' ';
    }
    for(const auto & i : maze){
        std::cout<<i<<std::endl;
    }
}


