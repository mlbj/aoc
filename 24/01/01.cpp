#include <iostream>
#include <algorithm>
#include <fstream>
#include <unordered_map>

int main(){
    const int size = 1000;
    int arr1[size], arr2[size];
    std::ifstream input_file("input.txt");

    // input 
    if (!input_file.is_open()){
        std::cout << "error opening file" << std::endl;
        return 1;
    }
    for (int i=0; i<size; i++){
        input_file >> arr1[i] >> arr2[i];
    }
    input_file.close();

    //// part a 
    int sum=0;

    // sort both arrays in ascending order 
    std::sort(arr1, arr1+size);
    std::sort(arr2, arr2+size);

    // subtract, take the absolute value and reduce
    for (int i=0; i<size; i++){
        sum = sum + std::abs(arr1[i] - arr2[i]);
    }

    std::cout << "sum (part a) = " << sum << std::endl;

    //// part b
    sum=0;
    std::unordered_map<int, int> map;

    // count the frequency of each element in arr1
    for (int i=0; i<size; i++){
        map[arr2[i]]++;
    }

    // compute the norm
    for (int i=0; i<size; i++){
        sum += arr1[i]*map[arr1[i]];
    }

    // output
    std::cout << "sum (part b) = " << sum << std::endl;

    return 0;
}