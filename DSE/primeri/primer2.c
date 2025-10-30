#include <stdio.h>

int process_data(int input) {
    int temp_val = 0;
    temp_val = input * 2; 
    return temp_val; 
}

int main() {
    int rez = process_data(5);
    return 0;
}
