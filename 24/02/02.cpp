#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

int main(){
    const int size = 1000;
    std::vector<int> reports[size]; 
    std::ifstream input_file("input.txt");

    // input 
    if (!input_file.is_open()){
        std::cout << "error opening file" << std::endl;
        return 1;
    }
     
    std::string line;
    int index=0;
    while (std::getline(input_file, line)){
        std::istringstream iss(line);
        int value;
        while (iss >> value){
            reports[index].push_back(value);
        }
        index++;
    }
    input_file.close();

    //// part a
    int n_safe=0;

    for (int i=0; i<size; i++){ 
        bool increasing = true;
        bool decreasing = true;
        int max_abs_diff = 0;

        for (int j=0; j<reports[i].size()-1; j++){
            if (reports[i][j+1] - reports[i][j] >= 0){
                decreasing = false;
            }
            if (reports[i][j+1] - reports[i][j] <= 0){
                increasing = false;
            }
            
            // compute the maximum absolute difference
            max_abs_diff = std::max(max_abs_diff, std::abs(reports[i][j+1] - reports[i][j]));
        }
        if ((increasing || decreasing) && max_abs_diff <= 3 && max_abs_diff >= 1){
            n_safe++;
        } 
    }

    std::cout << "n_safe (part a)= " << n_safe << std::endl;


    //// part b
    n_safe=0;

    for (int i=0; i<size; i++){ 
        bool increasing = true;
        bool decreasing = true;
        int max_abs_diff = 0;
        bool is_safe = true;

        // check if it is safe
        for (int j=0; j<reports[i].size()-1; j++){
            if (reports[i][j+1] - reports[i][j] >= 0){
                decreasing = false;
            }
            if (reports[i][j+1] - reports[i][j] <= 0){
                increasing = false;
            }
            
            // compute the maximum absolute difference
            max_abs_diff = std::max(max_abs_diff, std::abs(reports[i][j+1] - reports[i][j]));
        }
        if ((increasing || decreasing) && max_abs_diff <= 3 && max_abs_diff >= 1){
            n_safe++;
        }else{
            // brute force remove one element and check if it is safe again
            for (int j=0; j<reports[i].size(); j++){
                std::vector<int> temp = reports[i];
                temp.erase(temp.begin() + j);
                increasing = true;
                decreasing = true;
                max_abs_diff = 0;
                for (int k=0; k<temp.size()-1; k++){
                    if (temp[k+1] - temp[k] >= 0){
                        decreasing = false;
                    }
                    if (temp[k+1] - temp[k] <= 0){
                        increasing = false;
                    }
                    max_abs_diff = std::max(max_abs_diff, std::abs(temp[k+1] - temp[k]));
                }
                if ((increasing || decreasing) && max_abs_diff <= 3 && max_abs_diff >= 1){
                    n_safe++;
                    break;
                }
            }
        }


    }

    std::cout << "n_safe (part b) = " << n_safe << std::endl;


    return 0;
}