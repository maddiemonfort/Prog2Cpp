/*

This is a modified linked list that is used to create the snake.

*/



#include <stdexcept>

template <typename T>
class Node {
	public:
		T object;
		Node* next;
		
        //constructor
		Node(T object, Node<T>* next) {
			this->object = object;
			this->next = next;
		}
};

template <typename T>
class LL
{
	Node<T>* head;
	
	public:
    
		//constructor
        LL() {
			head = 0;
		}
		
		void insert(int position, T object) {
			if (position < 0 || position > size()) {
				throw std::domain_error("position is not valid");
			}
			
			if (size() == 0) {
				head = new Node<T>(object, 0);
				return;
			}
			
			if (position == 0) {
				Node<T>* insertion = new Node<T>(object, head);
				head = insertion;
				return;
			}
			
			Node<T>* current = head;
			Node<T>* previous = head;
			for (int i = 0; i < position; ++i) {
				previous = current;
				current = current->next;
			}
			
			previous->next = new Node<T>(object, current);
		}
		
		T remove(int position) {
			if (position < 0 || position > size() - 1)
			{
				throw std::domain_error("position is not valid");
			}
			
			Node<T>* current = head;
			Node<T>* previous = head;
			for (int i = 0; i < position; ++i)
			{
				previous = current;
				current = current->next;
			}
			
			previous->next = current->next;
			T data = current->object;
			delete current;
			return data;
		}
		
		int size() const {
			if (head == 0) {
				return 0;
			}
			
			int size = 1;
			Node<T>* current = head;
			while (current->next != 0) {
				++size;
				current = current->next;
			}
			
			return size;
		}
		
		T item_at(int position) const {
			if (position < 0 || position > size() - 1) {
				throw std::domain_error("position is not valid");
			}
			
			Node<T>* current = head;
			for (int i = 0; i < position; ++i) {
				current = current->next;
			}
			
			return current->object;
		}
    
    void move(T object, bool eat) {
        Node<T>* current = head;
        head = new Node<T>(object, current);

        if(!eat) {
        	remove(size() - 1);
        }
    }
};
