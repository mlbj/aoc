#include <iostream>
#include <stack>
#include <vector>
#include <utility>


int main(){
    int niter = 75;
    std::stack<std::pair<unsigned long, int>> pq;

    pq.push({5910927, 0});
    pq.push({0, 0});
    pq.push({1, 0});
    pq.push({47, 0});
    pq.push({261223, 0});
    pq.push({94788, 0});
    pq.push({545, 0});
    pq.push({7771, 0});

    unsigned long counter = 8;

    while(!pq.empty()){
        auto [value, level] = pq.top();
        pq.pop();
        if (level<niter){
            if (value == 0){
                value = 1;
                pq.push({value, level+1});
            }else if (std::to_string(value).size()%2 == 0){
                std::string value_str = std::to_string(value);
                value = std::stoull(value_str.substr(0, value_str.size()/2));
                unsigned long value_second = std::stoull(value_str.substr(value_str.size()/2, value_str.size()));
                pq.push({value_second, level+1});
                pq.push({value, level+1});
                counter++;
            }else{
                value = value*2024;
                pq.push({value, level+1});
            }
        }

        
    }

    std::cout << counter << std::endl; 
}