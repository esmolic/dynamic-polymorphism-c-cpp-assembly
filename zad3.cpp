#include <iostream>

class CoolClass{
public:
  virtual void set(int x){x_=x;};
  virtual int get(){return x_;};
private:
  int x_;
};
class PlainOldClass{
public:
  void set(int x){x_=x;};
  int get(){return x_;};
private:
  int x_;
};

using namespace std;
int main() {
    cout << "PlainOldClass size: " << sizeof(PlainOldClass) << endl;
    cout << "CoolClass size: " << sizeof(CoolClass) << endl;
}

/*
PlainOldClass veličine je 4 bajta. To je zato jer objekt čuva varijablu tipa int. 
CoolClass veličine je 16 bajtova jer čuva pokazivač na vtable (8 bajtova), 
varijablu tipa int (4 bajtova), a ostala 4 bajta pripisujem paddingu.
*/