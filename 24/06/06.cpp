    #include <iostream>
    #include <vector>
    #include <string>
    #include <fstream>


    class Grid{
    private:
        // contiguous block of memory
        std::vector<char> data;
        
    public:
        int rows, cols;
        int row, col;  
        int move_counter=0; 

    Grid(const Grid& other)
        : data(other.data),
        rows(other.rows),
        cols(other.cols),
        row(other.row),
        col(other.col),
        move_counter(other.move_counter) {}   
        
        // constructor from the shape and a single string 
        Grid(int rows, int cols, const std::string& input):
            rows(rows), cols(cols){
            // check if input makes sense
            
            //reserve memory for data
            data.resize(rows*cols, 0);
            
            for (int index=0; index<rows*cols; index++){
                // unpack positions 
                int j = index % cols;
                int i = (int) index/cols;
                
                // copy input char to grid 
                at(i, j) = input[index];
                
                // Get cursor position
                if (at(i, j) == '^' || at(i, j) == '>' || at(i, j) == 'v' || at(i, j) == '<') {
                    row = i;
                    col = j; 
                }
            }
            
        }
            
        // constructor from a vector of strings 
        Grid(const std::vector<std::string>& input){
            // check if input rows make sense
            
            rows = input.size();
            cols = input[0].length();
            
            // reserve memory for data
            data.resize(rows*cols, 0);
            
            for (int i=0; i<rows; i++){
                for (int j=0; j<cols; j++){ 
        
                    // Copy input char to grid
                    at(i, j) = input[i][j];
                    
                    // Get cursor position
                    if (at(i, j) == '^' || at(i, j) == '>' || at(i, j) == 'v' || at(i, j) == '<') {
                        row = i;
                        col = j; 
                    }
                }
            }
        }
         
        // rot90 method
        void rot90(){
            switch(at(row, col)){ 
                case '<':
                    at(row, col) = '^'; 
                    break;
                case '^':
                    at(row, col) = '>'; 
                    break;
                case '>':
                    at(row, col) = 'v'; 
                    break;
                case 'v':
                    at(row, col) = '<'; 
                    break;
            } 
        }
        
        // printer method  
        void print(){
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    std::cout << at(i, j);
                }
                std::cout << " " << std::endl;
            }
        }
        
        // validate position method
        bool valid_pos(int i, int j){
            return i>=0 && i<=rows-1 && j>=0 && j<=cols-1;
        }

        // forward method. Returns false if the cursor is out of limits, or 
        // true if the cursor is still within the limits.
        bool forward(){ 
            while(true){
                int next_row = row;
                int next_col = col;

                // determine the next position based on the current direction
                switch (at(row, col)){
                    case '<':
                        next_col = col - 1;
                        break;
                    case '^':
                        next_row = row - 1;
                        break;
                    case '>':
                        next_col = col + 1;
                        break;
                    case 'v':
                        next_row = row + 1;
                        break;
                }

                // handle out of limits 
                if (valid_pos(next_row, next_col)){

                    // handle blocks ('#')  
                    if (at(next_row, next_col) == '#'){ 
                        rot90(); 
                    // handle free path 
                    }else{
                        // increment the move_counter only 
                        // if a new position was found
                        if (at(next_row, next_col)=='.'){     
                            move_counter++; 
                        }

                        // mark the path with the cursor
                        at(next_row, next_col) = at(row, col);

                        // update the cursor position
                        row = next_row;
                        col = next_col;
                        
                        return true;
                    }
                }else{
                    // update the counter anyways
                    move_counter++;
                    return false;
                }
            }
        }
            
        // accessor in 2d indexing
        char& at(int i, int j){
            if (i >= rows || j >= cols){
                throw std::out_of_range("Index out of range");
            }
            return data[i*cols + j];
        }
        
        // overload operator() in 2d indexing
        char& operator()(int i, int j){
            return data[i*cols + j];
        }

        // overload operator= for deep copy assignment
        Grid& operator=(const Grid& other) {
            if (this != &other) {  
                // deep copy the data from `other` to this instance
                data = other.data;
                rows = other.rows;
                cols = other.cols;
                row = other.row;
                col = other.col;
                move_counter = other.move_counter;
            }
            return *this;
        }
    };

    int main(){ 
        // Input grid as a vector of strings
        // std::vector<std::string> input = {
        //     "....#.....",
        //     ".........#",
        //     "..........",
        //     "..#.......",
        //     ".......#..",
        //     "..........",
        //     ".#..^.....",
        //     "........#.",
        //     "#.........",
        //     "......#...",
        // };     

        //  std::vector<std::string> input = {
        //     "..#..",
        //     ".>..#",
        //     ".#...",
        //     "...#."};
        
        
        //read input from file	
        std::string filename = "input.txt";
        std::ifstream file(filename);

        std::vector<std::string> input;
        std::string line;
        while (std::getline(file, line)){
            input.push_back(line);
        }
        file.close();
        
        //// part a
        // cast grid object
        Grid grida(input);
        
        // brute force
        while (grida.forward()){}
        std::cout << "grid.move_counter = " << grida.move_counter << std::endl;

        //// part b
        // cast grid object
        Grid grid(input);
       
        std::vector<bool> placed;
        placed.resize(grid.rows*grid.cols, false);
        int how_many=0;
        Grid cgrid = Grid(grid); 

        // brute force
        for (int i=0; i<grid.rows; i++){
            for (int j=0; j<grid.cols; j++){
                // skip if the cell is not empty
                if (cgrid(i,j) != '.'){
                    continue;
                }

                // skip if the cell was already placed
                if (placed[i*grid.cols + j]){
                    continue;
                } 

                // place the block and count the find a loop
                cgrid(i,j) = '#';
                int counter = 0;
                while(cgrid.forward()){
                    if (counter>4*grid.rows*grid.cols){
                        placed[i*grid.cols + j] = true;
                        how_many++;
                        break;
                    }else{
                        counter++;
                    }
                }

                cgrid = Grid(grid);
            }
        }

        std::cout << "how_many = " << how_many << std::endl;
        
        return 0;
    }