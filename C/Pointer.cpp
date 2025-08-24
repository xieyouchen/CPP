#include <stdio.h>
#include <memory>

typedef struct {
    void (*speak)(void);
} VirtualTable;

typedef struct {
    VirtualTable* vtable;
} Animal;

void DogSpeak(void) {
    printf("dog speak.\n");
}

VirtualTable animalVTable = {DogSpeak};

int main() {
    int* p = 0;
    p = p+1;
    printf("%x\n",p);

    Animal* animal = (Animal*)malloc(sizeof(Animal));
    animal->vtable = {&animalVTable};

    animal->vtable->speak();
    
    return 0;
}
