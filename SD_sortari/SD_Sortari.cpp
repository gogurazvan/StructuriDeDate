#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
vector <int> v;
int n,maxim;

void generator(int n, int r_min, int r_max){
    v.clear();
    int x;
    for(int i=0;i<n;++i){
        x=rand()%(r_max+1)+r_min;
        v.push_back(x);
        if(x>maxim)
            maxim=x;
    }
}
void verificator(){

    bool sortat=1;

    for(int i=0; i<n-1; ++i)
        if(v[i]>v[i+1]) sortat=0;

    if(sortat!=0) cout<<"sortat";
    else cout<<"nesortat";
    cout<<"\n\n";
    v.clear();
}

void bubbleSort(){
    int sortat=0,j=n;

    while( sortat==0 ){

        sortat=1;
        for(int i=0;i<j-1;++i)
            if(v[i]>v[i+1]){
                swap(v[i],v[i+1]);
                sortat=0;
            }
        j--;
    }
}

void countSort(int emax){

    if(emax>999999){
        cout<<"nu se poate folosi aceasta sortare";
        return;
    }
    vector <int> contor(emax+1);

    for(int i=0; i<n; ++i)
        contor[v[i]]++;
    int j=0;
    for(int i=0; i<=emax; ++i)
        while(contor[i]>0){
            v[j]=i;
            j++;
            contor[i]--;
        }
    contor.clear();
}

void mergeSort(int capS, int capD){
    if(capS<capD){

        int mij=capS+ (capD-capS)/2;
        mergeSort(capS,mij);
        mergeSort(mij+1,capD);
        vector <int> interclasare;
        int k1=capS, k2=mij+1, j=0;
        while(k1<=mij && k2<=capD)
            if(v[k1]<=v[k2]){
                interclasare.push_back(v[k1]);
                k1++;
            }else{
                interclasare.push_back(v[k2]);
                k2++;
            }

        while(k1<=mij){
            interclasare.push_back(v[k1]);
            k1++;
        }
        while(k2<=capD){
            interclasare.push_back(v[k2]);
            k2++;
        }

        for(int i=capS; i<=capD; ++i)
            v[i]=interclasare[i-capS];
        interclasare.clear();
    }
}

int pivFind(int a1, int a2, int a3){
    if ((a1>a2) xor (a1>a3))
        return a1;
    else if ((a2<a1) xor (a2<a3))
            return a2;
        else
            return a3;
}
void quickSort(int capS, int capD){
    int i = capS, j = capD;
    int aux;
    int pivot = pivFind(v[capS],v[(capS+capD)/2],v[capD]);
    while (i <= j)
    {
        while (v[i] < pivot)
            i++;
        while (v[j] > pivot)
            j--;

        if (i <= j)
        {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    }

    if (capS < j)
        quickSort(capS, j);

    if (i < capD)
        quickSort(i, capD);
}

findExp(int x){
    int ep=1;
    while(x/ep >=10 )
        ep*=10;
    return ep;
}
subCount(int s,int d, int cif,int a[10]){
    int frq[10]={ 0 };
    for(int i=s;i<=d;++i)
        frq[(v[i]/cif)%10]++;
    a[0]=frq[0]+s-1;
    for(int i=1; i<=9;++i){
        frq[i]+=frq[i-1];
        a[i]=frq[i]+s-1;
    }
    vector <int> sortat(d-s+1);
    for(int i=d;i>=s;--i){
        sortat[frq[(v[i]/cif)%10]-1]=v[i];
        frq[(v[i]/cif)%10]--;
    }
    for(int i=s;i<=d;++i)
        v[i]=sortat[i-s];
    sortat.clear();
}
void radixSort(int capS, int capD,int exp){
    if(exp==0)
        return;
    int sep[10];
    subCount(capS,capD,exp,sep);
    if(sep[0]-capS+1>2)
        radixSort(capS,sep[0],exp/10);
    if(sep[0]-capS+1==2)
        if(v[sep[0]-1]>v[sep[0]])
            swap(v[sep[0]-1],v[sep[0]]);

    for(int i=1;i<=9;++i){
        if(sep[i]-sep[i-1]>2)
            radixSort(sep[i-1]+1,sep[i],exp/10);
        if(sep[i]-sep[i-1]==2)
            if(v[sep[i]-1]>v[sep[i]])
                swap(v[sep[i]-1],v[sep[i]]);
    }
}
int main()
{
    int T;
    ifstream in("date.in");
    in>>T;
    srand(time(NULL));
    for(int k=1;k<=T;++k){
        int M;
        in>>n>>M;
        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);

        if(n<=100005){
        generator(n,0,M);
        start = high_resolution_clock::now();
        bubbleSort();
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout <<"Bubble Sort: "<< duration.count()<<" nanosecunde\n";
        verificator();
        }else cout<<"BubbleSort prea ineficient\n\n";

        if(M<=1000000){
        generator(n,0,M);
        start = high_resolution_clock::now();
        countSort(maxim);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout <<"Count Sort: "<< duration.count()<<" nanosecunde\n";
        verificator();
        }else cout<<"Elementele din sir prea mari pentru CountSort\n\n";

        if(n<=10000001){
        generator(n,0,M);
        start = high_resolution_clock::now();
        mergeSort(0,n-1);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout <<"Merge Sort: "<< duration.count()<<" nanosecunde\n";
        verificator();
        }else cout<<"MergeSort prea ineficient\n\n";

        generator(n,0,M);
        start = high_resolution_clock::now();
        quickSort(0,n-1);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout <<"Quick Sort: "<< duration.count()<<" nanosecunde\n";
        verificator();

        generator(n,0,M);
        start = high_resolution_clock::now();
        radixSort(0,n-1,findExp(maxim));
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout <<"Radix Sort: "<< duration.count()<<" nanosecunde\n";
        verificator();

        generator(n,0,M);
        start = high_resolution_clock::now();
        sort(v.begin(),v.end());
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout <<"StlSort: "<< duration.count()<<" nanosecunde\n";
        verificator();

        cout<<"\n";
    }
    in.close();
    v.clear();
    return 0;
}
