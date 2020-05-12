#include <iostream>
#include <queue>  //方便插入 leaf 和 node
#include <string>  //第五題需使用
#include <bits/stdc++.h> //其他函式需求
using namespace std;

struct HuffNode //使用 min heap 去實作
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
        bool IsEmpty();  //判斷 heap 是不是空的
        const HuffNode& Top();  //列印 min heap 最上層的點
        void Push(const HuffNode&); //新增 min heap 內元素
        void Pop(); //刪除 min heap 元素
        void ChangeSize1D(HuffNode *a, const int oldSize, const int newSize); //擴充 min heap 大小
        void print();//列印 min heap
        int Level(); //計算 heap tree 的層數
        void Huffman_element(int*,int); //建立 HuffMan tree 的 leaf 和 node
        HuffNode* create_Huffman_tree(int); //建立 Huffman tree
        string decode(HuffNode*,string); //decode
        HuffNode* newNode(int data, char symbol); // 類似 copy constructor 功能
        int Max(int,int); //比大小，搭配計算 HuffMan tree level 用
        void preorder(HuffNode *root); //Preorder traversal
        void Inorder(HuffNode* root); //Inorder traversal
        int getHeight(HuffNode* root); //得 HuffMan tree 高度
        bool isLeaf(HuffNode* root); //判斷是否為 leaf
        void printEncode(int arr[], int n); //印出各英文字母的 HuffMan code(放在getCodes 裡面)
        void getCodes(HuffNode* root, int arr[], int top); //建立英文字母的 HuffMan code，並印出
    private:
        HuffNode *heap; // element array，做 HEAP
        HuffNode *tree; // Huffman tree
        queue<HuffNode*> itr1; //暫存器，leaf 和 Node 由小排到大
        int heapSize; // number of elements in heap
        int capacity; // size of the array heap
};

int main()
{
    string test;
    cout << "Input a string: " ;
    cin >> test;
    cout << endl;
    char *a = new char[test.length()];  //暫存 string 資料
    int *b = new int[test.length()];    //計算 freq 用
    for(int i = 0 ; i < test.length();i++)
        a[i] = test[i];
    for(int i = 0 ; i < test.length();i++)
        b[i] = 0;

    sort(a,a+test.length());  //將資料由大排到小
    char comp = a[0];
    int k = 0, j = 0;
    for(int i = 0 ; i < test.length();i++)  //計算各資料出現的 freq
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
    char *arr = new char[k+1];  //建立新空間(省空間)
    int *freq = new int[k+1];   //建立新空間(省空間)

    arr[0] = a[0];    //資料丟過去
    for(int i = 0 ; i < test.length();i++)
    {
        if(arr[j] != a[i])
        {
            j++;
            arr[j] = a[i];
        }
    }

    for(int i = 0; i < k + 1;i++)  //資料丟過去
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
    for (int i = 0; i < k+1; i++)  //將元素 push 進去
    {
        HuffNode leaf_node;
        leaf_node.data = freq[i];
        leaf_node.symbol = arr[i];
        leaf_node.leftChild = leaf_node.rightChild = nullptr;
        min_heap.Push(leaf_node);
    }

    min_heap.print();  // print min heap (第一題)
    min_heap.Huffman_element(freq,k+1);
    cout << "===============================================" << endl;
    HuffNode *temp = new HuffNode[1];
    temp = min_heap.create_Huffman_tree(k+1);
    cout << "Huffman Tree:" << endl;  //第二題
    cout << "Preorder: " ;
    min_heap.preorder(temp);
    cout << endl << "Inorder: ";
    min_heap.Inorder(temp);
    cout << endl << "Max Level: " << min_heap.getHeight(temp) << endl << "Number of node: " << 2*(k+1) - 1<< endl;
    cout << "===============================================" << endl;
    int code[min_heap.getHeight(temp)] = {0};
    int top = 0;
    min_heap.getCodes(temp,code,top);  //第三題
    cout << "===============================================" << endl;
    string decoder;
    cout << "Input sequence for decode: ";  //第四題
    cin >> decoder;
    cout << endl;
    cout << "Decoded HuffMan Data:" << endl << min_heap.decode(temp,decoder) << endl << endl;
    cout << "===============================================" << endl;
    delete[]arr;
    delete[]freq;
    return 0;
}

