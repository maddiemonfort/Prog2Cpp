#include <stdexcept>

template<typename T>
class Queue 
{
	struct node {
		T object;
		node* next;

		node(const T & object, node* next) {
			this->object = object;
			this->next = next;
		}
	};

	node* head;
	node* tail;
	int size;

	public:
		Queue() { //constructor
			head = NULL;
			tail = NULL;
			size = 0;
		}

		~Queue() { //destructor
			if(size == 1) {
				delete head;
			}
			else if(size > 1) {
				node* previous = head;
				node* current = head->next;
				//delete each of the nodes
				while(current != NULL) {
					delete previous;
					previous = current;
					current = current->next;
				}
				delete previous; //delete the last node in list
			}
		}

		//add node to end of the list
		void enqueue(T element) {
			if(isEmpty()) { //when at head (empty list)
				head = new node(element, NULL);
				tail = head;
			}
			else { 
				node* n = new node(element, NULL);
				tail->next = n;
				tail = tail->next;
			}
			size++;
		}

		//remove first node (FIFO)
		T dequeue() {
			if(isEmpty()) { //empty
				throw std::domain_error("Queue is empty.");
			}
			T element = head->object;
			node* current = head->next;
			delete head;
			head = current;
			//if you pop off the last element in the list (there was only one element left)
			if(head == NULL) {
				tail = head;
			}
			size--;
			return element;
		}

		bool isEmpty() {
			if(size == 0) {
				return true;
			}
			else  {
				return false;
			}
		}

};