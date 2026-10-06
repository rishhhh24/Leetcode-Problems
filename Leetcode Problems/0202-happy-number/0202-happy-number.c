#include<stdbool.h>
int getNext(int n){
    int sum=0;
    while(n>0){
        int digit=n%10;
        sum+=digit*digit;
        n/=10;
    }
    return sum;
}
bool isHappy(int n){
    int seen[1000]={0};
    while(n!=1){
        int idx=n%1000;
        if(seen[idx]==n)return false;
        seen[idx]=n;
        n=getNext(n);
    }
    return true;
}