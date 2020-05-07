#include<iostream>
using namespace std;

int List();      //選擇使用哪種 queue
int makeSize();  //確定 queue 大小
int Function();  //使用 queue 的功能(插入或刪除)

class linear_queue   //功能一
{
private:
    int front;
    int rear;
    int size = 5;
    int *queue;
public:
    void insert(int);
    void Delete();
    void display();
    linear_queue();
    linear_queue(int);
    ~linear_queue();
};

class circular_queue  //功能二
{
private:
    int front;
    int rear;
    int size = 5;
    int *cqueue;
public:
    void insert(int);
    void Delete();
    void display();
    circular_queue();
    circular_queue(int);
    ~circular_queue();
};

struct Node  //功能三要使用
{
    int data;
    struct Node *next;
};

class linkedlist_cqueue  //功能三
{
private:
    int size = 5;
    int head;    //方便做出助教 example 的效果
    int tail;    //方便做出助教 example 的效果
    Node *front = nullptr;
    Node *rear = nullptr;
public:
    linkedlist_cqueue();
    linkedlist_cqueue(int);
    ~linkedlist_cqueue();
    void insert(int a);
    void Delete();
    void display();
};

int main()
{
    //本程式只能選一種 queue 去做，若要使用另一種 queue，請重新執行一次

    int n = List();  //先提供選單
    int element;
    int size;

    while(n != 4)
    {
        if(n == 1)
            cout << "Linear Queue" << endl;
        else if(n == 2)
            cout << "Circular Queue" << endl;
        else if(n == 3)
            cout << "Linked List" << endl;
        else
        {
            cout << "Exit the program, see you next time!" << endl;
            break;
        }

        size = makeSize();   //確定大小

        linear_queue a(size);
        circular_queue b(size);
        linkedlist_cqueue c(size);

        int choice = Function();  //確定使用何種 function(插入或刪除)

        while(choice != 3)
        {
            if(choice == 1)
            {
                cout << "Enter an element : " ;  //若是插入
                cin >> element;                  //則新增元素
                cout << endl;
                if(n == 1)                     //若一開始選擇 linear queue，就用執行 linear queue 的 function
                    a.insert(element);         //反之
                else if(n == 2)
                    b.insert(element);
                else
                    c.insert(element);
            }
            else if(choice == 2) //若是刪除，則刪除元素
            {
                if(n == 1)
                    a.Delete();
                else if(n == 2)
                    b.Delete();
                else
                    c.Delete();
            }
            else
                break;
            choice = Function();  //重新選擇 function
        }
        cout << "Exit the program, see you next time!" << endl;
    }
    return 0;
}

int List()    //選擇使用哪種 queue
{
    int choice;
    cout << "Select your choice" << endl << endl;
    cout << "1.Linear Queue" << endl;
    cout << "2.Circular Queue" << endl;
    cout << "3.Linked List" << endl;
    cout << "4.EXIT" << endl << endl;
    cout << "Enter your choice : ";
    cin >> choice;
    return choice;
}

int makeSize()   //確定 queue 大小
{
    int qsize;
    cout << "Enter the size of Queue : ";
    cin >> qsize;
    cout << endl;
    return qsize;
}

int Function()  //使用 queue 的功能(插入或刪除)
{
    int choice;
    cout << "1.Insertion" << endl;
    cout << "2.Deletion" << endl;
    cout << "3.Exit" << endl << endl;
    cout << "Enter your choice : ";
    cin >> choice;
    return choice;
}

linear_queue::linear_queue()   //linear queue constructor
{
    front = 0;
    rear = 0;
    queue = new int[size];    //先建立大小
    for(int i = 0 ; i < size ; i++)   //再令裡面為空字元
        queue[i] = '\0';
}

linear_queue::linear_queue(int a)    //linear queue 另一種 constructor
{
    front = 0;
    rear = 0;
    size = a;
    queue = new int[size];
    for(int i = 0 ; i < size ; i++)    //再令裡面為空字元
        queue[i] = '\0';
}

linear_queue::~linear_queue()   //destructor 把記憶體歸還
{
   delete[]queue;
}

