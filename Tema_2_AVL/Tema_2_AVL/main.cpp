#include <iostream>

using namespace std;

int flag=0;
struct node
{
    int key;
    struct node* left;
    struct node* right;
    int height;
}*root;

class avl
{
    public:
           int max(int a, int b);
           int height(struct node *N);
           node* newNode(int key);
           node* Rrotate(struct node *y);
           node* Lrotate(struct node *x);
           int getBalance(struct node *N);
           struct node* insert(struct node* node, int key);
           struct node* minValNode(struct node* node);
           struct node* deleteNode(struct node* root, int key);
           void preOrder(struct node* root);
           void postOrder(struct node* root);
           void inOrder(struct node* root);
           void cautare(int);
        avl()
        {
            root = NULL;
        }
};

void avl::cautare(int key)

{
     node *temp = root,*parent = root;
    if(temp==NULL)
        cout<<"\nAVL Gol."<<endl;
    else
    {
        while(temp!=NULL && temp->key!=key)
        {
            parent=temp;
            if(temp->key<key)
            {
                temp=temp->right;
            }
            else
            {
                temp=temp->left;
            }
        }
    }

    if(temp==NULL)
        cout<<"Elementul dat nu se afla in AVL.";
    else
        {cout<<"\nElementul dat exista in AVL.";
        cout<<"\nElemntul are inaltimea : "<<temp->height;
        }

}

int avl::max(int a, int b)///maximul dintre 2 valori
{
    if (a>b)
        return a;
    return b;
}

int avl::height(struct node *N)///extrage inaltimea arborelui
{
    if (N == NULL)
        return 0;
    return N->height;
}

struct node* avl::newNode(int key)
{
    struct node* node = (struct node*)
                        new(struct node);
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;///nodul se adauga ca si frunza initial
    return(node);
}

///rotatie la dreapta
struct node* avl::Rrotate(struct node* y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

///rotatie la stanga
struct node* avl::Lrotate(struct node* x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    return y;
}

///functie de gasit cum se potriveste un element
int avl::getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
struct node* avl::insert(struct node* node, int key)
{
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    ///schimbam inaltimea
    node->height = max(height(node->left), height(node->right)) + 1;
    ///verificam daca isi pastreaza proprietatile de AVL
    int balance = getBalance(node);
    /// 1. Left Left
    if (balance > 1 && key < node->left->key)
        return Rrotate(node);
    /// 2. Right Right
    if (balance < -1 && key > node->right->key)
        return Lrotate(node);
    /// 3. Left Right
    if (balance > 1 && key > node->left->key)
    {
        node->left =  Lrotate(node->left);
        return Rrotate(node);
    }
    /// 4. Right Left
    if (balance < -1 && key < node->right->key)
    {
        node->right = Rrotate(node->right);
        return Lrotate(node);
    }
    return node;
}
///Returnez nodul cu cheia minima nevida
struct node * avl::minValNode(struct node* node)
{
    struct node* current = node;
    ///caut frunza cea mai din stanga
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct node* avl::deleteNode(struct node* root, int key)
{
    if (root == NULL)
        return root;
    ///Daca valoarea dorita sa fie stearsa este mai mica decat radacina, atunci aceasta se afla in STANGA
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    ///Daca valoarea dorita sa fie stearsa este mai mare decat radacina, atunci aceasta se afla in DREAPTA
    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    ///Altfel, este chiar radacina
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {   struct node *temp = root->left ? root->left : root->right;
            flag=1;
            ///nod fara copii
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
                flag=1;
            }
            else ///nod care are copii
             {*root = *temp;flag=1;}///copiez pentru un copil cu date
        delete temp;
        }
        else
        {
            struct node* temp = minValNode(root->right);
            ///Copiem succesorul
            root->key = temp->key;
            ///Sterge succesorul
            root->right = deleteNode(root->right, temp->key);
        }
    }
    ///Daca are doar 1 nod se termina
    if (root == NULL)
      return root;
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);///verificam daca isi pastreaza proprietatile de AVL

    /// 1. Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return Rrotate(root);

    /// 2. Left Right
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  Lrotate(root->left);
        return Rrotate(root);
    }

    /// 3.Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return Lrotate(root);

    /// 4. Right Left
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = Rrotate(root->right);
        return Lrotate(root);
    }

    return root;
}

void avl::preOrder(struct node *root)
{
    if(root != NULL)
    {
        cout<<root->key;
        preOrder(root->left);
        preOrder(root->right);
    }
}

void avl::postOrder(struct node *root)
{
    if(root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        cout<<root->key;
    }
}

void avl::inOrder(struct node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        cout<<root->key;
        inOrder(root->right);
    }
}

int main()
{
    int option, item;
    avl avl;
    while (true)
    {
        cout<<"\n\n==============================================="<<endl;
        cout<<"\t       Meniu pentru AVL              "<<endl;
        cout<<"==============================================="<<endl;
        cout<<'\n';
        cout<<"1. Introdu valoarea in AVL"<<endl;
        cout<<"2. Cauta un element in AVL"<<endl;
        cout<<"3. Sterge valoare de AVL"<<endl;
        cout<<"4. SVD (Stanga - Varf - Dreapta)"<<endl;
        cout<<"5. VSD (Varf - Stanga - Dreapta)"<<endl;
        cout<<"6. SDV (Dreapta - Stanga - Varf)"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"\nAlege optiunea dorita: ";
        cin>>option;
        cout<<"\n";
        switch(option)
        {
        case 1:
            cout<<"Ce valoare sa fie introdusa: ";
            cin>>item;
            root = avl.insert(root, item);
            break;
        case 2:cout<<"\nCauta elementul: ";
                cin>>item;
                avl.cautare(item);
                break;
        case 3: cout<<"\nIntrodu ce valoare sa fie stearsa: ";
             cin>>item;
             root = avl.deleteNode(root, item);
             if(flag==0)
                        cout<<"\nAcest element nu exista in AVL.";
             else
                 cout<<"\nGata! Am sters elementul.";
             break;
        case 4:
            cout<<"SVD (Stanga - Varf - Dreapta):"<<endl;
            avl.inOrder(root);
            cout<<endl;
            break;
        case 5:
            cout<<"VSD (Varf - Stanga - Dreapta):"<<endl;
            avl.preOrder(root);
            cout<<endl;
            break;
        case 6:
            cout<<"SDV (Dreapta - Stanga - Varf):"<<endl;
            avl.postOrder(root);
            cout<<endl;
            break;
        case 0:return 0;
            break;
        default:
            cout<<"\nNu ai introdus o optiune valida."<<endl;
        }
    }
}

