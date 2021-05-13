#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *str;
    int length;
    int capacity;
} string;

void set_str(string *str, char entrada[]) {
    str->str = NULL;
    str->length = 0;
    str->capacity = 0;

    str->length = strlen(entrada);
    if(entrada[str->length-1] == '\n') entrada[--str->length] = '\0';

    if(str->length%16) str->capacity = 16*((str->length/16)+1);
        else str->capacity = 16*(str->length/16);

    str->str = malloc(str->capacity*sizeof(char));

    strcpy(str->str, entrada);
}

void read_str(string *entrada) {
    entrada->str = malloc(300*sizeof(char));
    fgets(entrada->str,300,stdin);
}

void concat_str(string *str, string *entrada) {
    int tam = str->length+strlen(entrada->str);
    if(tam > str->capacity) {
        int capAux;
        if(tam%16) capAux = 16*((tam/16)+1);
            else capAux = 16*(tam/16);
        str->str = realloc(str->str, capAux*sizeof(char));
        str->length = tam;
        str->capacity = capAux;
    } else {
        str->length = tam;
    }
    strcat(str->str, entrada->str);
}

void clear_str(string *str) {
    free(str->str);
}

int main() {
    string greeting;
    string name;
    set_str(&greeting, "Oi ");
    read_str(&name);
    concat_str(&greeting, &name);
    printf("%s\n", greeting.str);
    printf("%i %i\n", greeting.capacity, greeting.length);
    clear_str(&greeting);
    clear_str(&name);
    return 0;
}