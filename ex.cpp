#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
// genereaza un nr random intre 0 si 100
// citeste de la tastatura un numar
// calculeaza diferenta absoluta intre numarul random si cel citit
// std::abs -> https://en.cppreference.com/w/cpp/numeric/math/abs

// daca diferenta > 20 print "foarte rece"
// daca diferenta > 10 <= 20 print "rece"
// daca diferenta > 5  <= 10 print "cald"
// daca diferenta <= 5 print "foarte cald"
// daca se ghiceste numarul print "BINGO!"

// daca se apasa '0' se iese din bucla
// Optional: daca se apasa '1' se genereaza un nr random nou
int n,dif;
int main(){
    cout<<"Citeste un numar de la tastatura: "<<endl;
    cin>>n;
    bool value=true;
    while(value==true){
        srand(time({}));            
        int randomNumber = rand() % 101; 
        //cout<<"Numarul generat este "<<randomNumber<<endl;
        dif=abs(randomNumber-n);
        if(dif>20){
            cout<<"Foarte rece"<<endl;
        }else if(dif>10){
            cout<<"Rece"<<endl;
        }else if(dif>50){
            cout<<"Cald"<<endl;
        }else if(dif!=0 && dif<=5){
            cout<<"Foarte cald"<<endl;
        }else if(dif==0){
            cout<<"Bingo!";
            break;
        }
        char op;
        cout<<"0 - se termina programul"<<endl<<"1 - se genareaza un alt numar"<<endl;
        cin>>op;
        switch (op){
            case '0':
            value=false;
            break;
            case '1':
            break;
        }

    }
  
}