void linear_queue::insert(int a)    //插入 function
{
    if(rear != size - 1)      //若 rear 不是指到最後一個
    {
        ++rear;               //可以往後移一格
        queue[rear] = a;      //給值
        display();            //並列印
    }
    else
    {
        cout << "Queue is full!" << endl;   //若指到最後一個，queue 已滿
        display();
    }
}

void linear_queue::Delete()
{
    if(rear - front > 0)       //若 rear - front 大於 0 (即還有元素)
    {
        cout << "Deleted element is " << queue[front + 1] << endl;  //delete 陣列第 front + 1 個，因為 front 指最後一個沒有元素的位置
        queue[front + 1] = '\0';
        front++;
        display();
    }
    else
    {
        cout << "Queue is empty, can't delete!" << endl;     //沒有元素，不能刪除
        display();
    }
}

void linear_queue::display()    // 將 linear queue 從頭印到尾
{
    cout << "Linear Queue:";
    for(int i = 0;i < size;i++)
    {
        if(queue[i] == '\0')
            cout << "[]" ;
        else
            cout << "[" << queue[i] << "]";
    }
    cout << endl;
    cout << "Front = " << front << ", " << "Rear = " << rear << endl << endl;
}

circular_queue::circular_queue()   //Circular queue constructor
{
    front = 0;
    rear = 0;
    cqueue = new int[size];
    for(int i = 0 ; i < size ; i++)
        cqueue[i] = '\0';
}

circular_queue::circular_queue(int a)   //另一種 Circular queue constructor
{
    front = 0;
    rear = 0;
    size = a;
    cqueue = new int[size];
    for(int i = 0 ; i < size ; i++)
        cqueue[i] = '\0';
}

circular_queue::~circular_queue()   //將記憶體歸還
{
   delete[]cqueue;
}

void circular_queue::insert(int a)
{
    if(abs(front - rear) < size - 1 && front - rear != 1)   //如果兩個相減不為 size - 1，和 front - rear == 1(特殊情況)，queue 未滿
    {
        if(rear == size - 1)     //若 rear 為最後一個
        {
            rear = 0;            //指向第一個位置
            cqueue[rear] = a;
        }
        else                     //否則就++
        {
            ++rear;
            cqueue[rear] = a;
        }
        display();
    }
    else
    {
        cout << "Queue is full!" << endl;
        display();
    }
}

void circular_queue::Delete()
{
    if(rear != front)       //若 rear != front 代表不是空陣列
    {
        if(front != size - 1)   //若 front 不是最後一個
        {
            cout << "Deleted element is " << cqueue[++front] << endl; //就 +1 刪除
            cqueue[front] = '\0';
        }
        else
        {
            cout << "Deleted element is " << cqueue[0] << endl;  //若是最後一個。記得 front = 0
            cqueue[0] = '\0';
            front = 0;
        }
        display();
    }
    else                                   //否則空 queue，不能刪
    {
        cout << "Queue is empty, can't delete!" << endl;
        display();
    }
}

void circular_queue::display()     // 將 circular queue 從頭印到尾
{
    cout << "Circular Queue:";
    for(int i = 0;i < size;i++)
    {
        if(cqueue[i] == '\0')
            cout << "[]" ;
        else
            cout << "[" << cqueue[i] << "]";
    }
    cout << endl;
    cout << "Front = " << front << ", " << "Rear = " << rear << endl << endl;
}

linkedlist_cqueue::linkedlist_cqueue()    //linked list circular queue constructor
{
    size = 5;
    head = 0;           //跟前面兩個的 front / rear 很像，方便列印出來時達到跟前面兩者效果一樣
    tail = 0;           //因為 linked list 是有多少資料才多大，跟 array 不同，所以要這兩個參數輔助方便達到跟前兩個列印出來的效果
                        //head 類似 front， tail 類似 rear
    Node *front = nullptr;    // linked list
    Node *rear = nullptr;
}

linkedlist_cqueue::linkedlist_cqueue(int a)   //另一種 linked list circular queue constructor
{
    size = a;
    head = 0;
    tail = 0;
    Node *front = nullptr;
    Node *rear = nullptr;

}

