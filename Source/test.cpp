#include <iostream>
int main(int argc, char const *argv[])
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int d = 0;
    int size = 621;
    for(int k = 0; k<1242;k++){
        if(k>=d && k<d+size){
            std::cout << k<<'\n';
        }
    }
    std::cout <<"IN BETWEEN\n";
    d=621;
    for(int k = 0; k<1242;k++){
        if(k>=d && k<d+size){
            std::cout << k<<'\n';
        }
    }
    return 0;
}
