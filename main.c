#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct Dog {
    const char *name;
    unsigned int age;
} Dog;

Dog *create_dog(const char *name, unsigned int age) {
    Dog *dog = malloc(sizeof(Dog));
    
    dog->name = name;
    dog->age = age;
    
    return dog;
}

void print_dog_info(void *data) {
    Dog dog = *(Dog *)data;
    
    printf("Hi I'm dog! My name is %s and I'm %u years old!\n",
            dog.name, dog.age);
}

void free_dog(void *data) {
    Dog *dog = data;
    
    free(dog);
}

int main() {
    list_t *list = new_list();
    
    push_front(list, create_dog("Frank", 4));
    push_front(list, create_dog("Big Red", 7));
    push_front(list, create_dog("Buddy", 10));
    
    printf("%d\n", get_size(list));
    
    empty_list(list, free_dog);
    
    if(is_empty(list)) {
        puts("The list is empty");
    } else {
        puts("The list contains data");
    }
    return 1;
}
