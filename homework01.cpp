#include <iostream>
#include <limits>
#include <cmath>
#include <cstdint>
#include <iomanip>
using namespace std;






 int main(){
    
     float a;
     float b;
     char op;

    std::cout << "CPP MIN size: " << std:: numeric_limits<int>::min() << std::endl;
    std::cout << "CPP MAX size: " << std:: numeric_limits<int>::max() << std::endl;

    
     
    
     
    std::cout <<"Calculator app " << std::endl;
    std::cout <<"Poti face op de tip: *,/,-,+,^"<< std::endl;
    std::cout <<"Pentru impartirea in multimea Q, se va folosi '.' pentru delimitarea zecimalelor"<< std::endl;
    std::cout <<"Introdu un numar a: " << std::endl;
    std::cin >> a;

    std::cout <<"Selectati tipul de operator: "<< std::endl;
    std::cin >> op;

    std::cout <<"Introdu al doilea numar: " << std::endl;
    std::cin >> b;

    float result;
    switch(op){
        case '+':
        result = a + b;
        if (isinf(result)){
            std::cout<<"Overflow"<<std::endl;
        }
        else{
            std::cout <<"a+b= " <<    result << std::endl;
        }
        break;
        case '-':
        result = a - b;
        if (isinf(result)){
            std::cout<<"Overflow/Underflow!\n"<<std::endl;
        }
        else{
            std::cout <<"a-b= " <<  result << std::endl;
        }
        break;
        case '/':
        result = a / b;
        if (isinf(result) || isnan(result))
            {std::cout<< "undefined"<<endl;
        
            }
        else{
            std::cout <<"a/b= " << setprecision(3) <<   result <<std::endl;
        }
        break;
        case '*':
        result = a * b;
        if(isinf(result)){ 
            cout <<"Overflow\n"<<std::endl;

        }
        else{
            std::cout <<"a*b= " <<  result << std::endl;
        }
        break;
        case '^':
        result = pow(a, b);
        if(isinf(result) || isnan(result)){
            std::cout<<"Overflow/undefined"<< std::endl;
        }
        else{std::cout <<"a^b= " << setprecision(3) <<  result<< std::endl;}
        break;
        
      
        default:
            std::cout<< "Eroare operatia nu este valida" << std::endl;
    }

    
    

    
     

    return 0;
    
}