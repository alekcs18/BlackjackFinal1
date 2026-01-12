#include <iostream>
#include <iomanip>
#include <limits>
#include <cfloat>
using namespace std;
/*● Citeste doua numere intregi de la tastatura
● Citeste un caracter de la tastature ce reprezinta o operatie matematica
(+,-,/,*,^)
● “ ^ “ este ridicare la putere ( 2 ^ 4 = 16 -> 2
4
)

● Afiseaza rezultatul operatiei aplicata pe cele doua numere
● Verifica overflow si underflow si afiseaza in caz de eroare
● Verifica impartire la 0 si afiseaza in caz de eroare
● Extra: trateaza rezultatul ca si float (c style casting (float)) si afiseaza-l cu 3
zecimale (check std::format)
*/
float putere(float a, int b){
    //a=numarul
    //b=puterea
    float rezultat=1;
    if(b==0){
        a=1;
    }else if(b==1){
        return a;
    }
    while(b){
        rezultat *=a;
        b--;
    }
    if(rezultat>FLT_MAX){
        return 0;
    }
    return rezultat;
}

//a+b
bool overflow_underflow_adunare(float a, float b) {
    if (a > 0 && b > 0 && a > FLT_MAX - b) return true;   // overflow
    if (a < 0 && b < 0 && a < FLT_MIN + b) return true;   // underflow
    return false;
}

//a-b
bool overflow_underflow_scadere(float a, float b) {
    if (b < 0 && a > FLT_MAX + b) return true;   // overflow
    if (b > 0 && a < FLT_MIN + b) return true;   // underflow
    return false;
}

//a*b
bool overflow_underflow_inmultire(float a, float b) {
    if (a != 0 && b != 0 && (a > FLT_MAX / b || a < FLT_MIN / b))  // overflow
    return false;
}

//a/b
bool overflow_underflow_impartire(float a, float b) {
    if (a == FLT_MIN && b == -1)   // overflow
    return false;
}


int main(){
    char op;
    float a, b;
    cout<<"Numerele sunt: ";
    cin>>a>>b;
    cout<<"Alege operatia dintre a si b!"<<endl<<"Ai optiunile urmatoare:"<<endl<<"+"<<" Adunare"<<endl<<"-"<<" Scadere"<<endl<<"*"<<" Inmultire"<<endl<<"/"<<" Impartire"<<endl<<'^'<<" Ridica la puterea b " <<endl;
    cout<<"Operatia este: ";
    cin>>op;
    switch(op) {
        default:

            cout<<"Operatie invalida! Selecteaza una dintre operatiile afisate!"<<endl;
            break;

        case '+':

            if(overflow_underflow_adunare(a, b)==true){
                cout<<"Adunarea nu este posibila";
            }else{
                cout<<"a + b = "<<setprecision(4)<<a+b;
            }
        break;

        case '-':

        if(overflow_underflow_scadere(a, b)==true){
                cout<<"Scaderea nu este posibila";
            }else{
                cout<<"a - b = "<<setprecision(4)<<a-b;
            }
        break;

        case '*':

        if(overflow_underflow_inmultire(a, b)==true){
                cout<<"Inmultirea nu este posibila";
            }else{
                cout<<"a * b = "<<setprecision(4)<<a*b;
            }
        break;

        case '/':

        if(overflow_underflow_impartire(a, b)==true){
                cout<<"Impartirea nu este posibila";
            }
            if(b==0){
                cout<<"Impartirea nu este posibila!";
         }else{
            cout<<"a / b = "<<setprecision(4)<<a/b;
            }
        break;

        case '^':

            if(putere(a,b)==0){
                cout<<"Ridicarea la putere nu este posibila";
            }else{
                cout<<"a ^ b = "<<setprecision(4)<<putere(a,b);
            }
        break;

    }
}


