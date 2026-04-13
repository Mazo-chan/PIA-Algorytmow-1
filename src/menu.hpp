#pragma once
#include "array_list.hpp"
#include "data_prepare.hpp"
#include <iostream>
#include <chrono>

class menu{
private:
    int _points;
    std::string _dataset_name;
    array_list<DataIn> data_list;
public:
    menu() : _points(100000), _dataset_name("C:/Users/jakla/Documents/GitHub/PIA-Algorytmow-1/data/projekt1_dane.csv") {}
    void display_menu(){
        std::cout << "1. Choose Benchmark parameters.\n";
        std::cout << "2. Generate/Rebuild Dataset.\n";
        std::cout << "3. Manual Mode\n";
        std::cout << "0. Exit\n";
    }
    
    void generate_dataset(){
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "Generating/Rebuilding dataset 'clean_data.csv' from '" << _dataset_name
            << "'...\n";
        data_prepare::remove_nan(_dataset_name, "./clean_data.csv");
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Dataset generated in " << duration.count() << " milliseconds.\n";
    }
    void parameters(){
        std::cout << "Enter number of records: ";
        std::cin >> _points;
        std::cout << "Choose dataset:\n";
        std::cin >> _dataset_name;
        }
    void manual_mode(){
        int choice;
        std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
        std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        while(true){
            std::cout << "Manual Mode - Choose an operation:\n";
            std::cout << "1. Load dataset\n";
            std::cout << "2. Merge sort\n";
            std::cout << "3. Bucket sort\n";
            std::cout << "4. Intro sort\n";
            std::cout << "5. Display list\n";
            std::cout << "6. Check if sorted\n";
            std::cout << "7. Clear list\n";
            std::cout << "0. Exit Manual Mode\n";
            std::cin >> choice;
            if(choice == 0) break;
            switch (choice) {
                case 1:
                    std::cout << "Loading dataset...\n";
                    data_list.clear();
                    data_prepare::load_data(_dataset_name, data_list, _points);
                    break;
                case 2:
                    std::cout << "Running merge sort...\n";
                    std::cout<<"Sorting "<<data_list.get_size()<<" elements..."<<std::endl;
                    start = std::chrono::high_resolution_clock::now();
                    data_list.merge_sort();
                    end = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    std::cout << "Merge sort completed in " << duration.count() << " milliseconds.\n";
                    break;
                case 3:
                    std::cout << "Running bucket sort...\n";
                    std::cout<<"Sorting "<<data_list.get_size()<<" elements..."<<std::endl;
                    start = std::chrono::high_resolution_clock::now();
                    data_list.bucket_sort(10);
                    end = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    std::cout << "Bucket sort completed in " << duration.count() << " milliseconds.\n";
                    break;
                case 4:
                    std::cout << "Running intro sort...\n";
                    std::cout<<"Sorting "<<data_list.get_size()<<" elements..."<<std::endl;
                    start = std::chrono::high_resolution_clock::now();
                    data_list.intro_sort(0, data_list.get_size(), 2 * std::log2(data_list.get_size()));
                    end = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    std::cout << "Intro sort completed in " << duration.count() << " milliseconds.\n";
                    break;
                case 5:
                    std::cout << "Displaying list...\n";
                    data_list.display();
                    break;
                case 6:
                    std::cout << "Checking if sorted...\n";
                    std::cout << (data_list.check_sorted() ? "List is sorted.\n" : "List is not sorted.\n");
                    break;
                case 7:
                    std::cout << "Clearing list...\n";
                    data_list.clear();
                    break;
                case 0:
                    std::cout << "Exiting Manual Mode...\n";
                    return;
                    break;
                default:
                    std::cout << "Invalid choice.\n";
            }
        }
    }
    void run(){
        std::cout << "Welcome to the Sort Benchmarking Tool!\n";
        while(true){
            display_menu();
            int choice;
            std::cin >> choice;
            switch (choice) {
                case 1:
                    parameters();
                    break;
                case 2:
                    generate_dataset();
                    break;
                case 3:
                    manual_mode();
                    break;
                case 0:       
                    data_list.clear();             
                    std::cout << "Exiting program. Goodbye!\n";
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};
