#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//----------provided code----------

//we can look at the char as the denotation of "method's" return value,
//it could've been int if we decided to point to a function returning an int
typedef char const* (*PTRFUN)();

char const* dogGreet(void){
  return "vau!";
}
char const* dogMenu(void){
  return "kuhanu govedinu";
}
char const* catGreet(void){
  return "mijau!";
}
char const* catMenu(void){
  return "konzerviranu tunjevinu";
}

//----------provided code----------

//tables of PTRFUNs defining concrete types' behaviour and
//their initialization code
PTRFUN dogVTable[2] = {dogGreet, dogMenu};
PTRFUN catVTable[2] = {catGreet, catMenu};

//datatype struct Animal containing:
typedef struct {
  //a) a pointer to the Animal's name
  char* name;

  //b) a pointer to a function table containing PTRFUNS for 
  //the Animal's concrete type's functions
  //NOTE: it doesn't have to be a pointer (we could just have
  //declared a PTRFUN table), but this way we are reducing
  //memory footprint of polymorphism
  PTRFUN* vTable;
} Animal;


//"abstract" functions of "interface" Animal

void animalPrintGreeting(Animal* animalImplementation) {
  printf("%s pozdravlja: %s\n", animalImplementation->name,
    animalImplementation->vTable[0]());
}
void animalPrintMenu(Animal* animalImplementation) {
printf("%s voli %s\n", animalImplementation->name,
    animalImplementation->vTable[1]());
}

//Animal "implementations'" constructors

void constructDog(Animal* animal, char* name) {
  //argument animal points to allocated heap space of 
  //the size of an Animal, but it is "empty" - we need to:

  //a) put a string (i. e. char*) in the "container" for the name
  animal->name = name;

  //b) put a pointer to the "virtual table" (i. e. PTRFUN) of
  //the concrete type in question in the "container" for the v. table
  //those v. tables have been defined earlier in the code
  animal->vTable = dogVTable;
}

  constructCat(Animal* animal, char* name) {
  animal->name = name;
  animal->vTable = catVTable;
}

//Animal "implementations'" constructors' encapsulation

Animal* createDog(char* name) {
  //allocate memory space for an Animal implementation
  Animal* animal = (Animal*)malloc(sizeof(Animal));

  //now we have a pointer to empty space enough for a 
  //char* (name) and a pointer to an array of two PTRFUNs
  //(pointer to vTable)

  //that means we have three empty "containers" to put
  //implementation's "fields" in - one for name and 
  //two for function implementations (PTRFUNs)

  //let's initialize those "containers"
  animal->name = NULL;

  PTRFUN animalUnimplVTable[2] = {NULL, NULL};
  animal->vTable = animalUnimplVTable;

  //construct a Dog (fill the "containers")
  constructDog(animal, name);

  return animal;
}

Animal* createCat(char* name) {
  Animal* animal = (Animal*)malloc(sizeof(Animal));

  animal->name = name;
  PTRFUN animalUnimplVTable[2] = {NULL, NULL};
  animal->vTable = animalUnimplVTable;

  constructCat(animal, name);

  return animal;
}

//function for creating n dogs
//returns pointer to the first element of array
//of pointers to Animal implementations
Animal* createNDogs(int n) {
  Animal** dogs = (Animal**)malloc(sizeof(Animal*)*n);

  for (int i = 0; i < n; i++) {
    *(dogs+i) = createDog("");
  }

  return dogs;
}

void testAnimals(void){
  struct Animal* p1=createDog("Hamlet");
  struct Animal* p2=createCat("Ofelija");
  struct Animal* p3=createDog("Polonije");

  animalPrintGreeting(p1);
  animalPrintGreeting(p2);
  animalPrintGreeting(p3);

  animalPrintMenu(p1);
  animalPrintMenu(p2);
  animalPrintMenu(p3);

  free(p1); free(p2); free(p3);

  createNDogs(3);
}

int main(void) {
    testAnimals();
    return 0;
}
