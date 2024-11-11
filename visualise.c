#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>

int checkvalid_decimal(const char *t) {
    int i = 0;
    int p = 0;
    
    if (t[0] =='-') {
        i = 1;
    }
    for (; t[i] != '\0'; i++) {
        if (t[i]== '.') {
            if (p) {
            return 0; 
            }
            p = 1;
        } else if (!isdigit(t[i])) {
            return 0;
    }
    }

    if (t[0] == '0') {
        return 0;
    }

    if (t[i - 1] == '.') {
        return 0;
    }
    return 1;
}

void convertChar(char x, char *y) {
    int index = 0;
    for (int i = 7; i >= 0; i--) {
        if ((x >> i) & 1) {   
            y[index++] = '1';
        } else {  
            y[index++] = '0';
        }
        if (i % 4 == 0 && i != 0) {
            y[index++] = ' ';
        }

}
    y[index] = '\0';
}

void convertInt(int x, char *y) {
    
    int index = 0;
    for(int i = 31; i >= 0; i--){
        if ((x >> i) & 1) {
            
            y[index++] = '1';
        } else {
            y[index++] = '0';
        }
        if (i % 4 == 0 && i != 0) {
            y[index++] = ' ';
        }
    }
    y[index] = '\0';
}

void convertLong(long x, char *y) {
    int index = 0;
    int bits = sizeof(long) * 8;
    for (int i = bits - 1; i >= 0; i--) {
        if ((x >> i) & 1) {
            y[index++] = '1';
        } else {
            y[index++] = '0';
        }
        if (i % 4 == 0 && i != 0) {
            y[index++] = ' ';
        }
    }
    y[index] = '\0';
}

void convertUnsignedchar(unsigned char x, char *y) {
    int index = 0;
    for (int i = 7; i >= 0; i--) {
        if ((x >> i) & 1) {
            y[index++] = '1';
        } else {
            y[index++] = '0';
        }
        if (i % 4 == 0 && i != 0) {
            y[index++] = ' ';
        }
    }
    y[index] = '\0';
}

void convertUnsignedint(unsigned int x, char *y) {
    int index = 0;
    for (int i = 31; i >= 0; i--) {
        if ((x >> i) & 1) {
            y[index++] = '1';
        } else {
            y[index++] = '0';
        }
        if (i % 4 == 0 && i != 0) {
            y[index++] = ' ';
        }
    }
    y[index] = '\0';
}

void convertDouble(double x, char *y) {
    unsigned long long *p = (unsigned long long *)&x;
    
    unsigned long long m = *p;
    int index = 0;
    for (int i = 63; i >= 0; i--) {
        if ((m >> i) & 1) {
            
            y[index++] = '1';
        } else {
            y[index++] = '0';
        }
        
        if (i % 4 == 0 && i != 0) {
            y[index++] = ' ';
        
        }

    }
    y[index] = '\0';
}

long long convertBinary(const char *theBinary) {
    long long a = 0;
    
    int length = strlen(theBinary);
    int whetherNegative = (length == 8 && theBinary[0] == '1');
    while (*theBinary) {
    
    if (*theBinary == '1') {
        a = (a << 1) | 1;
    } else if (*theBinary == '0') {
        a = a << 1;
    } else if (*theBinary != ' ') {
        return LLONG_MIN;
    }
        
        theBinary++;
    
    }
    if (whetherNegative &&length == 8) {
        a -= (1LL << 8);
    }
    
    return a;
}

