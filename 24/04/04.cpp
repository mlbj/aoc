#include <iostream>
#include <fstream>
#include <vector> 
#include <string>

class Grid{
private:
    // contiguous block of memory
    std::vector<char> data;


public:
    int rows, cols;

    // constructor from input file containing a grid 
    Grid(const std::string& filename){
        // initialize rows and cols
        rows = 0;
        cols = 0;

        // open file
        std::ifstream file(filename);
        if (!file.is_open()){
            throw std::runtime_error("Could not open file");
        }
        
        // read char by char
        char c;
        while (file.get(c)){
            // count rows and cols
            if (c == '\n'){
                rows++;
                continue;
            }
            if (rows == 0){
                cols++;
            }

            // store the char in the data vector
            data.push_back(c); 
        }

    }

    // printer method
    void print(){
        std::cout << "rows = " << rows << std::endl;
        std::cout << "cols = " << cols << std::endl;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                std::cout << at(i, j);
            }
            std::cout << "" << std::endl;
        }
    }

    // accessor in 2d indexing
    char& at(int i, int j){
        return data[i*cols + j];
    }

    // overload operator() in 2d indexing
    char& operator()(int i, int j){
        return data[i*cols + j];
    }

    // get neighbor item
    char& neighbor(int i, int j, int di, int dj){
        if (i+di < 0 || i+di >= rows || j+dj < 0 || j+dj >= cols){
            throw std::out_of_range("Index out of range");
        }

        return at(i+di, j+dj);
    }

};

int main(){
    Grid grid("input.txt");

    // debug 
    //grid.print();

    //// part a
    // count the number of 'X' that have 'MAS' in all directions
    int counter = 0; 

    for (int i=0; i<grid.rows; i++){
        for (int j=0; j<grid.cols; j++){
            if (grid(i, j) == 'X'){
                // test all possible directions 

                // (-1,-1)
                if (i-3 >= 0 && j-3 >= 0){
                    if (grid.neighbor(i, j, -1, -1) == 'M' && grid.neighbor(i, j, -2, -2) == 'A' && grid.neighbor(i, j, -3, -3) == 'S'){
                        counter++;
                    }
                }

                // (-1,0)
                if (i-3 >= 0){
                    if (grid.neighbor(i, j, -1, 0) == 'M' && grid.neighbor(i, j, -2, 0) == 'A' && grid.neighbor(i, j, -3, 0) == 'S'){
                        counter++;
                    }
                }

                // (-1,1)
                if (i-3 >= 0 && j+3 < grid.cols){
                    if (grid.neighbor(i, j, -1, 1) == 'M' && grid.neighbor(i, j, -2, 2) == 'A' && grid.neighbor(i, j, -3, 3) == 'S'){
                        counter++;
                    }
                }

                // (0,-1)
                if (j-3 >= 0){
                    if (grid.neighbor(i, j, 0, -1) == 'M' && grid.neighbor(i, j, 0, -2) == 'A' && grid.neighbor(i, j, 0, -3) == 'S'){
                        counter++;
                    }
                }

                // (0,1)
                if (j+3 < grid.cols){
                    if (grid.neighbor(i, j, 0, 1) == 'M' && grid.neighbor(i, j, 0, 2) == 'A' && grid.neighbor(i, j, 0, 3) == 'S'){
                        counter++;
                    }
                }

                // (1,-1)
                if (i+3 < grid.rows && j-3 >= 0){
                    if (grid.neighbor(i, j, 1, -1) == 'M' && grid.neighbor(i, j, 2, -2) == 'A' && grid.neighbor(i, j, 3, -3) == 'S'){
                        counter++;
                    }
                }

                // (1,0)
                if (i+3 < grid.rows){
                    if (grid.neighbor(i, j, 1, 0) == 'M' && grid.neighbor(i, j, 2, 0) == 'A' && grid.neighbor(i, j, 3, 0) == 'S'){
                        counter++;
                    }
                }

                // (1,1)
                if (i+3 < grid.rows && j+3 < grid.cols){
                    if (grid.neighbor(i, j, 1, 1) == 'M' && grid.neighbor(i, j, 2, 2) == 'A' && grid.neighbor(i, j, 3, 3) == 'S'){
                        counter++;
                    }
                }
 
            }
        }
    }

    std::cout << "counter (part a) = " << counter << std::endl;

    //// part b
    // count ocurrences of the following patterns 
    // 
    //   M.M  M.S  S.M  S.S 
    //   .A.  .A.  .A.  .A.
    //   S.S  S.M  M.S  M.M
    // 
    counter = 0;

    for (int i=0; i<grid.rows; i++){
        for (int j=0; j<grid.cols; j++){
            if (grid(i, j) == 'A'){
                // test all directions 
                if (i-1 >= 0 && j-1 >= 0 && i+1 < grid.rows && j+1 < grid.rows){
                    // find the main diagonal pattern 
                    if ((grid.neighbor(i, j, -1, -1) == 'M' && grid.neighbor(i, j, 1, 1) == 'S') || 
                        (grid.neighbor(i, j, -1, -1) == 'S' && grid.neighbor(i, j, 1, 1) == 'M')){
                        // find the secondary diagonal pattern
                        if ((grid.neighbor(i,j, -1, 1) == 'M' && grid.neighbor(i, j, 1, -1) == 'S') || 
                            (grid.neighbor(i,j, -1, 1) == 'S' && grid.neighbor(i, j, 1, -1) == 'M')){
                            counter++;
                        }
                    }
                }
            }
        }
    }

    std::cout << "counter (part b) = " << counter << std::endl;

    return 0;
}
