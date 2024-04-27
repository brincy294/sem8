#include <iostream>
#include <omp.h>
using namespace std;

int main(){
    int n;
    cout<<"Enter number of inputs: ";
    cin>>n;
    int arr[n];
    cout<<"Enter "<<n<<" integers: ";
    for (int i=0; i<n; ++i){
        cin>>arr[i];
    }

    int sum=0, min_val=arr[0], max_val=arr[0];

    #pragma omp parallel for reduction(+:sum)
    for (int i=0; i<n; i++){
        sum += arr[i];
    }

    double avg = sum / static_cast<double>(n);

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val)
    for (int i=0; i<n; i++){
        if (min_val > arr[i]) min_val = arr[i];
        if (max_val < arr[i]) max_val = arr[i];
    }

    cout<<"\nSum: "<<sum;
    cout<<"\nAverage: "<<avg;
    cout<<"\nMin value: "<<min_val;
    cout<<"\nMax value: "<<max_val;
}