#include <iostream>
#include <queue>  //��K���J leaf �M node
#include <string>  //�Ĥ��D�ݨϥ�
#include <bits/stdc++.h> //��L�禡�ݨD
using namespace std;

struct HuffNode //�ϥ� min heap �h��@
{
int data;
char symbol;
HuffNode *leftChild = nullptr;
HuffNode *rightChild = nullptr;
};

class MinHeap {
    public:
        MinHeap(); //initialize
        MinHeap(int); //constructor
        ~MinHeap();  //destructor
        bool IsEmpty();  //�P�_ heap �O���O�Ū�
        const HuffNode& Top();  //�C�L min heap �̤W�h���I
        void Push(const HuffNode&); //�s�W min heap ������
        void Pop(); //�R�� min heap ����
        void ChangeSize1D(HuffNode *a, const int oldSize, const int newSize); //�X�R min heap �j�p
        void print();//�C�L min heap
        int Level(); //�p�� heap tree ���h��
        void Huffman_element(int*,int); //�إ� HuffMan tree �� leaf �M node
        HuffNode* create_Huffman_tree(int); //�إ� Huffman tree
        string decode(HuffNode*,string); //decode
        HuffNode* newNode(int data, char symbol); // ���� copy constructor �\��
        int Max(int,int); //��j�p�A�f�t�p�� HuffMan tree level ��
        void preorder(HuffNode *root); //Preorder traversal
        void Inorder(HuffNode* root); //Inorder traversal
        int getHeight(HuffNode* root); //�o HuffMan tree ����
        bool isLeaf(HuffNode* root); //�P�_�O�_�� leaf
        void printEncode(int arr[], int n); //�L�X�U�^��r���� HuffMan code(��bgetCodes �̭�)
        void getCodes(HuffNode* root, int arr[], int top); //�إ߭^��r���� HuffMan code�A�æL�X
    private:
        HuffNode *heap; // element array�A�� HEAP
        HuffNode *tree; // Huffman tree
        queue<HuffNode*> itr1; //�Ȧs���Aleaf �M Node �Ѥp�ƨ�j
        int heapSize; // number of elements in heap
        int capacity; // size of the array heap
};

int main()
{
    string test;
    cout << "Input a string: " ;
    cin >> test;
    cout << endl;
    char *a = new char[test.length()];  //�Ȧs string ���
    int *b = new int[test.length()];    //�p�� freq ��
    for(int i = 0 ; i < test.length();i++)
        a[i] = test[i];
    for(int i = 0 ; i < test.length();i++)
        b[i] = 0;

    sort(a,a+test.length());  //�N��ƥѤj�ƨ�p
    char comp = a[0];
    int k = 0, j = 0;
    for(int i = 0 ; i < test.length();i++)  //�p��U��ƥX�{�� freq
    {
        if(comp == a[i])
            b[k] = b[k] + 1;
        else
        {
            comp = a[i];
            k++;
            b[k] = b[k] + 1;
        }
    }
    char *arr = new char[k+1];  //�إ߷s�Ŷ�(�٪Ŷ�)
    int *freq = new int[k+1];   //�إ߷s�Ŷ�(�٪Ŷ�)

    arr[0] = a[0];    //��ƥ�L�h
    for(int i = 0 ; i < test.length();i++)
    {
        if(arr[j] != a[i])
        {
            j++;
            arr[j] = a[i];
        }
    }

    for(int i = 0; i < k + 1;i++)  //��ƥ�L�h
        freq[i] = b[i];

    delete[]a;
    delete[]b;

    cout << "Your input size[int]: " << k + 1 << endl;
    cout << "Your input symbol[char]: " ;
    for(int i = 0; i < k + 1; i++)
        cout << arr[i] << " ";
    cout << endl;
    cout << "Your input frequency[int]: " ;
    for(int i = 0; i < k + 1; i++)
        cout << freq[i] << " ";
    cout << endl << "===============================================" << endl;
    MinHeap min_heap(k+1);
    // Initalize the leaf node
    for (int i = 0; i < k+1; i++)  //�N���� push �i�h
    {
        HuffNode leaf_node;
        leaf_node.data = freq[i];
        leaf_node.symbol = arr[i];
        leaf_node.leftChild = leaf_node.rightChild = nullptr;
        min_heap.Push(leaf_node);
    }

    min_heap.print();  // print min heap (�Ĥ@�D)
    min_heap.Huffman_element(freq,k+1);
    cout << "===============================================" << endl;
    HuffNode *temp = new HuffNode[1];
    temp = min_heap.create_Huffman_tree(k+1);
    cout << "Huffman Tree:" << endl;  //�ĤG�D
    cout << "Preorder: " ;
    min_heap.preorder(temp);
    cout << endl << "Inorder: ";
    min_heap.Inorder(temp);
    cout << endl << "Max Level: " << min_heap.getHeight(temp) << endl << "Number of node: " << 2*(k+1) - 1<< endl;
    cout << "===============================================" << endl;
    int code[min_heap.getHeight(temp)] = {0};
    int top = 0;
    min_heap.getCodes(temp,code,top);  //�ĤT�D
    cout << "===============================================" << endl;
    string decoder;
    cout << "Input sequence for decode: ";  //�ĥ|�D
    cin >> decoder;
    cout << endl;
    cout << "Decoded HuffMan Data:" << endl << min_heap.decode(temp,decoder) << endl << endl;
    cout << "===============================================" << endl;
    delete[]arr;
    delete[]freq;
    return 0;
}

