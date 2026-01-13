// #include <iostream>
// #include <iterator>
// #include <vector>
// #include <climits>

// int main(){
//     int array[3][3][3] = {{ { 35, 9, 20} ,{41, 67, 27} ,{75, 17, 51} },{ { 35, 9, 20} , {41, 67, 27} ,{75, 17, 51} },{ { 35, 9, 20} , {41, 67, 27} ,{75, 17, 51} }};
//     int x = std::size(array[0]);
//     int y = std::size(array);
//     int z = std::size(array[0][0]);
//     int max_size = INT_MIN;
//     int min_size = INT_MAX;
//     int sum = 0;
//     for(int i = 0; i < x;  i++){
//         for(int j = 0; j < y;  j++){
//             for(int k = 0; k < z; k++){

        
            
        
//         //std::cout <<array[i]<<std::endl;
//         //std::cout<<array_size<<std::endl;
//          int element = array[i][j][k];
//             if(element > max_size){
//                 max_size = element;
//             }
            

//             //std::cout<<array_size<<std::endl;
//             if(element < min_size){
//                 min_size = element;
            
            
//             }
            
//             sum = sum + element;
//         }
//     }
//     std::cout<<"Max value of array: "<<max_size<<std::endl;
//     std::cout<<"Min value of array: "<<min_size<<std::endl;
//     std::cout<<"Sum of elements of array: "<<sum<<std::endl;
//     std::cout<<array[3][3][3]<<std::endl;

    
    
//     return 0;
// }
// }
#include <iostream>
#include <iterator>
#include <vector>
#include <climits>
#include <cstring>

#define BUFF_MAX_LEN 256
int function(char buffer[], char letter){
    int buffer_len = strlen(buffer);
    int letter_count = 0;
    
    for(int i = 0; i < buffer_len; i++){
        if(buffer[i] == letter){
            letter_count++;
        }
        
    }
    return(letter_count);
    
}

int main()
{
    
    char buffer[BUFF_MAX_LEN];
    char letter;
    
    std::cout<<"Cititor de litere in propozitii"<<std::endl;
    std::cout<<"Introduceti o litera: "<<std::endl;
    std::cin >> letter;
    std::cout << "Am citit:" << letter << std::endl;

    std::cout<<"Scrieti o propozitie"<<std::endl;
    std::cin >> buffer;
    std::cout << "Am citit:" << buffer << std::endl;
    
    std::cout<<function(buffer,letter)<<std::endl;

    return 0;
}

//Sa citeasca 2,3 caractere dar lucrand cu o noua functie(working around it)