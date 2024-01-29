
#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

typedef struct 
{
    int bits[4];
} s21_decimal;

//arithmetic

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // оператор сложения 
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // оператор вычитания 
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // оператор умножения
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // оператор деления 

//comparison

int s21_is_less(s21_decimal, s21_decimal); // <
int s21_is_less_or_equal(s21_decimal, s21_decimal); // <=
int s21_is_greater(s21_decimal, s21_decimal); // >
int s21_is_greater_or_equal(s21_decimal, s21_decimal); // >=
int s21_is_equal(s21_decimal, s21_decimal); // ==
int s21_is_not_equal(s21_decimal, s21_decimal); // !=

//convert 

int s21_from_int_to_decimal(int src, s21_decimal *dst); // реобразование из int 
int s21_from_float_to_decimal(float src, s21_decimal *dst); // реобразование из float
int s21_from_decimal_to_int(s21_decimal src, int *dst); // реобразование в int  
int s21_from_decimal_to_float(s21_decimal src, float *dst); // реобразование в float

//another functions

int s21_floor(s21_decimal value, s21_decimal *result); // округление в сторону отрицательной бесконечности
int s21_round(s21_decimal value, s21_decimal *result); // округление до ближайшего целого 
int s21_truncate(s21_decimal value, s21_decimal *result); // отбрасывание дробной части 
int s21_negate(s21_decimal value, s21_decimal *result); // результат умножения на -1

//Onniajua functions

int get_exponent(int bit);


#endif