MinHeap::MinHeap()  //��l��
{
    heapSize = 0;
    capacity = 10;
    heap = new HuffNode[capacity + 1]; //heap[0] ���Ӱ� Huffman tree
    heap[0].data = 0;
    heap[0].symbol = '$';
    heap[0].leftChild = nullptr;
    heap[0].rightChild = nullptr;
    tree = new HuffNode[capacity - 1];
    for(int j = 0; j < capacity - 1;j++)
    {
        tree[j].rightChild = nullptr;
        tree[j].leftChild = nullptr;
        tree[j].data = 0;
        tree[j].symbol = '$';
    }
}

MinHeap::MinHeap(int a)   //��l��
{
    heapSize = 0;
    capacity = a;
    heap = new HuffNode[capacity + 1];  //heap[0] ���Ӱ� Huffman tree
    heap[0].data = 0;
    heap[0].symbol = '$';
    heap[0].leftChild = nullptr;
    heap[0].rightChild = nullptr;
    tree = new HuffNode[capacity - 1];
    for(int j = 0; j < capacity - 1;j++)
    {
        tree[j].rightChild = nullptr;
        tree[j].leftChild = nullptr;
        tree[j].data = 0;
        tree[j].symbol = '$';
    }
}

MinHeap::~MinHeap()  //destructor
{
    delete[]heap;
    delete[]tree;
}

bool MinHeap::IsEmpty()  //�p�G heap �šAtrue
{
    if(heapSize == 0)
        return true;
    else
        return false;
}

const HuffNode& MinHeap::Top()
{
    return heap[1];
}

//�`���۽ҥ��� sample code
void MinHeap::Push(const HuffNode& a)
{
    if(heapSize == capacity)
    {
        ChangeSize1D(heap, capacity, 2*capacity);
        capacity *= 2;
    }

    int currentNode = ++heapSize;
    while(currentNode != 1 && heap[currentNode/2].data > a.data)  //�� recursive �T�O�ƧǬO min heap
    {
        heap[currentNode] = heap[currentNode/2]; //�p�G���l����`�I�j�A�n���洫��
        currentNode /= 2;    //�M��A���W����������A����̰_�l�����
    }
    heap[currentNode] = a;
}

//�`���۽ҥ��� sample code
void MinHeap::Pop()
{
    if(IsEmpty())
        cout << "���|�w�šA����A�R���F!" << endl;
    else
    {
        HuffNode lastE = heap[heapSize];
        heapSize--;
        int currentNode = 1; // ���
        int child = 2; // currentNode ���@�Ө�l�`�I

        while(child <= heapSize)
        {
            if(child < heapSize && heap[child].data > heap[child + 1].data)
                child++;
            if(lastE.data <= heap[child].data)
                break;

            heap[currentNode] = heap[child];
            currentNode = child;
            child*=2;
        }
        heap[currentNode] = lastE;
    }
}

