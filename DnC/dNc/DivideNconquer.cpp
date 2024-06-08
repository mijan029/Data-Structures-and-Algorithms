#include<iostream>
#include<ctime>
#include<algorithm>
#include<fstream>

using namespace std;


void mergesort(int *arr, int l, int r)
{
    if(l>=r) return;
    int m=(l+r)>>1;
    mergesort(arr,l,m);
    mergesort(arr,m+1,r);

    int suparr[r-l+1]={0};
    for(int i=l,j=m+1, k=0; i<=m || j<=r; k++){
        int x,y;
        x=y=INT_MAX;
        if(i<=m) x=arr[i];
        if(j<=r) y=arr[j];
        if(x<=y){
            suparr[k]=x;
            i++;
        }
        else{
            suparr[k]=y;
            j++;
        }
    }
    for(int i=0; i<r-l+1; i++)
        arr[l+i]=suparr[i];
}


int findk(int *arr, int l, int r)
{
    int i=l;
    for(int j=l; j<r; j++){
        if(arr[j]<=arr[r]) swap(arr[i],arr[j]);
        if(arr[i]<=arr[r]) i++;
    }
    swap(arr[i],arr[r]);
    return i;
}
void quicksort(int *arr, int l, int r)
{
    if(l>=r) return;
    int k = findk(arr,l,r);
    quicksort(arr,l,k-1);
    quicksort(arr,k+1,r);
}


void randomizedquicksort(int *arr, int l, int r)
{
    if(l>=r) return;
    int pivot = l+rand()%(r-l+1);
    swap(arr[pivot],arr[r]);
    int k = findk(arr,l,r);
    randomizedquicksort(arr,l,k-1);
    randomizedquicksort(arr,k+1,r);
}


void insertionsort(int *arr, int l, int r)
{
    for(int i=l; i<=r; i++){
        int j=i;
        while(j>l){
            if(arr[j]<arr[j-1]){
                swap(arr[j],arr[j-1]);
                j--;
            }
            else break;
        }
    }
}
int main()
{
    int N[]={5, 10, 100, 1000, 10000, 100000};

    int n=N[5];
    int arr[N[5]], input[N[5]];
    srand(clock());
    for(int i=0; i<n; i++)
        input[i] = rand();

    for(int i=0; i<n; i++)
        arr[i] = input[i];
    clock_t time_of_mergesort = clock();
    mergesort(arr,0,n-1);
    cout<<"merge sort takes "<<float(clock()-time_of_mergesort)/CLOCKS_PER_SEC<<"s"<<endl;


    for(int i=0; i<n; i++)
        arr[i] = input[i];
    clock_t time_of_quicksort = clock();
    quicksort(arr,0,n-1);
    cout<<"quick sort takes "<<float(clock()-time_of_quicksort)/CLOCKS_PER_SEC<<"s"<<endl;


    for(int i=0; i<n; i++)
        arr[i] = input[i];
    clock_t time_of_randomquicksort = clock();
    randomizedquicksort(arr,0,n-1);
    cout<<"randomized quick sort takes "<<float(clock()-time_of_randomquicksort)/CLOCKS_PER_SEC<<"s"<<endl;

    for(int i=0; i<n; i++)
        arr[i] = input[i];
    clock_t time_of_insertionsort = clock();
    insertionsort(arr,0,n-1);
    cout<<"insertion sort takes "<<float(clock()-time_of_insertionsort)/CLOCKS_PER_SEC<<"s"<<endl;

    clock_t time_of_quicksort1 = clock();
    quicksort(arr,0,n-1);
    cout<<"quick sort in sorted array takes "<<float(clock()-time_of_quicksort1)/CLOCKS_PER_SEC<<"s"<<endl;


    clock_t time_of_randomquicksort1 = clock();
    randomizedquicksort(arr,0,n-1);
    cout<<"randomized quick sort in sorted array takes "<<float(clock()-time_of_randomquicksort1)/CLOCKS_PER_SEC<<"s"<<endl;


    for(int i=0; i<n; i++)
        arr[i] = input[i];
    clock_t time_of_sort = clock();
    sort(arr,arr+n);
    cout<<"STL sort takes "<<float(clock()-time_of_sort)/CLOCKS_PER_SEC<<"s"<<endl;


    ofstream myfile("divideNconquer.csv");
    myfile<<"Time required in ms"<<endl;
    myfile<<"n"<<","<<"Merge Sort"<<","<<"Quicksort"<<","<<"Randomized Quicksort"<<","<<"Insertion Sort"<<","<<"Quicksort with Sorted Input"<<","<<"Randomized Quicksort with Sorted Input"<<","<<"STL sort() function"<<endl;
    for(int j=0; j<6; j++){
        float tmerge=0,tquick=0,trquick=0,tinsertion=0,tsquick=0,trsquick=0,tstl=0;
        int t=20;
        n = N[j];
        for(int i=0; i<n; i++)
            input[i] = rand();
        while(t--){
            for(int i=0; i<n; i++)
                arr[i] = input[i];
            clock_t time_of_mergesort = clock();
            mergesort(arr,0,n-1);
            tmerge+=float(clock()-time_of_mergesort)/CLOCKS_PER_SEC;


            for(int i=0; i<n; i++)
                arr[i] = input[i];
            clock_t time_of_quicksort = clock();
            quicksort(arr,0,n-1);
            tquick+=float(clock()-time_of_quicksort)/CLOCKS_PER_SEC;


            for(int i=0; i<n; i++)
                arr[i] = input[i];
            clock_t time_of_randomquicksort = clock();
            randomizedquicksort(arr,0,n-1);
            trquick+=float(clock()-time_of_randomquicksort)/CLOCKS_PER_SEC;

            for(int i=0; i<n; i++)
                arr[i] = input[i];
            clock_t time_of_insertionsort = clock();
            insertionsort(arr,0,n-1);
            tinsertion+=float(clock()-time_of_insertionsort)/CLOCKS_PER_SEC;

            clock_t time_of_quicksort1 = clock();
            quicksort(arr,0,n-1);
            tsquick+=float(clock()-time_of_quicksort1)/CLOCKS_PER_SEC;


            clock_t time_of_randomquicksort1 = clock();
            randomizedquicksort(arr,0,n-1);
            trsquick+=float(clock()-time_of_randomquicksort1)/CLOCKS_PER_SEC;


            for(int i=0; i<n; i++)
                arr[i] = input[i];
            clock_t time_of_sort = clock();
            sort(arr,arr+n);
            tstl+=float(clock()-time_of_sort)/CLOCKS_PER_SEC;
        }

        myfile<<n<<","<<50*tmerge<<","<<50*tquick<<","<<50*trquick<<","<<50*tinsertion<<","<<50*tsquick<<","<<50*trsquick<<","<<50*tstl<<endl;

    }
    myfile.close();
}
