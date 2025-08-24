#include <stdio.h>
#include <memory>

typedef struct {
    void (*speak)(void);
} VirtualTable;

typedef struct {
    VirtualTable* vtable;
} Animal;

void DogSpeak() {
    printf("dog speak.\n");
}

void CatSpeak() {
    printf("cat speak.\n");
}

VirtualTable animal_dog = {DogSpeak};
VirtualTable animal_cat = {CatSpeak};


int main() {
    Animal* animal = (Animal*)malloc(sizeof(Animal));
    animal->vtable = {&animal_dog};

    Animal* animal1 = (Animal*)malloc(sizeof(Animal));
    animal1->vtable = {&animal_cat};

    animal->vtable->speak();
    animal1->vtable->speak();

    return 0;
}