int checkvalid_binary(const char *thebinary) {
    
    for (int i = 0;thebinary[i] !='\0'; i++) {
        if (thebinary[i] != '0' && thebinary[i] != '1' && thebinary[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

void testChar() {
    char result[10];
    convertChar(7, result);
    assert(strcmp(result, "0000 0111") == 0);

    convertChar(-128,result);
    assert(strcmp(result, "1000 0000") == 0);


    convertChar(255, result);
    assert(strcmp(result, "input error."));

}

void testInt() {
    char result[40];
    convertInt(10, result);
    assert(strcmp(result, "0000 0000 0000 0000 0000 0000 0000 1010") == 0);

    convertInt(-1, result);
    assert(strcmp(result, "1111 1111 1111 1111 1111 1111 1111 1111") == 0);
}

void testLong() {
    char result[80];

    convertLong(10, result);
    assert(strcmp(result, "0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010") == 0);

    convertLong(-1, result);
    assert(strcmp(result, "1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111") == 0);

}

void testUnsignedchar(){
    char result[10];

    convertUnsignedchar(255, result);
    assert(strcmp(result, "1111 1111") == 0);

    convertUnsignedchar(0, result);
    assert(strcmp(result, "0000 0000") == 0);
}

void testUnsignedint() {
    char result[40];

    convertUnsignedint(0, result);
    assert(strcmp(result, "0000 0000 0000 0000 0000 0000 0000 0000") == 0);
}

void testDouble() {
    char result[80];

    convertDouble(-1.25, result);
    assert(strcmp(result, "1011 1111 1111 0100 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000") == 0);

}

void testconvertBinary() {
    assert(convertBinary("0000 0111") == 7);

}

int main(int number, char *argument[]) {
    if (number == 1) { 
        testChar();
        testInt();
        testLong();
        testUnsignedchar();
        testUnsignedint();
        testDouble();
        testconvertBinary();
        
        printf("All tests pass\n");
        
        return 0;
    }

    if (number == 3) {
        char r[100];
        if (strcmp(argument[1], "char") ==0){
            if (checkvalid_binary(argument[2])) {
                
                long long k = convertBinary(argument[2]);
            if (k < CHAR_MIN || k > CHAR_MAX) {
                
                printf("Input error\n");
                return 1;
                }
                printf("%lld\n", k);
            } else if (checkvalid_decimal(argument[2])){
                
                int value = atoi(argument[2]);
                
            if (value < CHAR_MIN || value > CHAR_MAX) {
                    printf("Input error\n");
                    return 1;
                } else {
                    convertChar((char)value, r);
                    printf("%s\n", r);
                }
            } else {
                printf("Input error\n");
                return 1;
            }
        } else if (strcmp(argument[1], "int") == 0) {
            if (!checkvalid_decimal(argument[2])) {
                printf("Input error\n");
                return 1;
            }
            int value = atoi(argument[2]);
            convertInt(value, r);
            printf("%s\n", r);
        } else if (strcmp(argument[1], "long") == 0) {
            if (!checkvalid_decimal(argument[2])) {
               
                printf("Input error\n");
                return 1;
            }
            long value = atol(argument[2]);
            
            convertLong(value, r);
            printf("%s\n", r);
        } else if (strcmp(argument[1], "double") == 0) {
            if (!checkvalid_decimal(argument[2]) && argument[2][0] != '-') {
                printf("Input error\n");
                return 1;
            }
            double value = atof(argument[2]);
            
            convertDouble(value, r);
            printf("%s\n", r);
        } else if (strcmp(argument[1], "binary") == 0) {
            
            if (!checkvalid_binary(argument[2])) {
                printf("Input error\n");
                return 1;
            }
            long long k = convertBinary(argument[2]);
            if (k == LLONG_MIN) {
                printf("Input error\n");
                return 1;
            }
            printf("%lld\n", k);
        } else {
           
            printf("Input error\n");
            return 1;
        }

        return 0;
    }

    if (number == 4) {
        char r[100];
        if (strcmp(argument[1], "unsigned") == 0) {
            if (strcmp(argument[2], "char") == 0) {
                if (checkvalid_binary(argument[3])) {
                    
                    long long k = convertBinary(argument[3]);
                if (k < 0 || k > UCHAR_MAX) {
                        
                        printf("Input error\n");
                        return 1;
                    }
                    printf("%lld\n", k);
                } else if (checkvalid_decimal(argument[3])) {
                    
                    unsigned int value = atoi(argument[3]);
                    if (value > UCHAR_MAX) {
                        printf("Input error\n");
                        return 1;
                    }
                    convertUnsignedchar((unsigned char)value, r);
                    printf("%s\n", r);
                } else {
                    printf("Input error\n");
                    return 1;
                }
            } else if (strcmp(argument[2], "int") == 0) {
                if (!checkvalid_decimal(argument[3])) {
                    
                    printf("Input error\n");
                    return 1;
                }
                
                unsigned long value = atol(argument[3]);
                if (value > UINT_MAX) {
                    printf("Input error\n");
                    return 1;
                }
                convertUnsignedint((unsigned int)value, r);
                printf("%s\n", r);
            } else {
                printf("Input error\n");
                return 1;
            }
        } else {
            printf("Input error\n");
            return 1;
        }
        return 0;
    }

    printf("Input error\n");
    return 1;
}
