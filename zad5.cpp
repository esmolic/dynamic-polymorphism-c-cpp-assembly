#include <iostream>

class B{
public:
  virtual int prva()=0;
  virtual int druga(int)=0;
};

class D: public B{
public:
  virtual int prva(){return 42;}
  virtual int druga(int x){return prva()+x;}
};

using namespace std;
void print_B_virtual_functions(B* pb) {
    
  typedef int (*FUNPTR)(B*, int);
  typedef int (*prva)(B*);
  typedef int (*druga)(B*, int);

  cout << pb << endl;

  FUNPTR* vt = *(FUNPTR**)pb;

  prva pr = (prva) vt[0];
  druga dr = vt[1];

    cout << "Rezultat funkcije prva(): " << pr(pb) << endl;
    
    int x;
    cout << "Unesite x: ";
    cin >> x;
    
    cout << "Rezultat funkcije druga(x): " << dr(pb, x) << endl;

}

int main() {
    B* pb = new D();
    print_B_virtual_functions(pb);
}
