template<class T>
class Cnodes
{
    public:
        Cnodes(T x);
        T m_data;
        Cnodes<T> *Prev_next[2];


};


template<class T>
 Cnodes<T>::Cnodes(T x)
{
    m_data=x;
    Prev_next[0]=Prev_next[1]=0;
}


/////arbol
template<class T>
struct Cgreater
{
    inline bool operator()(T a,T b)
    {
        return a>b;
    }

};
template<class T>
struct Cless
{
    inline bool operator()(T a,T b)
    {
        return a<b;
    }
};




template<class T,class C>
class Ctree
{
    public:
        Ctree();
        bool Buscar(T x,Cnodes<T>**&p);
        bool Insertar(T x);
        bool Eliminar(T x);
        virtual ~Ctree();
        Cnodes<T> **punt(Cnodes<T>**p);
        C comp;
        void Imprimir(Cnodes<T>*p);
        void imprimirMulti(string orden,Cnodes<T>*p);
        void convert();

        Cnodes<T>*m_root;
    private:
};

template<class T,class C>
Ctree<T,C>::Ctree()
{
    m_root=NULL;
}

template<class T,class C>
Ctree<T,C>::~Ctree()
{
    T x;
    while(m_root)
    {
        x=m_root->m_data;
        Eliminar(x);
    }
}



template<class T,class C>
bool Ctree<T,C>::Buscar(T x,Cnodes<T>**&p)
{
    for(p=&m_root;(*p) and (*p)->m_data!=x;p=&(*p)->Prev_next[comp((*p)->m_data,x)]);
    return !!*p;
}

template<class T,class C>
bool Ctree<T,C>::Insertar(T x)
{
    Cnodes<T>**p;
    if(Buscar(x,p))
        return 0;
    Cnodes<T>*nuevo=new Cnodes<T>(x);
    *p=nuevo;
    return 1;
}


template<class T,class C>
bool Ctree<T,C>::Eliminar(T x)
{
    Cnodes<T>**p;
    if(!Buscar(x,p))
        return 0;
    if((*p)->Prev_next[0]!=0 and (*p)->Prev_next[1]!=0)
    {
        Cnodes<T>**q=punt(p);
        (*p)->m_data=(*q)->m_data;
        p=q;
    }
    Cnodes<T>*w=*p;
    (*p)=(*p)->Prev_next[(*p)->Prev_next[1]!=0];
    delete w;
    return 1;
}

template<class T,class C>
Cnodes<T> ** Ctree<T,C>::punt(Cnodes<T>**p)
{
    p=&(*p)->Prev_next[0];
    while((*p)->Prev_next[1]!=NULL)
    {
        p=&(*p)->Prev_next[1];
    }
    return p;
}

template <class T,class C>
void Ctree<T,C>::Imprimir(Cnodes<T>*Pointer)
{
    if(Pointer)
    {
        Imprimir(Pointer->Prev_next[0]);
        cout<<Pointer->m_data<<"  ";
        Imprimir(Pointer->Prev_next[1]);
    }

}

template<class T,class C>
void Ctree<T,C>::imprimirMulti(string orden,Cnodes<T>*p)
{
    int estado = 0;
    while(estado<3)
    {
        if(orden[estado] == '1')
            cout << p->m_data << " ";
        else if(orden[estado] == '2' && p->Prev_next[1] )
            imprimirMulti(orden,p->Prev_next[1]);
        else if(orden[estado] == '3' && p->Prev_next[0])
            imprimirMulti(orden,p->Prev_next[0]);
        estado++;
    }
}

template<class T,class C>
void Ctree<T,C>::convert()
{
    Cnodes<T> *p = m_root;
    Cnodes<T> *q = m_root;
    while(p->Prev_next[1]) //fin se va alfinal de la derecha mientras exista
    {
        p = p->Prev_next[1];
    }
    while(q)
    {
        if(q->Prev_next[0]) //si existe el hijo izquierdo, p apunta al hijo izquierdo de q y q en su hijo izquirdo apunta a null
        {
            p->Prev_next[1] = q->Prev_next[0];
            q->Prev_next[0] = NULL;
            while(p->Prev_next[1]) //va hacia el final del hijo derecho
            {
                p = p->Prev_next[1];
            }
	    }
        q = q->Prev_next[1];//q avanza al siguiente
    }



}


/////main

int main()
{

    Ctree<int,Cless<int>> tree;
    tree.Insertar(45);
    tree.Insertar(22);
    tree.Insertar(3);
    tree.Insertar(6);
    tree.Insertar(89);
    tree.Insertar(42);
    tree.Eliminar(45);
    cout<<"arbol normal:";
    tree.Imprimir(tree.m_root);
    cout<<endl;
    cout<<"arbol convertido:";
    tree.convert();
    tree.Imprimir(tree.m_root);

}