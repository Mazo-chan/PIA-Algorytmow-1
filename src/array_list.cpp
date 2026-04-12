#include "array_list.hpp"
#include "data_prepare.hpp"
#include <iostream>

template <typename T>

array_list<T>::~array_list(){
    delete[] _arr;
}
template <typename T>
array_list<T>::array_list() : _arr(nullptr), _size(0), _capacity(0) {}; //pytanie czy chcemy na pusto dawac 0 size czy zakladamy ze bedzie ktos przynajmniej 1 element zaraz wsadzal
template <typename T>
array_list<T>::array_list(int cap) : _capacity(cap), _size(0) {
    // std::cout<<"constructor with cap "<<cap<<std::endl;
    if(cap > 0) {
        _arr = new T[cap];
    } else {
        _arr = nullptr;
    }
};
template <typename T>
array_list<T>::array_list(const array_list& other){
            _capacity = other._capacity;
            _size = other._size;
            _arr = new T[_capacity];
            for(int i = 0; i < _size; i++){
                _arr[i] = other._arr[i];
            }
        };
template <typename T>
array_list<T>::array_list(const array_list& other, int cap):_capacity(cap), _arr(new T[_capacity]), _size(other._size > cap? cap : other._size){
            for(int i = 0; i < _size; i++){
                _arr[i] = other._arr[i];
            }
        };
template <typename T>
array_list<T>::array_list(array_list&& other1, array_list&& other2): _capacity(other1._capacity + other2._capacity), _size(other1._size + other2._size), _arr(new T[_capacity]){
            for(int i = 0; i < other1._size; i++){
                _arr[i] = other1._arr[i];
            }
            for(int i = 0; i < other2._size; i++){
                _arr[other1._size + i] = other2._arr[i];
            }
        };
template <typename T>
void array_list<T>::resize(int new_capacity){
    if(new_capacity <= 0) return; // Prevent resizing to invalid capacity
    T* new_arr = new T[new_capacity];
    for(int i = 0; i < _size; i++){
        new_arr[i] = _arr[i];
    }
    delete[] _arr;
    _arr = new_arr;
    _capacity = new_capacity;
}
template <typename T>
array_list<T>& array_list<T>::operator=(const array_list& other){
            if(this == &other) return *this;
            delete[] _arr;
            _capacity = other._capacity;
            _size = other._size;
            _arr = new T[_capacity];
            for(int i = 0; i < _size; i++){
                _arr[i] = other._arr[i];
            }
            return *this;
        };
