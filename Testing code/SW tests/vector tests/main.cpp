#include <iostream>
#include <stdlib.h>

using namespace std;

int Vector[]= {1,2,3,4,5,6};
void vectS(int *a, int n){
    for(int i =0; i<6; i++){
        a[i] += 1;
    }
}
int main()
{
    for(int i =0; i<6; i++){
        cout << Vector[i];
    }
    cout << endl;
    system ("CLS");
    vectS(Vector, 6);

    for(int i =0; i<6; i++){
        cout << Vector[i];
    }

    return 0;
}
