#include<bits/stdc++.h>
using namespace std;

//Insert, delete min, build, merge]
struct nod{

    int val,ord;
    nod* copil[22];

    nod(int x)
    {
        this->val = x;
        this->ord=1;
        for(int i=0;i<22;++i){
            this->copil[i]=NULL;
        }
    }
};
class Heap{

public:
 nod* rad[22];



    void mover(int i){
        while(this->rad[i+1]!=NULL && i<20){

            if( this->rad[i+1]->val < this->rad[i]->val )
                swap( this->rad[i], this->rad[i+1] );

            this->rad[i+1]->copil[i+1] = this->rad[i];
            this->rad[i+1]->ord+=1;

            this->rad[i]=NULL;

            i=i+1;


        }

        this->rad[i+1] = this->rad[i];
        this->rad[i]=NULL;

    }


    void mergeH(Heap &h){

        for( int i=1; i<20; ++i){
            if(h.rad[i]!=NULL){

                nod* r;
                r=h.rad[i];


                if(rad[i]==NULL){
                    this->rad[i]=r;
                }
                else{

                    if( this->rad[i]->val < r->val )
                        swap (r,this->rad[i]);

                    rad[i]->copil[i]=r;
                    rad[i]->ord++;

                    mover(i);

                }
            }
            h.rad[i]=NULL;
        }

    }

    void insertH(int x){

        nod* r=new nod(x);

        if(rad[1]==NULL){
            rad[1]=r;
        }
        else{

            if( rad[1]->val < r->val )
                swap (r,rad[1]);

            rad[1]->copil[1]=r;
            rad[1]->ord++;

            mover(1);
        }

    }


    int delmaxH(){

        int maxi=0,poz=0;

        for(int i=1; i<20; ++i){
            if(rad[i]!=NULL){
                if(rad[i]->val>maxi){
                    maxi=rad[i]->val;
                    poz=i;
                }
            }
        }
        if(poz==0) return 0;

        nod* r;
        r=rad[poz];

        int m=r->ord;
        rad[poz]=NULL;

        for(int i=1; i<m; ++i){
            if(rad[i]==NULL){
                rad[i] = r->copil[i];
            }
            else{

                if( rad[i]->val < r->copil[i]->val )
                    swap (r->copil[i],rad[i]);

                rad[i]->copil[i]=r->copil[i];
                rad[i]->ord++;

                mover(i);

            }
        }

        delete r;

        return maxi;

    }
/*
    void DFSterg( nod* p ){
        for(int i=1; i<20; ++i){
            if(p->copil[i]!=NULL){
                DFSterg(p->copil[i]);
            }
        }
        delete p;
    }
*/


    Heap(){
        for(int i=0;i<22;++i){
            rad[i]=NULL;
        }
    }
/*
    ~Heap(){
        for ( int i=1; i<21; ++i ){
             if( rad[i] != NULL ){
                DFSterg( rad[ i ] );
             }
{1}
        }
    }
{1}
*/
};





int main(){
    int n, q, com,j;
    ifstream in("mergeheap.in");
    ofstream out("mergeheap.out");
    in>>n>>q;
    Heap v[n+1];
    for( int i=0; i<q; ++i){
        in>>com>>j;
        j=j-1;
        if(com==1){
            int x;
            in>>x;
            v[j].insertH(x);
        }
        if(com==2){
            out<<v[j].delmaxH()<<"\n";
        }
        if(com==3){
            int x;
            in>>x;
            x=x-1;
            v[j].mergeH(v[x]);
        }

    }

    return 0;
}
