#include <iostream>
#include <regex>
#include <string>
#include <fstream>

int main(){ 
    // input 
    std::ifstream input_file("input.txt");

    // read string from file 
    std::string input_string = "";
    if (input_file.is_open()){
        std::string line;
        while (std::getline(input_file, line)){
            input_string += line;
        }
        input_file.close();
    } else {
        std::cout << "error opening file" << std::endl;
        return 1;
    } 

    //// part a 
    int counter = 0;  

    // regex to match and capture numbers inside mul(num1,num2)
    std::regex pattern(R"(mul\((\d+),(\d+)\))");

    // Iterator to find all matches
    auto matches_begin = std::sregex_iterator(input_string.begin(), input_string.end(), pattern);
    auto matches_end = std::sregex_iterator();

    // iterate over all matches
    for (std::sregex_iterator i = matches_begin; i != matches_end; ++i){
        // it's a match! 
        std::smatch match = *i;  
        int num1 = std::stoi(match[1].str());  
        int num2 = std::stoi(match[2].str());  
        counter = counter+num1*num2;    
    }

    std::cout << "counter (part a)= " << counter << std::endl;

    //// part b
    std::regex patternb(R"((do\(\))|(don't\(\))|(mul\((\d+),(\d+)\)))");

    // iterator to find all matches
    auto matches_beginb = std::sregex_iterator(input_string.begin(), input_string.end(), patternb);
    auto matches_endb = std::sregex_iterator();

    bool enabled = true;
    counter = 0;  
    
    for (std::sregex_iterator i = matches_beginb; i != matches_endb; i++){
        // it's a match!
        std::smatch match = *i;

        // parse the match
        if (match[1].matched) {
            // "do()"
            enabled = true;
        } else if (match[2].matched) {
            // "don't()"
            enabled = false;
        } else if (enabled && match[3].matched && match[4].matched) {
            // "mul(num1,num2)" when enabled
            int num1 = std::stoi(match[4].str());
            int num2 = std::stoi(match[5].str());
        
            counter = counter + num1 * num2;
        }  
    }

    std::cout << "counter (part b) = " << counter << std::endl;

    return 0;
}