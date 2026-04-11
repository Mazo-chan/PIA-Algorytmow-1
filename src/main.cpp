#include <iostream>
#include "array_list.hpp"
#include "data_prepare.hpp"

int main() {
    // data_prepare::remove_nan("C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/projekt1_dane.csv", "C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/clean_data.csv");
    int sizes[] = {10000, 100000, 500000, 1000000};
    array_list<DataIn> data_list;
    data_prepare::load_data("C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/clean_data.csv", data_list, 100000);
    // data_list.display();
    data_list.heap_sort();
    std::cout << data_list.check_sorted() << std::endl;
    std::cin>> std::ws; // Czekamy na wciśnięcie klawisza Enter
    return 0;
}