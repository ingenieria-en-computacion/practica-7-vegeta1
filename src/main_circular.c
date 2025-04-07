#define LINKED_LIST_IMPLEMENTATION
#include "Circular_Linked_List.h"
#include <stdio.h>

// Funciones de impresión
void print_int(int value) {
    printf("%d", value);
}

bool int_cmp(int a, int b) {
    return a == b;
}

void print_char(char value) {
    printf("%c", value);
}

bool char_cmp(char a, char b) {
    return a == b;
}

int main() {
    // Lista circular de enteros
    List_int* nums = list_int_create();
    list_int_append(nums, 10);
    list_int_append(nums, 20);
    list_int_append(nums, 30);

    printf("Lista de enteros: ");
    list_int_print(nums, print_int);  // Debería imprimir [10, 20, 30]

    // Probando inserciones
    list_int_insert(nums, 5, 0);      // Al principio
    list_int_insert(nums, 25, 3);     // En el medio
    list_int_append(nums, 40);        // Al final

    printf("Despues de insertar: ");
    list_int_print(nums, print_int);  // Debería imprimir [5, 10, 20, 25, 30, 40]

    // Pruebas de eliminación
    list_int_remove_at(nums, 0);      // Eliminar el primero
    list_int_remove_at(nums, 2);      // Eliminar en el medio
    list_int_remove_at(nums, list_int_length(nums) - 1); // Eliminar el último

    printf("Despues de eliminar: ");
    list_int_print(nums, print_int);  // Debería imprimir [10, 20, 30]

    list_int_destroy(nums);

    // Lista circular de caracteres
    List_char* chars = list_char_create();
    list_char_append(chars, 'a');
    list_char_append(chars, 'b');
    list_char_append(chars, 'c');
    list_char_append(chars, 'd');
    list_char_append(chars, 'e');

    printf("Lista de caracteres: ");
    list_char_print(chars, print_char);  // [a, b, c, d, e]

    list_char_insert(chars, 'x', 0);     // Inserta al inicio
    list_char_insert(chars, 'y', 3);     // Inserta en el medio
    list_char_append(chars, 'z');        // Inserta al final

    printf("Despues de insertar en chars: ");
    list_char_print(chars, print_char);  // [x, a, b, y, c, d, e, z]

    list_char_destroy(chars);

    return 0;
}