MinHeap::MinHeap()  //初始化
{
    heapSize = 0;
    capacity = 10;
    heap = new HuffNode[capacity + 1]; //heap[0] 拿來做 Huffman tree
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

MinHeap::MinHeap(int a)   //初始化
{
    heapSize = 0;
    capacity = a;
    heap = new HuffNode[capacity + 1];  //heap[0] 拿來做 Huffman tree
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

bool MinHeap::IsEmpty()  //如果 heap 空，true
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

//節錄自課本的 sample code
void MinHeap::Push(const HuffNode& a)
{
    if(heapSize == capacity)
    {
        ChangeSize1D(heap, capacity, 2*capacity);
        capacity *= 2;
    }

    int currentNode = ++heapSize;
    while(currentNode != 1 && heap[currentNode/2].data > a.data)  //做 recursive 確保排序是 min heap
    {
        heap[currentNode] = heap[currentNode/2]; //如果葉子比母節點大，要做交換值
        currentNode /= 2;    //然後再跟更上面的做比較，直到最起始的樹根
    }
    heap[currentNode] = a;
}

//節錄自課本的 sample code
void MinHeap::Pop()
{
    if(IsEmpty())
        cout << "堆疊已空，不能再刪除了!" << endl;
    else
    {
        HuffNode lastE = heap[heapSize];
        heapSize--;
        int currentNode = 1; // 樹根
        int child = 2; // currentNode 的一個兒子節點

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

//建立一個 HuffMan pointer，擴增大小和把資料賦予過去後，指回去
void MinHeap::ChangeSize1D(HuffNode *a, const int oldSize, const int newSize)
{
    HuffNode *temp = new HuffNode[newSize + 1];

    for(int i = 1 ;i < oldSize;i++)
        temp[i] = a[i];

    delete[]a;
    a = temp;
}

void MinHeap::print()  //print HuffMan tree data，超過 2 的次方換下一行列印
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

int MinHeap::Level()    //計算 heap 的 level，heapSize 與 level 關係 2^level + 1 = heapSize
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

void MinHeap::Huffman_element(int *a, int b) // leaf + node 數量等於 2*heapSize - 1
{
    int *p = new int[2*b - 1]; // leaf + node 數量等於 2*heapSize - 1
    int *q = new int[b - 1];   // 記 node data 值
    int temp = 0;
    int k = 0;
    int j = 1;
    for(int i = 0;i < b;i++)   //先存取 leaf data 值
        p[i] = a[i];

    sort(p,p + b);  //sort 由小到大，這樣可以做類似 priority queue 的動作
    for(int i = 0;i < b - 1;i++)  //會得到 heapSize - 1 個 node，故做 heapSize - 1 次
    {
        temp = p[k] + p[k + 1];  //將最兩小的值相加
        p[b + j - 1] = temp; //把值放進去
        q[j - 1] = temp; //記 node data 資料
        sort(p,p + b + j); //重新排列過
        k = k + 2;
        j++;
    }

    MinHeap g(2*b - 1); //建立huffman tree 空間大小
    for(int i = 1;i<b+1;i++)
        g.Push(heap[i]);

    HuffNode h;
    for(int i = 0;i < b - 1;i++)  //此時 heap 含有 HuffMan Node
    {
        h.data = q[i];
        h.symbol = '$';
        g.Push(h);  //push node 進去
    }

    int tmp1;
    char tmp2;
    for(int i = 2*b - 1; i > 0; i--)  //做 bubble sort，得到的 leaf / node freq 由小到大
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

    for(int i = 1; i < 2*b; i++)   // NODE 跟 LEAF 由小到大，值一樣 NODE 排在前
        itr1.push(&g.heap[i]);     //push 到 queue

    delete[]p;
    delete[]q;
}

HuffNode* MinHeap::create_Huffman_tree(int a)  //建立 HuffMan tree，從最底層(tree level 值最大)開始建
{
    int i = 0;
    int k = 0; //做節點用
    while(k < a - 2)  // Node 數量 = heapSize - 2
    {
        if(itr1.front()->symbol != '$' && tree[i].rightChild == nullptr)  //如果 queue 第一個的 symbol != '$'，又現在node的右子樹為 nullptr
        {
            tree[i].rightChild = newNode(itr1.front()->data,itr1.front()->symbol); //把它當做右子樹
            itr1.pop();
        }
        else if(itr1.front()->symbol != '$' && tree[i].leftChild == nullptr)  //左子樹同理
        {
            tree[i].leftChild = newNode(itr1.front()->data,itr1.front()->symbol);
            itr1.pop();
            i++;  //滿了，換到下一個節點
        }
        else if(itr1.front()->symbol == '$' /*&& tree[i].data == 0*/)  //如果 = '$' 當節點使用
        {
            tree[k].data = itr1.front()->data;  //指向節點
            tree[k].symbol = itr1.front()->symbol;
            itr1.pop();
            if(tree[i].rightChild != nullptr) //節點的上面一定是節點
            {
                tree[i].leftChild = &tree[k];  //右節點滿了指向左節點
                i++;
                if(i == a - 1) //除非是最後一個，即為 ROOT
                {
                    tree[i - 1].data = itr1.front()->data;
                    tree[i - 1].symbol = itr1.front()->symbol;
                    itr1.pop();
                }
            }
            else
                tree[i].rightChild = &tree[k]; //反之

            k++;

        }
    }
    return &tree[a-2]; //回傳 ROOT
}

string MinHeap::decode(HuffNode *root,string s)  // 輸入一連串的 huffman codes
{
    string ans = "";
    HuffNode* curr = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '1')  //1 就往左子樹跑
           curr = curr->leftChild;
        else  //反之
           curr = curr->rightChild;

        // reached leaf node
        if (isLeaf(curr))
        {
            ans += curr->symbol;
            curr = root; //然後從頭開始
        }
    }
    // cout<<ans<<endl;
    return ans+'\0';
}

HuffNode* MinHeap::newNode(int data, char symbol)  //類似在做 copy constructor 功能
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
   if (root != nullptr) //如果節點不是 nullptr
   {
      cout<<root->data<<" "; //先印節點
      preorder(root->leftChild); //走訪 leftChild
      preorder(root->rightChild); //最後在走訪 rightChild
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
   if (isLeaf(root)) //到底部
         return 0;

   // 去尋找其左右子樹的深度
   int lh = getHeight(root->leftChild);  //recursive
   int rh = getHeight(root->rightChild); //recursive

   return 1 + Max(lh,rh);
}

bool MinHeap::isLeaf(HuffNode* root) //判斷是不是 leaf
{
    if(root->leftChild == nullptr && root->rightChild == nullptr)
        return 1;
    else
        return 0;
}

void MinHeap::printEncode(int arr[], int n)  //列印 codes
{
    int i;
    for (i = 0; i < n; ++i)
        cout<< arr[i];

    cout<<"\n";
}

void MinHeap::getCodes(HuffNode* root, int arr[], int top) //arr 大小只要 height 長度就好

{
    //往左走等於 1
    if (root->leftChild)
    {
        arr[top] = 1;
        getCodes(root->leftChild, arr, top + 1);
    }
    //往右走等於 0
    if (root->rightChild)
    {
        arr[top] = 0;
        getCodes(root->rightChild, arr, top + 1);
    }
    //然後持續的遞迴，arr 到其他 leaf 不受影響(return 回去時會把值覆寫掉)
    if (isLeaf(root))
    {
        cout<< root->symbol <<": ";
        printEncode(arr, top);
    }
}
