#include<iostream>
using namespace std;

int List();      //��ܨϥέ��� queue
int makeSize();  //�T�w queue �j�p
int Function();  //�ϥ� queue ���\��(���J�ΧR��)

class linear_queue   //�\��@
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

class circular_queue  //�\��G
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

struct Node  //�\��T�n�ϥ�
{
    int data;
    struct Node *next;
};

class linkedlist_cqueue  //�\��T
{
private:
    int size = 5;
    int head;    //��K���X�U�� example ���ĪG
    int tail;    //��K���X�U�� example ���ĪG
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
    //���{���u���@�� queue �h���A�Y�n�ϥΥt�@�� queue�A�Э��s����@��

    int n = List();  //�����ѿ��
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

        size = makeSize();   //�T�w�j�p

        linear_queue a(size);
        circular_queue b(size);
        linkedlist_cqueue c(size);

        int choice = Function();  //�T�w�ϥΦ�� function(���J�ΧR��)

        while(choice != 3)
        {
            if(choice == 1)
            {
                cout << "Enter an element : " ;  //�Y�O���J
                cin >> element;                  //�h�s�W����
                cout << endl;
                if(n == 1)                     //�Y�@�}�l��� linear queue�A�N�ΰ��� linear queue �� function
                    a.insert(element);         //�Ϥ�
                else if(n == 2)
                    b.insert(element);
                else
                    c.insert(element);
            }
            else if(choice == 2) //�Y�O�R���A�h�R������
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
            choice = Function();  //���s��� function
        }
        cout << "Exit the program, see you next time!" << endl;
    }
    return 0;
}

int List()    //��ܨϥέ��� queue
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

int makeSize()   //�T�w queue �j�p
{
    int qsize;
    cout << "Enter the size of Queue : ";
    cin >> qsize;
    cout << endl;
    return qsize;
}

int Function()  //�ϥ� queue ���\��(���J�ΧR��)
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
    queue = new int[size];    //���إߤj�p
    for(int i = 0 ; i < size ; i++)   //�A�O�̭����Ŧr��
        queue[i] = '\0';
}

linear_queue::linear_queue(int a)    //linear queue �t�@�� constructor
{
    front = 0;
    rear = 0;
    size = a;
    queue = new int[size];
    for(int i = 0 ; i < size ; i++)    //�A�O�̭����Ŧr��
        queue[i] = '\0';
}

linear_queue::~linear_queue()   //destructor ��O�����k��
{
   delete[]queue;
}

void linear_queue::insert(int a)    //���J function
{
    if(rear != size - 1)      //�Y rear ���O����̫�@��
    {
        ++rear;               //�i�H���Ჾ�@��
        queue[rear] = a;      //����
        display();            //�æC�L
    }
    else
    {
        cout << "Queue is full!" << endl;   //�Y����̫�@�ӡAqueue �w��
        display();
    }
}

void linear_queue::Delete()
{
    if(rear - front > 0)       //�Y rear - front �j�� 0 (�Y�٦�����)
    {
        cout << "Deleted element is " << queue[front + 1] << endl;  //delete �}�C�� front + 1 �ӡA�]�� front ���̫�@�ӨS����������m
        queue[front + 1] = '\0';
        front++;
        display();
    }
    else
    {
        cout << "Queue is empty, can't delete!" << endl;     //�S�������A����R��
        display();
    }
}

void linear_queue::display()    // �N linear queue �q�Y�L���
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

circular_queue::circular_queue(int a)   //�t�@�� Circular queue constructor
{
    front = 0;
    rear = 0;
    size = a;
    cqueue = new int[size];
    for(int i = 0 ; i < size ; i++)
        cqueue[i] = '\0';
}

circular_queue::~circular_queue()   //�N�O�����k��
{
   delete[]cqueue;
}

void circular_queue::insert(int a)
{
    if(abs(front - rear) < size - 1 && front - rear != 1)   //�p�G��Ӭ۴�� size - 1�A�M front - rear == 1(�S���p)�Aqueue ����
    {
        if(rear == size - 1)     //�Y rear ���̫�@��
        {
            rear = 0;            //���V�Ĥ@�Ӧ�m
            cqueue[rear] = a;
        }
        else                     //�_�h�N++
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
    if(rear != front)       //�Y rear != front �N���O�Ű}�C
    {
        if(front != size - 1)   //�Y front ���O�̫�@��
        {
            cout << "Deleted element is " << cqueue[++front] << endl; //�N +1 �R��
            cqueue[front] = '\0';
        }
        else
        {
            cout << "Deleted element is " << cqueue[0] << endl;  //�Y�O�̫�@�ӡC�O�o front = 0
            cqueue[0] = '\0';
            front = 0;
        }
        display();
    }
    else                                   //�_�h�� queue�A����R
    {
        cout << "Queue is empty, can't delete!" << endl;
        display();
    }
}

void circular_queue::display()     // �N circular queue �q�Y�L���
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
    head = 0;           //��e����Ӫ� front / rear �ܹ��A��K�C�L�X�ӮɹF���e����̮ĪG�@��
    tail = 0;           //�]�� linked list �O���h�ָ�Ƥ~�h�j�A�� array ���P�A�ҥH�n�o��ӰѼƻ��U��K�F���e��ӦC�L�X�Ӫ��ĪG
                        //head ���� front�A tail ���� rear
    Node *front = nullptr;    // linked list
    Node *rear = nullptr;
}

