#include <iostream>
#include <sstream>  // istringstream
#include <string>
using namespace std;

int f(int n){
    if(n == 5)
        return -1;
    else
        return 0;
}

int main() {
    int n;
    while(cin>>n){
        if(n > 20)
            break;
        else{
            if(n == 0)
                break;
        }
    }
    return 0;
}