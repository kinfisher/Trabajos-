#include <iostream>
#include <vector>
using namespace std;

template<class T>
class nodo
{
public:
    int x;
    int y;
    T dato;
    nodo<T> *dir[2];
    nodo(){}
    nodo(int xx,int yy,T dat)
    {
        x=xx;
        y=yy;
        dato=dat;
        dir[0]=NULL;//derecha
        dir[1]=NULL;//abajo
    }
};


template<class T>
class matriz;

template <class T>
class traits
{
    public:
        int p_x;
        int p_y;
        matriz<T> *p_matriz;
        traits(int x,int y,matriz<T>*ptr){
            p_x=x;
            p_y=y;
            p_matriz=ptr;
        }
        T operator =(T x)
        {
            return p_matriz->insert(p_x,p_y,x);
        }
        operator T();
};

template<class T>
traits<T>::operator T()
{
    nodo<T> **p,**q;
    if (p_matriz->find_x(p_x, p, p_matriz->columna[p_y],1) && p_matriz->find_y(p_y,q,p_matriz->fila[p_x],0) );
        return (*p)->dato;
}

template<class T>
class matriz
{
    public:
        vector<nodo<T>*> columna;
        vector<nodo<T>*> fila;
        nodo<T> *m_head;
        int m_x;
        int m_y;
        int element_null=0;
        matriz *m_ptr;
        matriz(int,int);
        bool find_x(T,nodo<T>**&,nodo<T>*&,bool);
        bool find_y(T,nodo<T>**&,nodo<T>*&,bool);
        bool find_N(nodo<T>**&,nodo<T>*&);
        bool insert(int,int,T);
        bool insert_columna_fila(int,int,T);
        void find_e(T);
        traits<T> operator() (int x,int y)
        {
            return traits<T> (x,y,this) ;
        }
        void conv_lista();
        void imprimir();
};

template<class T>
matriz<T>::matriz(int x,int y)
{
    m_x=x;
    m_y=y;
    m_head=NULL;
    fila.resize(m_x);
    columna.resize(m_y);
    for(int i=0;i<m_x;i++)
    {
        fila[i]=NULL;
    }
    for(int i=0;i<m_y;i++)
    {
        columna[i]=NULL;
    }
}

template<class T>
bool matriz<T>::find_x(T x,nodo<T>**& p,nodo<T>*& head,bool dire){
    for(p=&head;(*p)&& (*p)->x <x; p=&((*p)->dir[dire])){}
    return (*p) &&(*p)->x==x;
}
template<class T>
bool matriz<T>::find_y(T x,nodo<T>**& p,nodo<T>*& head,bool dire){
    for(p=&head;(*p)&& (*p)->y <x; p=&((*p)->dir[dire])){}
    return (*p) &&(*p)->y==x;
}
template<class T>
bool matriz<T>::find_N(nodo<T>**& p,nodo<T>*& head){
    for(p=&head;(*p); p=&((*p)->dir[0])){}
    return (*p);
}

template<class T>
void matriz<T>::find_e(T x){
    nodo<T> **p;
    for(int i=0;i<fila.size();i++){
        for(int j=0;j<columna.size();j++){
            if(find_x(i,p,columna[j],1)){
                if((*p)->dato==x){
                        cout<<"coordenada x: "<<(*p)->x;
                cout<<"coordenada y: "<<(*p)->y;
                cout<<endl;}
            }

        }
        cout<<endl;
    }
}


template<class T>
bool matriz<T>::insert(int x,int y,T dat){
    nodo<T>**p,**q;
    cout<<"COORDENADA X INGRESADA: "<<x<<endl;
    cout<<"COORDENADA Y INGRESADA: "<<y<<endl;
    cout<<"DATO PARA INGRESAR: "<<dat<<endl;
    cout<<"PRIMERA COMPROBACION X "<<find_x(x,p,columna[y],1)<<endl;
    cout<<"PRIMERA COMPROBACION Y "<<find_y(y,q,fila[x],0)<<endl;
    if(find_x(x,p,columna[y],1)&&find_y(y,q,fila[x],0))
    {
        cout<<"ENTRO"<<endl;
        if(dat==element_null)
        {
            nodo<T>*tmp_x;
            nodo<T>*tmp_y;
            tmp_x=(*p)->dir[1];
            tmp_y=(*q)->dir[0];
            delete *p;
            *p=tmp_x;
            *q=tmp_y;
        }
        else
        {
            (*p)->dato=dat;
        }
    }
    else
    {
        insert_columna_fila(x,y,dat);
    }
    return 1;
}

template<class T>
bool matriz<T>::insert_columna_fila(int x,int y,T dato)
{
    nodo<T> **p,**q;
    cout<<"SEGUNDA COMPROBACION X "<<find_x(x,p,columna[y],1)<<endl;
    cout<<"SEGUNDA COMPROBACION Y "<<find_y(y,q,fila[x],0)<<endl;
    if(find_x(x,p,columna[y],1)&&find_y(y,q,fila[x],0))
    {
        return 0;
    }
    nodo<T> *w=new nodo<T>(x,y,dato);
    w->dir[0]=*q;
    w->dir[1]=*p;
    *p=w;
    *q=w;
    return 1;
}

template<class T>
void matriz<T>::imprimir(){
    nodo<T> **p;
    for(int i=0;i<fila.size();i++){
        for(int j=0;j<columna.size();j++){
            if(find_x(i,p,columna[j],1)){
                cout<<(*p)->dato<<" ";
            }
            else{
                cout<<"* ";
            }
        }
        cout<<endl;
    }
}

template<class T>
void matriz<T>::conv_lista(){
    nodo<T> **p;
    m_head=fila[0];
    for(int i=0;i<m_x-1;i++){
        find_N(p,fila[i]);
        *p=fila[i+1];
    }
    columna.clear();
    fila.clear();
    nodo<T>*aux=m_head;
    while(aux!=NULL){
    cout<<"->"<<aux->dato;
    aux=aux->dir[0];
    }
    cout<<endl;

}
int main()
{
    int a;
    matriz<int> mat(3,3);

    mat(0,0)=1;
    mat.imprimir();
    mat(0,1)=2;
     mat(0,2)=3;
     mat(1,0)=mat(0,0);
     mat(1,1)=5;
    mat(1,2)=6;
    mat(2,0)=7;
    mat(2,1)=8;
     mat(2,2)=9;
    mat.imprimir();


    //mat.find_e(7);
   // mat.conv_lista();
}