linkedlist_cqueue::linkedlist_cqueue(int a)   //�t�@�� linked list circular queue constructor
{
    size = a;
    head = 0;
    tail = 0;
    Node *front = nullptr;
    Node *rear = nullptr;

}

linkedlist_cqueue::~linkedlist_cqueue()  //�O�����k��
{
    Node *tmp1 = front;    //���t�䤤�@�Ӹ� front ��m�ۦP�A�q�o��}�l�R��
    Node *tmp2;
    while(1)
    {
        if(tmp1->next != front)     //�Y�٨S���^ front
        {
            tmp2 = tmp1->next;      //�R���쵲
            delete tmp1;
            tmp1 = tmp2;
        }
        else                    //�Y���^�h front
        {
            delete tmp1;        //�N�O�����k��
            delete tmp2;
            break;
        }
    }
}

void linkedlist_cqueue::insert(int a)               //���J function
{
    if(abs(tail - head) < size - 1 && head - tail != 1)   //�� circular queue ����@��
    {
        if(front == nullptr || rear == nullptr)   //�Y�٨S���쵲
        {
            Node *newNode;            //���гy�@�ӪŶ�
            newNode = new Node;

            newNode->data = a;       //�ñN data �x�s�i�h
            newNode->next = nullptr;

            front = newNode;    //�ñN������ front �M rear (�]���u���@���쵲)
            rear = newNode;
        }
        else      //�Y�D���쵲
        {
            Node *newNode;        //�@�˥��гy�@�ӪŶ�
            newNode = new Node;

            newNode->data = a;     // data �x�s�i�h
            rear->next = newNode;

            newNode->next = front;    //���ɱN�s�Ŷ����V front
            rear = newNode;          //�A�������� rear
        }

        if(tail < size - 1)     //�Y�s�W��ƦӥB�ä��O�b�̫�@�Ӧ�m
            tail++;             //�N++
        else
            tail = 0;          //���M���� 0

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
    if(tail != head)     //�P�_�O�_���� queue
    {
        Node *n;       //�O�@�� node �� front
        n = front;
        cout << "Deleted element is " << n->data << endl;
        front = front->next;   //�A�N front ���V�U�@��
        delete n;      //���ɴN�i�H�R��

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

void linkedlist_cqueue::display()   //�N�F��L�X�ӡA�����๳���e�x�}�@�˷Ӷ��ǦL
{
    Node *ptr;
    ptr = front;   // �O�@�� node = front
    if(head == tail)   //�Y head = tail �A �� queue
    {
        cout << "Linked List Circular Queue:";
        for(int i = size; i > 0; i--)
            cout << "[]";
        cout << endl;
        cout << "Front = " << head << ", " << "Rear = " << tail << endl << endl;
    }
    else  //�_�h�O�@�� array �� data size �@�ˤj
    {
        int A[size] = {'\0'};  //�������Ŧr��
        int num;
        int tmp;

        if(head == size - 1)  //���p�����}�l���O�Ŧr��
            tmp = 0;
        else
            tmp = head + 1;

        if(tail > head)    //�p��X�ӫD�Ŧr��
            num = tail - head;
        else
            num = size - head + tail;

        while(num)
        {
            if(tmp == size - 1 && num > 1)  //�Y��m���̫�@�ӡA���S���O�̫�@�Ӥ���
            {
                A[tmp] = ptr->data;   //�O����m������
                ptr = ptr->next;      //���V�U�@���쵲
                tmp = 0;               //�U�@�Ӧ�m�� 0
                --num;                //�n�[�i�h�� data �� -1
            }
            else if(num == 1)    //�Y��n���̫�@��
            {
                A[tmp] = ptr->data;   //�N���Ϋ��V�U���쵲
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
        cout << "Linked List Circular Queue:";  //�A�Ӷ��ǦL�X��
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
    delete ptr;  //�k�٪Ŷ�
}