//�إߤ@�� HuffMan pointer�A�X�W�j�p�M���ƽᤩ�L�h��A���^�h
void MinHeap::ChangeSize1D(HuffNode *a, const int oldSize, const int newSize)
{
    HuffNode *temp = new HuffNode[newSize + 1];

    for(int i = 1 ;i < oldSize;i++)
        temp[i] = a[i];

    delete[]a;
    a = temp;
}

void MinHeap::print()  //print HuffMan tree data�A�W�L 2 �����贫�U�@��C�L
{
    cout << "MinHeap Tree:" << endl;
    int k = 1;
    for(int i = 1; i < heapSize + 1; i++)
    {
        cout << heap[i].data << "__" ;
        if(k % 2 && k == i)
        {
            k = 2 * k + 1;
            cout << endl;
        }
    }
    cout << endl << "Max Level: " << Level() << endl;
}

int MinHeap::Level()    //�p�� heap �� level�AheapSize �P level ���Y 2^level + 1 = heapSize
{
    int i = 1;
    int k = 0;
    while(i <= heapSize)
    {
        i *= 2;
        k++;
    }
    return k - 1;
}

void MinHeap::Huffman_element(int *a, int b) // leaf + node �ƶq���� 2*heapSize - 1
{
    int *p = new int[2*b - 1]; // leaf + node �ƶq���� 2*heapSize - 1
    int *q = new int[b - 1];   // �O node data ��
    int temp = 0;
    int k = 0;
    int j = 1;
    for(int i = 0;i < b;i++)   //���s�� leaf data ��
        p[i] = a[i];

    sort(p,p + b);  //sort �Ѥp��j�A�o�˥i�H������ priority queue ���ʧ@
    for(int i = 0;i < b - 1;i++)  //�|�o�� heapSize - 1 �� node�A�G�� heapSize - 1 ��
    {
        temp = p[k] + p[k + 1];  //�N�̨�p���Ȭۥ[
        p[b + j - 1] = temp; //��ȩ�i�h
        q[j - 1] = temp; //�O node data ���
        sort(p,p + b + j); //���s�ƦC�L
        k = k + 2;
        j++;
    }

    MinHeap g(2*b - 1); //�إ�huffman tree �Ŷ��j�p
    for(int i = 1;i<b+1;i++)
        g.Push(heap[i]);

    HuffNode h;
    for(int i = 0;i < b - 1;i++)  //���� heap �t�� HuffMan Node
    {
        h.data = q[i];
        h.symbol = '$';
        g.Push(h);  //push node �i�h
    }

    int tmp1;
    char tmp2;
    for(int i = 2*b - 1; i > 0; i--)  //�� bubble sort�A�o�쪺 leaf / node freq �Ѥp��j
    {
        for(int j = 1; j <= i-1; j++)
        {
            if( g.heap[j].data > g.heap[j+1].data)
            {
                tmp1 = g.heap[j].data;
                tmp2 = g.heap[j].symbol;
                g.heap[j].data = g.heap[j+1].data;
                g.heap[j].symbol = g.heap[j+1].symbol;
                g.heap[j+1].data = tmp1;
                g.heap[j+1].symbol = tmp2;
            }
        }
    }

    for(int i = 1; i < 2*b; i++)   // NODE �� LEAF �Ѥp��j�A�Ȥ@�� NODE �Ʀb�e
        itr1.push(&g.heap[i]);     //push �� queue

    delete[]p;
    delete[]q;
}

