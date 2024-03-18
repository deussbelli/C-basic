#include<iostream>
using namespace std;

struct Node {
    friend class TreeAVL;
    int key;
    struct Node* left;
    struct Node* right;
    int height;
}*base;

class TreeAVL {
public:

    int max(int x, int y);
    int height(Node* N);
    bool isEmpty();
    static Node* newNode(int key);
    void Print(Node* ptr, int level);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int getBalance(Node* N);
    Node* insert(Node* node, int key);
    static Node* minValueNode(Node* node);
    Node* deleteNode(Node* base, int key);
    void preOrder(Node* base);
    void postOrder(Node* base);
    void inOrder(Node* base);
    bool search(int);
    void printHelper(Node* base, string indent, bool last);
    void printWithBalance(Node* base);
    TreeAVL() {
        base = nullptr;
    }
};

int TreeAVL::height(Node* N) {
    if (N == nullptr)
        return -1;
    else {
        int left_height = height(N->left);
        int right_height = height(N->right);
        if (left_height > right_height)
            return (left_height + 1);
        else return (right_height + 1);
    }
}

bool TreeAVL::isEmpty() {
    if (base == nullptr)
        return true;
    else
        return false;
}

int TreeAVL::getBalance(Node* N) {
    if (N == nullptr)
        return -1;
    return height(N->left) - height(N->right);
}

Node* TreeAVL::rightRotate(Node* y) 
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* TreeAVL::leftRotate(Node* x) 
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

Node* TreeAVL::newNode(int key) 

{
    auto* node = (struct Node*)
        malloc(sizeof(struct Node));
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 0; 
    return(node);
}

Node* TreeAVL::insert(Node* N, int key)
{

    if (N == nullptr)
        return(newNode(key));
    if (key < N->key)
        N->left = insert(N->left, key);
    else if (key > N->key)
        N->right = insert(N->right, key);
    else {
        cout << "No duplicate values allowed!" << endl;
        return N;
    }

    N->height = max(height(N->left), height(N->right)) + 1;
    int balance = getBalance(N);  


    if (balance > 1 && key < N->left->key)
        return rightRotate(N);

    if (balance < -1 && key > N->right->key) 
        return leftRotate(N);

    if (balance > 1 && key > N->left->key)  
    {
        N->left = leftRotate(N->left);
        return rightRotate(N);
    }

    if (balance < -1 && key < N->right->key)
    {
        N->right = rightRotate(N->right);
        return leftRotate(N);
    }

    return N;
}

Node* TreeAVL::minValueNode(Node* N) 
{
    Node* current = N;

    while (current->left != nullptr)
        current = current->left;
    return current;
}

int TreeAVL::max(int x, int y) 
{
    return (x > y) ? x : y;
}

Node* TreeAVL::deleteNode(Node* base, int key) 
{

    if (base == nullptr)
        return base;
    if (key < base->key) 
        base->left = deleteNode(base->left, key);
    else if (key > base->key) 
        base->right = deleteNode(base->right, key);

    else
    {   
        if ((base->left == nullptr) || (base->right == nullptr))
        {
            Node* temp = base->left ? base->left : base->right;
            if (temp == nullptr)
            {
                temp = base;
                base = nullptr;
            }
            else 
            {
                *base = *temp;
            }
            free(temp);
        }
        else
        {  
            struct Node* temp = minValueNode(base->right);

            base->key = temp->key;

            base->right = deleteNode(base->right, temp->key);
        }
    }
    if (base == nullptr)  
        return base;

    int balance = getBalance(base);
   
    if (balance == 2 && getBalance(base->left) >= 0) 
        return rightRotate(base);
    if (balance == 2 && getBalance(base->left) == -1)   
    {
        base->left = leftRotate(base->left);
        return rightRotate(base);
    }
    if (balance == -2 && getBalance(base->right) <= 0) 
        return leftRotate(base);
    if (balance == -2 && getBalance(base->right) == 1)   
    {
        base->right = rightRotate(base->right);
        return leftRotate(base);
    }
    return base;
}

bool TreeAVL::search(int key) 
{
    Node* temp = base, * parent = base;
    if (temp == nullptr) {
        cout << "\nThe AVL Tree is empty\n" << endl;
        return false;
    }
    else
    {
        while (temp != nullptr && temp->key != key)
        {
            parent = temp;
            if (temp->key < key)
                temp = temp->right;
            else
                temp = temp->left;
        }
    }

    if (temp == nullptr)
        cout << "This element is NOT present in the tree!";
    else
        cout << "\n" << "'" << key << "'" << " element is present in the tree! " << "\nIt's height is: " << temp->height << endl;
    return true;
}

void TreeAVL::Print(Node* ptr, int level) 
{
    int i;
    if (ptr != nullptr)
    {
        Print(ptr->right, level + 1);
        printf("\n");
        if (ptr == base)
            cout << "Root -> ";
        for (i = 0; i < level && ptr != base; i++)
            cout << "        ";
        cout << ptr->key;
        Print(ptr->left, level + 1);
    }
}

void TreeAVL::preOrder(Node* base) 
{
    if (base != nullptr)
    {
        printf("%d ", base->key);
        preOrder(base->left);
        preOrder(base->right);
    }
}

void TreeAVL::postOrder(Node* base) 
{
    if (base != nullptr)
    {
        postOrder(base->left);
        postOrder(base->right);
        printf("%d ", base->key);
    }
}

void TreeAVL::inOrder(Node* base) 
{
    if (base != nullptr)
    {
        inOrder(base->left);
        printf("%d ", base->key);
        inOrder(base->right);
    }
}

void TreeAVL::printHelper(Node* base, string indent, bool last)
{

    if (base != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "     ";
        }
        else {
            cout << "L----";
            indent += "|    ";
        }

        cout << base->key << "( BF = " << getBalance(base) << ")" << endl;

        printHelper(base->left, indent, false);
        printHelper(base->right, indent, true);
    }
}

void TreeAVL::printWithBalance(Node* base)
{
    Node* temp = base;
    printHelper(temp, "", true);
}

void Destroy(Node* base) 
{
    if (base == nullptr) return;
    Destroy(base->left);
    Destroy(base->right);

    delete base;
}

int main() {
    TreeAVL avl;
    base = avl.insert(base, 10);
    base = avl.insert(base, 20);
    base = avl.insert(base, 30);
    base = avl.insert(base, 40);
    base = avl.insert(base, 50);
    base = avl.insert(base, 25);
    avl.search(20);

    avl.Print(base, 1);
    cout << "\n****************" << endl;

    avl.printWithBalance(base);
    avl.deleteNode(base, 50);
    avl.deleteNode(base, 25);
    avl.deleteNode(base, 10);
    avl.Print(base, 1);
    cout << endl;
    cout << "****************" << endl;
    avl.inOrder(base);
    avl.search(20);
    Destroy(base);
    system("pause");
    return 0;
}