#include <iostream>
#include <chrono>
#include "array_list.hpp"
#include "data_prepare.hpp"

int main() {
    // data_prepare::remove_nan("C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/projekt1_dane.csv", "C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/clean_data.csv");
    int sizes[] = {10000, 50000, 100000, 200000, 500000, 1000000};
    array_list<DataIn> data_list;
    // data_prepare::load_data("C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/clean_data.csv", data_list, 1000000);
    // data_list.display();
    // data_list.intro_sort(0, data_list.get_size(), 2 * std::log2(data_list.get_size()));
    // data_list.bucket_sort(10);
    std::cout<<"Testing bucket sort on different sizes of data..."<<std::endl;
    for(int size : sizes){
        data_list.clear();
        data_prepare::load_data("C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/clean_data.csv", data_list, size);
        std::cout<<"Sorting "<<data_list.get_size()<<" elements..."<<std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        data_list.bucket_sort(10);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << data_list.check_sorted() << std::endl;
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    }
    std::cout<<"Testing merge sort on different sizes of data..."<<std::endl;
    for(int size : sizes){
        data_list.clear();
        data_prepare::load_data("C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/clean_data.csv", data_list, size);
        std::cout<<"Sorting "<<data_list.get_size()<<" elements..."<<std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        data_list.merge_sort();
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << data_list.check_sorted() << std::endl;
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    }
    std::cout<<"Testing intro sort on different sizes of data..."<<std::endl;
    for(int size : sizes){
        data_list.clear();
        data_prepare::load_data("C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/clean_data.csv", data_list, size);
        std::cout<<"Sorting "<<data_list.get_size()<<" elements..."<<std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        data_list.intro_sort(0, data_list.get_size(), 2 * std::log2(data_list.get_size()));
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << data_list.check_sorted() << std::endl;
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    }
    data_list.clear();
    // std::cout << data_list.check_sorted() << std::endl;
    std::cin>> std::ws; // Czekamy na wciśnięcie klawisza Enter
    return 0;
}