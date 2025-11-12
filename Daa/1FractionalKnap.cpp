#include <iostream>
using namespace std;

struct arr{
    double weight;
    double value;
    double ratio;
};

int main(){
    double profit=0;
    double capacity;
    
    cout<<"Enter the maximum capacity of knapsack: ";
    cin>>capacity;
    cout<<"Enter the total number of items: ";
    int n;
    cin>>n;
    arr a[n];
    
    for(int i=0;i<n;i++){
        cout<<"Enter the value of item "<<i+1<<":";
        cin>>a[i].value;
        cout<<"Enter the weight of item "<<i+1<<":";
        cin>>a[i].weight;
        a[i].ratio=(a[i].value/a[i].weight);
        
    }
    
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(a[j].ratio<a[j+1].ratio){
                swap(a[j],a[j+1]);
            }
        }
    }
    
    for(int i=0;i<n;i++){
        if(a[i].weight<=capacity){
            capacity-=a[i].weight;
            profit+=a[i].value;
        }
        else{
            profit+=(capacity/a[i].weight)*a[i].value;
        }
    }
    
    cout<<"MAX PROFIT: "<<profit;
    }