linkedlist_cqueue::~linkedlist_cqueue()  //記憶體歸還
{
    Node *tmp1 = front;    //先另其中一個跟 front 位置相同，從這邊開始刪除
    Node *tmp2;
    while(1)
    {
        if(tmp1->next != front)     //若還沒指回 front
        {
            tmp2 = tmp1->next;      //刪除鏈結
            delete tmp1;
            tmp1 = tmp2;
        }
        else                    //若指回去 front
        {
            delete tmp1;        //將記憶體歸還
            delete tmp2;
            break;
        }
    }
}

void linkedlist_cqueue::insert(int a)               //插入 function
{
    if(abs(tail - head) < size - 1 && head - tail != 1)   //跟 circular queue 條件一樣
    {
        if(front == nullptr || rear == nullptr)   //若還沒有鏈結
        {
            Node *newNode;            //先創造一個空間
            newNode = new Node;

            newNode->data = a;       //並將 data 儲存進去
            newNode->next = nullptr;

            front = newNode;    //並將它等於 front 和 rear (因為只有一個鏈結)
            rear = newNode;
        }
        else      //若非空鏈結
        {
            Node *newNode;        //一樣先創造一個空間
            newNode = new Node;

            newNode->data = a;     // data 儲存進去
            rear->next = newNode;

            newNode->next = front;    //此時將新空間指向 front
            rear = newNode;          //再讓它等於 rear
        }

        if(tail < size - 1)     //若新增資料而且並不是在最後一個位置
            tail++;             //就++
        else
            tail = 0;          //不然等於 0

        display();
    }
    else
    {
        cout << "Queue is full!" << endl;
        display();
    }
}
void linkedlist_cqueue::Delete()
{
    if(tail != head)     //判斷是否為空 queue
    {
        Node *n;       //令一個 node 為 front
        n = front;
        cout << "Deleted element is " << n->data << endl;
        front = front->next;   //再將 front 指向下一個
        delete n;      //此時就可以刪除

        if(head < size - 1)
            head++;
        else
            head = 0;

        display();
    }
    else
    {
        cout << "Queue is empty, can't delete!" << endl;
        display();
    }

}

void linkedlist_cqueue::display()   //將東西印出來，但不能像之前矩陣一樣照順序印
{
    Node *ptr;
    ptr = front;   // 令一個 node = front
    if(head == tail)   //若 head = tail ， 空 queue
    {
        cout << "Linked List Circular Queue:";
        for(int i = size; i > 0; i--)
            cout << "[]";
        cout << endl;
        cout << "Front = " << head << ", " << "Rear = " << tail << endl << endl;
    }
    else  //否則令一個 array 的 data size 一樣大
    {
        int A[size] = {'\0'};  //全部為空字元
        int num;
        int tmp;

        if(head == size - 1)  //先計算哪邊開始不是空字元
            tmp = 0;
        else
            tmp = head + 1;

        if(tail > head)    //計算幾個非空字元
            num = tail - head;
        else
            num = size - head + tail;

        while(num)
        {
            if(tmp == size - 1 && num > 1)  //若位置為最後一個，但又不是最後一個元素
            {
                A[tmp] = ptr->data;   //令此位置等於資料
                ptr = ptr->next;      //指向下一個鏈結
                tmp = 0;               //下一個位置為 0
                --num;                //要加進去的 data 數 -1
            }
            else if(num == 1)    //若剛好為最後一個
            {
                A[tmp] = ptr->data;   //就不用指向下個鏈結
                num = 0;
            }
            else
            {
                A[tmp] = ptr->data;
                ptr = ptr->next;
                ++tmp;
                --num;
            }
        }
        cout << "Linked List Circular Queue:";  //再照順序印出來
        for(int i = 0;i < size;i++)
        {
            if(A[i] == '\0')
               cout << "[]" ;
            else
               cout << "[" << A[i] << "]";
        }
        cout << endl;
        cout << "Front = " << head << ", " << "Rear = " << tail << endl << endl;
    }
    delete ptr;  //歸還空間
}
