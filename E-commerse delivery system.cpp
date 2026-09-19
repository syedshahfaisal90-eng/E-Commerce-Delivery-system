#include<iostream>
#include<string>
#include<limits>
#include<algorithm>
using namespace std;

class Node{

    public:

    string OrderItem;
    Node* next;
    Node* previous;
    
    Node(string orderItem):OrderItem(orderItem),next(NULL),previous(NULL){};

};
class OrderList {
    Node* head;
    Node* tail;

public:
    OrderList() : head(NULL), tail(NULL) {}

    OrderList(const OrderList& other) : head(NULL), tail(NULL) {
        Node* temp = other.head;
        while (temp != NULL) {
            append(temp->OrderItem);
            temp = temp->next;
        }
    }

    OrderList& operator=(const OrderList& other) {
        if (this == &other) return *this;

        Node* cur = head;
        while (cur) {
            Node* nx = cur->next;
            delete cur;
            cur = nx;
        }
        head = tail = NULL;

        Node* temp = other.head;
        while (temp != NULL) {
            append(temp->OrderItem);
            temp = temp->next;
        }
        return *this;
    }

    void append(string item) {
        Node* newNode = new Node(item);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            newNode->previous = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void display() const {
        if (head == NULL) {
            cout << "List is empty!\n";
            return;
        }
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->OrderItem <<" ";
            temp = temp->next;
        }
        cout<<endl;
    }

    ~OrderList() {
        Node* current = head;
        while (current != NULL) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = NULL;
    }
};
class OrderPackage{

    public:

    OrderList Order;
    string customer;
    string address;
    unsigned long long distance;

    OrderPackage() : customer(""), address(""), distance(0ULL) {};

    OrderPackage(const OrderList& O, const string& cust, const string& add, unsigned long long dist)
        : Order(O), customer(cust), address(add), distance(dist) {};


    void display(){
        
        cout<<"Name:"<<customer<<endl;
        cout<<"Address:"<<address<<endl;
        cout<<"Distance:"<<distance<<"m\n";
        cout<<"Items:"<<endl;
        Order.display();

    }
};
void DistanaceSort(OrderPackage package[], int size){
     for(int i=0;i<size;i++){
        int min_ind=i;
        for(int j=i+1;j<size;j++){
            if(package[j].distance < package[min_ind].distance){
                min_ind=j;
            }
            
        }
        if(min_ind != i) swap(package[i],package[min_ind]);
    }
}
class Bagstack{
    OrderPackage* package;
    int size;
    int top;
    public:
    Bagstack(int s=3){
     size=s;
     top=-1;
     package= new OrderPackage[size];
    }

    Bagstack(const Bagstack& other) {
        size = other.size;
        top = other.top;
        package = new OrderPackage[size];
        for (int i = 0; i <= top; ++i) package[i] = other.package[i];
    }

    Bagstack& operator=(const Bagstack& other) {
        if (this == &other) return *this;
        delete[] package;
        size = other.size;
        top = other.top;
        package = new OrderPackage[size];
        for (int i = 0; i <= top; ++i) package[i] = other.package[i];
        return *this;
    }

     void Push(const OrderPackage& p) {
        if (top < size - 1) {
            package[++top] = p;
        }
        else {
            cout << "Stack overflow!\n";
        }
    }

    OrderPackage Pop(){
        if(top>=0){
           return package[top--];
            
        }
        else{
            cout<<"Stack underflow!\n";
            return OrderPackage();
        }
    }

    bool isEmpty() const {
        return top == -1;
    }

    void displayStack(){
        if (isEmpty()) {
            cout << "Bagstack is empty.\n";
            return;
        }
        cout << "Bagstack contents (top -> bottom):\n";
        for (int i = top; i >= 0; --i) {
            package[i].display();
        }
    }

    ~Bagstack(){
      delete[] package;
    }
};
class node{

    public:

    Bagstack data;
    node* next;
    node(const Bagstack& b):data(b),next(NULL){};

};
class Queue{

    node* front;
    node* rear;

    public:

    Queue(){
    front=rear=NULL;
    }

    void enqueue(const Bagstack& b) {
        node* newnode = new node(b);
        if (rear == NULL) {
            rear = front = newnode;
        }
        else {
            rear->next = newnode;
            rear = newnode;
        }
    }

    void dequeue(){
        if(front==NULL){
            cout<<"Queue is Empty!\n";
            return;
        }
        
            node* temp= front;
             if(!temp->data.isEmpty()) {
                temp->data.displayStack();
                front = front->next;
                 if (front == NULL) rear = NULL;
                    delete temp;
                       return;

           }
           OrderPackage pkg = temp->data.Pop();
           cout<<"Delivering package to "<<pkg.customer<<" at distance "<<pkg.distance<<"m\n";
            pkg.display();
            cout<<"-----------------------\n";
            
    }

    ~Queue() {
       node* curr = front;
    while (curr != NULL) {
        node* next = curr->next;
        delete curr;   
        curr = next;
    }

    }

};
int main(){
    OrderList l1,l2,l3;

    l1.append("Laptop");
    l1.append("Phone");
    l1.append("HeadPhones");
    l1.append("Charger");
    l1.append("Keyboard");

    l2.append("Monitor");
    l2.append("Mouse");
    l2.append("Laptop Stand");

    l3.append("Nokia 3310");
    l3.append("Fishing Rod");
    l3.append("Radio");
    l3.append("Pilum");

    OrderPackage p1(l2,"Ezio Auditore da Firenze","Florence, Republic of Florence ", 900ULL);
    OrderPackage p2(l1,"M Khizar 16881","Charsadda",700ULL);
    OrderPackage p3(l3,"Some uncivilized alien species","Beyond the Observable Universe",1844674407370955161ULL);


    OrderPackage arr[]={p1,p2,p3};
    DistanaceSort(arr,3);
    Bagstack s(3);
    
 
    for(int i = 2; i >= 0; i--){
        s.Push(arr[i]);
    }

    Queue q;
    q.enqueue(s);
    q.dequeue();
    

}