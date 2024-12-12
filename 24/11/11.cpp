#include <iostream>
#include <string>

struct Node{
    unsigned long long data;
    bool blinked;
    Node* next; 

    // constructor
    Node(unsigned long long data, bool blinked=false) :
        data(data), blinked(blinked), next(nullptr) {}

    // blink data method 
    int blink(){
        blinked = true;
        int plus = 0;
        
        std::string data_str = std::to_string(data);
        if (data==0){
            data = 1;
        }else if (data_str.size()%2 == 0){
            data = std::stoull(data_str.substr(0, data_str.size()/2));
            unsigned long long second = std::stoull(data_str.substr(data_str.size()/2, data_str.size()));    

            Node* new_node = new Node(second, true);
            new_node->next = next;
            next = new_node;
            
            // increase plus by 1
            plus++;
        }else{
            data = data*2024;
        }

        return plus;
    }

    // 

};

// linked list implementation
class LinkedList{
public:
    Node* head;
    unsigned long long counter = 0;

    // constructor 
    LinkedList() : head(nullptr){}

    // destructor 
    ~LinkedList(){
        Node* current = head;
        while (current != nullptr){
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // add a node to the end of the list 
    void append(unsigned long long value){
        Node* new_node = new Node(value);
        if (head == nullptr){
            head = new_node;
        }else{
            Node* temp = head;
            while (temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = new_node;
        }
        counter++;
    }

    // print the list
    void print(){
        Node* current = head;
        while (current != nullptr){
            std::cout << current->data << "->";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // transverse blinking all nodes
    void transverse(){
        Node* current = head;
        while (current != nullptr){
            if (current->blinked == false){
                counter += (unsigned long long) current->blink();
            }
            
            // change the blinked state to false. 
            // this will allow the node to blink again later
            current->blinked = false;

            // move to the next node
            current = current->next;
        }
    }

};

int main(){
    LinkedList list;
    list.append(5910927);
    list.append(0);
    list.append(1);
    list.append(47);
    list.append(261223);
    list.append(94788);
    list.append(545);
    list.append(7771);
    
    for (int i=0; i<25; i++){
        list.transverse();
    }
    std::cout << "counter (part a)= " << list.counter << std::endl;

    // not working!!
    // for (int i=0; i<50; i++){
    //     list.transverse();
    // }
    // std::cout << "counter (part b)= " << list.counter << std::endl;


    return 0;
}