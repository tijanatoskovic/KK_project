#include <stdio.h>

int main() {
    int x = 0;    // dead store
    x = 5;        
    return 0;
}