HuffNode* MinHeap::create_Huffman_tree(int a)  //�إ� HuffMan tree�A�q�̩��h(tree level �ȳ̤j)�}�l��
{
    int i = 0;
    int k = 0; //���`�I��
    while(k < a - 2)  // Node �ƶq = heapSize - 2
    {
        if(itr1.front()->symbol != '$' && tree[i].rightChild == nullptr)  //�p�G queue �Ĥ@�Ӫ� symbol != '$'�A�S�{�bnode���k�l�� nullptr
        {
            tree[i].rightChild = newNode(itr1.front()->data,itr1.front()->symbol); //�⥦���k�l��
            itr1.pop();
        }
        else if(itr1.front()->symbol != '$' && tree[i].leftChild == nullptr)  //���l��P�z
        {
            tree[i].leftChild = newNode(itr1.front()->data,itr1.front()->symbol);
            itr1.pop();
            i++;  //���F�A����U�@�Ӹ`�I
        }
        else if(itr1.front()->symbol == '$' /*&& tree[i].data == 0*/)  //�p�G = '$' ��`�I�ϥ�
        {
            tree[k].data = itr1.front()->data;  //���V�`�I
            tree[k].symbol = itr1.front()->symbol;
            itr1.pop();
            if(tree[i].rightChild != nullptr) //�`�I���W���@�w�O�`�I
            {
                tree[i].leftChild = &tree[k];  //�k�`�I���F���V���`�I
                i++;
                if(i == a - 1) //���D�O�̫�@�ӡA�Y�� ROOT
                {
                    tree[i - 1].data = itr1.front()->data;
                    tree[i - 1].symbol = itr1.front()->symbol;
                    itr1.pop();
                }
            }
            else
                tree[i].rightChild = &tree[k]; //�Ϥ�

            k++;

        }
    }
    return &tree[a-2]; //�^�� ROOT
}

string MinHeap::decode(HuffNode *root,string s)  // ��J�@�s�ꪺ huffman codes
{
    string ans = "";
    HuffNode* curr = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '1')  //1 �N�����l��]
           curr = curr->leftChild;
        else  //�Ϥ�
           curr = curr->rightChild;

        // reached leaf node
        if (isLeaf(curr))
        {
            ans += curr->symbol;
            curr = root; //�M��q�Y�}�l
        }
    }
    // cout<<ans<<endl;
    return ans+'\0';
}

HuffNode* MinHeap::newNode(int data, char symbol)  //�����b�� copy constructor �\��
{
    HuffNode* temp = new HuffNode[1];

    temp->leftChild = nullptr;
    temp->rightChild = nullptr;
    temp->data = data;
    temp->symbol = symbol;

    return temp;
}

void MinHeap::preorder(HuffNode *root)
{
   //VLR-- visiting current node , go to leftChild(if not nullptr , leftChild = root node), then go to rightChild---->recursive
   if (root != nullptr) //�p�G�`�I���O nullptr
   {
      cout<<root->data<<" "; //���L�`�I
      preorder(root->leftChild); //���X leftChild
      preorder(root->rightChild); //�̫�b���X rightChild
   }
}

void MinHeap::Inorder(HuffNode *root)
{
    //LVR-- go to leftChild(if not nullptr , leftChild = root node), visiting current node , then go to rightChild---->recursive
    if (root != nullptr)
    {
        Inorder(root->leftChild);
        cout << root->data << " ";
        Inorder(root->rightChild);
    }
}

int MinHeap::Max(int a, int b)
{
    if(a >= b)
        return a;
    else
        return b;
}

int MinHeap::getHeight(HuffNode *root)
{
   if (isLeaf(root)) //�쩳��
         return 0;

   // �h�M��䥪�k�l�𪺲`��
   int lh = getHeight(root->leftChild);  //recursive
   int rh = getHeight(root->rightChild); //recursive

   return 1 + Max(lh,rh);
}

bool MinHeap::isLeaf(HuffNode* root) //�P�_�O���O leaf
{
    if(root->leftChild == nullptr && root->rightChild == nullptr)
        return 1;
    else
        return 0;
}

void MinHeap::printEncode(int arr[], int n)  //�C�L codes
{
    int i;
    for (i = 0; i < n; ++i)
        cout<< arr[i];

    cout<<"\n";
}

void MinHeap::getCodes(HuffNode* root, int arr[], int top) //arr �j�p�u�n height ���״N�n

{
    //���������� 1
    if (root->leftChild)
    {
        arr[top] = 1;
        getCodes(root->leftChild, arr, top + 1);
    }
    //���k������ 0
    if (root->rightChild)
    {
        arr[top] = 0;
        getCodes(root->rightChild, arr, top + 1);
    }
    //�M����򪺻��j�Aarr ���L leaf �����v�T(return �^�h�ɷ|����мg��)
    if (isLeaf(root))
    {
        cout<< root->symbol <<": ";
        printEncode(arr, top);
    }
}
