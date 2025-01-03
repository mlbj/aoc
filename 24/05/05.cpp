#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>

// key -> value1, value2, ... 
// valuei must appear after the key 
std::unordered_map<int,std::vector<int>> rules;

// problem
std::vector<std::vector<int>> entries;

// parser 
void parse(const std::string& filename){
    std::ifstream infile(filename);
    if (!infile.is_open()){
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    // parse the rule book
    std::string line;
    while (std::getline(infile, line)){
        // break at empty line
        if (line.empty()){
            break;
        }

        // check if line contains |
        if (line.find('|') != std::string::npos){
            // extract substrings
            size_t delimiter_pos = line.find('|');
            std::string token_before = line.substr(0, delimiter_pos);
            std::string token_after = line.substr(delimiter_pos+1);
            
            // fill rules
            rules[stoi(token_before)].push_back(stoi(token_after));
            
        }
    }

    // parse sequences 
    while (std::getline(infile, line)){
        if (line.find(',') != std::string::npos){
            std::stringstream ss(line);
            std::string token;

            // current entry
            std::vector<int> entry;
            
            // append to current entry
            while (std::getline(ss, token, ',')){
                entry.push_back(stoi(token));
            }

            // append entry to entries
            entries.push_back(entry);
        }
    }
}


int main(){
    std::string filename = "input.txt";
    parse(filename);
    
    // sanity debug 
    // std::cout << entries.size() << std::endl;
    // std::cout << entries[0].size() << std::endl;
    
    //// part a. 
    int sum = 0;

    std::vector<int> valid_entries;
    for (int i=0; i<entries.size(); i++){
        std::vector<int> entry = entries[i];
        bool valid_entry = true;
        for (int j=entry.size()-1; j>=0; j--){
            
            // check if key exists
            if (rules.find(entry[j]) != rules.end()){
                // comparison position 
                int k=j-1;
                while (k>=0 && valid_entry){
                    for (int value : rules[entry[j]]){
                        if (entry[k]==value){
                            valid_entry = false;
                            break;
                        }
                    }
                    k--;
                }      
            }

            if (!valid_entry){
                break;
            }
        }

        // if correct, add to the correct list 
        if (valid_entry){
            valid_entries.push_back(i);
        }

    }   

    // get middle elements 
    for (int i=0; i<valid_entries.size(); i++){
        const std::vector<int> current_entry = entries[valid_entries[i]];
        sum = sum + current_entry[(int) current_entry.size()/2]; 
    }

    // print output 
    std::cout << sum << std::endl;


    //// part b. 
    std::vector<int> incorrect order;

    // at main break: break loop, swap and start over.

    
    return 0;
}