void array_list<int>::display(){

    for(int i = 0; i < _size; i++){
        std::cout << "[" << _arr[i] << "] ";
        (i+1) % 10 == 0 ? std::cout << std::endl : std::cout << "";
    }
    std::cout << std::endl;
}
void array_list<DataIn>::display(){
    for(int i = 0; i < _size; i++){
        std::cout << "[" << _arr[i]._score << ", " << _arr[i]._title << "] ";
        (i+1) % 10 == 0 ? std::cout << std::endl : std::cout << "";
    }
    std::cout << std::endl;
}
template <typename T>
void array_list<T>::clear(){
    delete[] _arr;
    _arr = nullptr;
    _size = 0;
    _capacity = 0;
}
template <typename T>
void array_list<T>::push_back(T value){
    if(_size == _capacity) resize(_capacity == 0 ? 1 : _capacity * 2);
    _arr[_size++] = value;
}
template <typename T>
void array_list<T>::push_front(T value){
    if(_size == _capacity) resize(_capacity == 0 ? 1 : _capacity * 2);
    for(int i = _size; i > 0; i--){
        _arr[i] = _arr[i-1];
    }
    _arr[0] = value;
    _size++;
}
template <typename T>
void array_list<T>::insert(T value, int index){
    if(index < 0 || index > _size) return;
    if(_size == _capacity) resize(_capacity == 0 ? 1 : _capacity * 2);
    for(int i = _size; i > index; i--){
        _arr[i] = _arr[i-1];
    }
    _arr[index] = value;
    _size++;
}
// template <typename T>
// void array_list<T>::merge(const array_list& other){
//     if(_size + other._size > _capacity) resize(_capacity + other._size > _capacity * 2 ? _capacity + other._size : _capacity * 2);
//     for(int i = 0; i < other._size; i++){
//         _arr[_size + i] = other._arr[i];
//     }
//     _size += other._size;
// }
template <typename T>
void array_list<T>::pop_back(){
    if(_size == 0) return;
    _size--;
    if(_size < _capacity / 4 ) resize(_capacity / 2);
}
template <typename T>
void array_list<T>::pop_front(){
    if(_size == 0) return;
    for(int i = 0; i < _size - 1; i++){
        _arr[i] = _arr[i+1];
    }
    _size--;
    if(_size < _capacity / 4 ) resize(_capacity / 2);
}
template <typename T>
void array_list<T>::remove(int index){
    if(index < 0 || index >= _size) return;
    for(int i = index; i < _size - 1; i++){
        _arr[i] = _arr[i+1];
    }
    _size--;
    if(_size < _capacity / 4 ) resize(_capacity / 2);
}
template <typename T>
bool array_list<T>::find(T value){
    for(int i = 0; i < _size; i++){
        if(_arr[i] == value) return true;
    }
    return false;
}
template <typename T>
int array_list<T>::get_size(){
    return _size;
}
template <typename T>
T array_list<T>::get_last(){
    if(_size == 0) throw std::out_of_range("List is empty");
    return _arr[_size - 1];
}
template <typename T>
bool array_list<T>::check_sorted(){
    for(int i = 1; i < _size; i++){
        if(_arr[i] < _arr[i-1]) return false;
    }
    return true;
}
template <typename T>
void array_list<T>::merge_sort(){
    if(_size <= 1) return;
    int mid = _size / 2;
    // std::cout<<"going left "<<std::endl;
    array_list<T> left(mid);
    // std::cout<<"left size "<<left.get_size()<<std::endl;
    for(int i = 0; i < mid; i++){
        left.push_back(_arr[i]);
    }
    // std::cout<<"going right "<<std::endl;
    array_list<T> right(_size - mid);
    for(int i = mid; i < _size; i++){
        right.push_back(_arr[i]);
    }
    
    left.merge_sort();
    right.merge_sort();
    
    int i = 0, j = 0, k = 0;
    while(i < left._size && j < right._size){
        if(left._arr[i] < right._arr[j]){
            _arr[k++] = left._arr[i++];
        } else {
            _arr[k++] = right._arr[j++];
        }
    }
    while(i < left._size){
        _arr[k++] = left._arr[i++];
    }
    while(j < right._size){
        _arr[k++] = right._arr[j++];
    }
}
template <typename T>
void array_list<T>::heapify(int index, int left, int right){
    int largest = index;
    int leftChild = 2 * (index - left) + 1 + left;
    int rightChild = 2 * (index - left) + 2 + left;

    if(leftChild < right && _arr[leftChild] > _arr[largest]) largest = leftChild;
    if(rightChild < right && _arr[rightChild] > _arr[largest]) largest = rightChild;

    if(largest != index){
        std::swap(_arr[index], _arr[largest]);
        heapify(largest, left, right);
    }
}
template <typename T>
void array_list<T>::heap_sort(int left, int right){
    // Implementacja heap sort dla array_list na zakresie [left, right)
    if(right - left <= 1) return;
    
    // Tworzymy kopiec maksymalny
    int heap_size = right - left;
    for(int i = left + heap_size / 2 - 1; i >= left; i--){
        heapify(i, left, right);
    }
    
    // Sortujemy elementy
    for(int i = right - 1; i > left; i--){
        std::swap(_arr[left], _arr[i]);
        heapify(left, left, i);
    }
}
template <typename T>
void array_list<T>::intro_sort(int left, int right, int depth_limit){
    if(right - left <= 1) return;
    if(depth_limit == 0){
        heap_sort(left, right);
        return;
    }
    int pivot_index = left + (right - left) / 2;
    T pivot = _arr[pivot_index];
    std::swap(_arr[pivot_index], _arr[right - 1]);
    int store_index = left;
    for(int i = left; i < right - 1; i++){
        if(_arr[i] < pivot){
            std::swap(_arr[i], _arr[store_index]);
            store_index++;
        }
    }
    std::swap(_arr[store_index], _arr[right - 1]);
    
    intro_sort(left, store_index, depth_limit - 1);
    intro_sort(store_index + 1, right, depth_limit - 1);
}
template <>
void array_list<DataIn>::bucket_sort(int max_value){
    if(_size == 0) return;
    array_list<DataIn>* buckets = new array_list<DataIn>[max_value]; //od 1 do 10
    // std::cout<<"Created buckets "<<std::endl;
    for(int i = 0; i < _size; i++){
        buckets[_arr[i]._score - 1].push_back(_arr[i]);
        }
    int index = 0;
    for(int i = 0; i < max_value; i++){
        if(buckets[i].get_size() > 0){
            // std::cout<<"Sorting bucket "<<i+1<<" with size "<<buckets[i].get_size()<<std::endl;
            buckets[i].merge_sort(); // Sortujemy każdy kubełek
            for(int j = 0; j < buckets[i].get_size(); j++){
                _arr[index++] = buckets[i]._arr[j];
            }
        }
    }
    
    delete[] buckets;
}

// Explicit template instantiation
// template class array_list<int>;
template class array_list<DataIn>;
