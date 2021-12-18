#include <iostream>

using namespace std;
template <class N>
struct Node{
    N nodeValue;
    Node* nextNode = NULL;
};

template <class T>

class Stack{
	public:		
		Node<T>* head = NULL;
		Node<T>* tmp;
		Node<T>* n;
	
		void Push(T x){
			n = new Node<T>;
			n -> nodeValue = x;
			
			if(head == NULL){
				head = n;
				tmp = n;
			}
			else{
				tmp -> nextNode = n;
				tmp = tmp -> nextNode;
			}
		}
		
		void Pop(){
            if(!Size())
                cout << "Error in Pop(): Stack is empty." << endl;
            else if(Size() == 1){
                Node<T>* t = head -> nextNode;
                head = NULL;
                delete t;
            }
            else{
                Node<T>* t;
                for(Node<T>* i = head;i -> nextNode != NULL;i = i -> nextNode)
                    t = i;
                
                tmp = t;
                t = t -> nextNode;
                tmp -> nextNode = NULL;
                delete t;
            }
		}
		
		int Size(){
			int cnt = 0;
			for(Node<T>* i = head;i != NULL;i = i -> nextNode)
				cnt++;
			return cnt;
		}
		
		T Top(){
            if(!Size()){
                cout << "Error in Top(): Stack is empty" << endl;
                return -1;
            }
            else{
                Node<T>* i = head;
                
                while(i -> nextNode != NULL)
                    i = i -> nextNode;
                
                return i -> nodeValue;	
            }
		}
        void print(){
            cout << "test.Top(): " << Top () << endl;
            cout << "test.Size(): " << Size() << endl;
            cout << "test.data(): ";
            for(Node<T>* i = head;i != NULL;i = i -> nextNode){
                cout << i -> nodeValue << " ";
            }
            cout << endl;
        }
};

int main(){
	Stack<int> test;
    int data;
    char cmd;
    cin >> cmd;
    while(cmd!='e'){
        switch(cmd){
            case 'i':
                cin >> data;
                test.Push(data);
                break;
            case 'o':
                test.Pop();
                break;
        }
        test.print();
        cin >> cmd;
    }
	return 0;
}
