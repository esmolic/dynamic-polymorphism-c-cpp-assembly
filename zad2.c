#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//----------Unary_Function----------

//vtable will be a struct instead of array
//for easier upgrade
typedef struct
{
    double (*value_at)(struct Unary_Function*, double);
    double (*negative_value_at)(struct Unary_Function*, double)
} Unary_Function_vtable;

//"class"
typedef struct {
    Unary_Function_vtable* vptr;

    int lower_bound;
    int upper_bound;


} Unary_Function;

//virtual functions

//pure virtual function
//cannot omit because other Unary_Function's functions (or its constructor) may call it
double Unary_Function_value_at(Unary_Function* this, double x) {
    return 0;
}


double Unary_Function_negative_value_at(Unary_Function* this, double x) {
    return -1 * (Unary_Function_value_at(this, x));
}

//non-virtual functions

//"class" function
void tabulate(Unary_Function* this) {
    for (int x = this->lower_bound; x <= this->upper_bound; x++) {
        printf("f(%d)=%lf\n", x, this->vptr->value_at(this, x));
    }
}

//"static" function
bool same_functions_for_ints(Unary_Function *f1, Unary_Function *f2, double tolerance) {
      if(f1->lower_bound != f2->lower_bound) return false;
      if(f1->upper_bound != f2->upper_bound) return false;
      for(int x = f1->lower_bound; x <= f1->upper_bound; x++) {
        double delta = f1->vptr->value_at(f1, x) - f2->vptr->value_at(f2, x);
        if(delta < 0) delta = -delta;
        if(delta > tolerance) return false;
      }
      return true;
    };

Unary_Function_vtable* Unary_Function_vptr = {NULL, &Unary_Function_negative_value_at};

//"constructor"
void Unary_Function_constructor(Unary_Function* this, int lower_bound, int upper_bound) {
    this->vptr = &Unary_Function_vptr;

    this->lower_bound = lower_bound;
    this->upper_bound = upper_bound;
}

//"new"
//since it would be an abstract class in OOP, not allowed

/*
Unary_Function* new_Unary_Function(int lower_bound, int upper_bound) {
    Unary_Function* this = (Unary_Function*) malloc(sizeof(Unary_Function));
    Unary_Function_constructor(this, lower_bound, upper_bound);

    return this;
}
*/

//----------Linear----------

typedef struct {
    double (*value_at)(Unary_Function* this, double x);
} Linear_vtable;

typedef struct {
    Linear_vtable* vptr;

    int lower_bound;
    int upper_bound;
    double a;
    double b;
} Linear;

double Linear_value_at(Unary_Function* this, double x) {
    Linear* this_impl = (Linear*) this;

    return (this_impl->a)*x + (this_impl->b);
}

Linear_vtable* Linear_vptr = {&Linear_value_at};

void Linear_constructor(Linear* this, int lower_bound, int upper_bound, double a_coef, double b_coef) {
    Unary_Function_constructor((Unary_Function*) this, lower_bound, upper_bound);
    this->a = a_coef;
    this->b = b_coef;

    this->vptr = &Linear_vptr;
}

Unary_Function* new_Linear(int lower_bound, int upper_bound, double a_coef, double b_coef) {
    Linear* this = (Linear*) malloc(sizeof(Linear));
    Linear_constructor(this, lower_bound, upper_bound, a_coef, b_coef);
    return (Unary_Function*)this;
}

//----------Square----------
typedef struct {
    double (*value_at)(Unary_Function* this, double x);
} Square_vtable;

typedef struct {
    Square_vtable* vptr;

    int lower_bound;
    int upper_bound;
} Square;

double Square_value_at(Unary_Function* this, double x) {
    //probably redunant
    //Square* this_impl = (Square*) this;

    return x*x;
}

Square_vtable* Square_vptr = {&Square_value_at};

void Square_constructor(Square* this, int lower_bound, int upper_bound) {
    Unary_Function_constructor((Unary_Function*) this, lower_bound, upper_bound);
    this->vptr = &Square_vptr;
}

Unary_Function* new_Square(int lower_bound, int upper_bound) {
    Square* this = (Square*) malloc(sizeof(Square));

    Square_constructor(this, lower_bound, upper_bound);
    return (Unary_Function*)this;

}


int main() {
  Unary_Function *f1 = new_Square(-2, 2);
  tabulate(f1);
  Unary_Function *f2 = new_Linear(-2, 2, 5, -2);
  tabulate(f2);
  printf("f1==f2: %s\n", same_functions_for_ints(f1, f2, 1E-6) ? "DA" : "NE");
  printf("neg_val f2(1) = %lf\n", f2->vptr->negative_value_at(f2, 1.0));
  free(f1);
  free(f2);
  return 0;

}