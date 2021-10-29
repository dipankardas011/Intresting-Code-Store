/***
 * @goal is to create string datatype like c++ and java for ( C language)
 * @author Dipankar Das
 * @version 0.0.1
 */
#include <stdlib.h>
void toBinary(int N) {
    if (N > 0) {
        toBinary(N >> 1);
        printf("%d ", N&1);
    }
}


typedef struct stringF {
    // char character;// terminated by '\0' inside
    char *Str;
    size_t length;
} String;

/**
 * @param size the size of arrays i.e. chacters required
 * @return return array of characters
 */
String *createMemory(size_t size) {
    String *str;
    str->Str = (char *)malloc(sizeof(char) * (size + 1));
    str->length = size;
    return str;
}

/**
 * @def to get the length
 * @return to return the length
 */
size_t getLength(String *str) {
    return str->length;
}

/**
 * @def to pop chacters
 */
void pop(int );

/**
 * @def to return the chacter at certain position
 */
char atIndex(String *str, size_t index) {
    return (str->length >= index) ? '?' : str->Str[index];
}

/**
 * @def to push character or the chacter
 */
void push(String *str, char ch) {
    str = (String *)realloc(str,str->length+1);
    str->Str[str->length] = ch;
    str->length++;
}