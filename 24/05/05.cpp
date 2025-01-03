#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>

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

// complement of a vector of numbers for 0 to n-1, selected with no repetition
std::vector<int> get_complement(const std::vector<int>& input, int n){
    // fill full sequence with numbers 0, 1, ..., n-1
    std::vector<int> full_sequence(n);
    std::iota(full_sequence.begin(), full_sequence.end(), 0);

    // sort input vector
    std::vector<int> sorted_input = input;
    std::sort(sorted_input.begin(), sorted_input.end());

    // get complement with std::set_difference
    std::vector<int> complement;
    std::set_difference(
        full_sequence.begin(), 
        full_sequence.end(),
        sorted_input.begin(),
        sorted_input.end(),
        std::back_inserter(complement)
    );

    return complement;
}


int main(){
    std::string filename = "input.txt";
    parse(filename);
    
    //// part a
    int sum = 0;

    std::vector<int> valid_entries_idx;
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
            valid_entries_idx.push_back(i);
        }

    }   

    // get middle elements 
    for (int i=0; i<valid_entries_idx.size(); i++){
        const std::vector<int> current_entry = entries[valid_entries_idx[i]];
        sum = sum + current_entry[(int) current_entry.size()/2]; 
    }

    // print output 
    std::cout << "sum (part a) = " << sum << std::endl;


    //// part b  
    std::vector<int> invalid_entries_idx = get_complement(valid_entries_idx, entries.size());

    for (int i=0; i<invalid_entries_idx.size(); i++){ 
        std::vector<int> entry = entries[invalid_entries_idx[i]];

        // we will pretend that the entry is valid. however we know that it is not
        // the idea is that we will break and swap the positions k 
        // and j when we find a rule breaking point. at that point, we will decrement 
        // i and start over.
        bool valid_entry = true;
        for (int j=entry.size()-1; j>=0; j--){
            
            // check if key exists
            if (rules.find(entry[j]) != rules.end()){
                // comparison position 
                int k = j-1;
                while (k>=0 && valid_entry){
                    for (int value : rules[entry[j]]){
                        if (entry[k]==value){
                            // swap i and j elements
                            int swap = entry[k];
                            entries[invalid_entries_idx[i]][k] = entries[invalid_entries_idx[i]][j];
                            entries[invalid_entries_idx[i]][j] = swap; 

                            // decrement i idx
                            i--;

                            // force the loop to break 
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
    }   

    // get middle elements of invalid entries
    sum = 0;
    for (int i=0; i<invalid_entries_idx.size(); i++){
        const std::vector<int> current_entry = entries[invalid_entries_idx[i]];
        sum = sum + current_entry[(int) current_entry.size()/2]; 
    }

    // print output 
    std::cout << "sum (part b) = " << sum << std::endl;
    
    return 0;
}
