#include "s21_decimal.h"

int get_exponent(int bit) {
    for(int i = 0; i < 16; i++) {
        bit / = 2;
    }
    return bit % 256;
}

int get_sign(int bit) {
    return bit >= 0 ? 0 : 1;
}

int get_empty(int bit) {
    for(int i = 0; i < 16; i++) {
        if(bit % 2 != 0) { 
            return -1;
        }
        bit / = 2;
    }
    return bit % 256;
}
