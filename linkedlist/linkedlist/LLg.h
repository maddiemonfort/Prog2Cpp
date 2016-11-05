#include<stdexcept>
#include<ostream>
#include<string>

using namespace std;

template <typename T>
class LL
{
	struct Node
	// methods/variables in a struct are public by default
	// the struct itself is private inside class LL
	{
		T object;
		Node* next;
	
		Node(const T& object, Node* next) // constructor
		{
            this->object = object;
            this->next = next;
		}
		
		// do you need a destructor?
	};
	
	// private methods
	// these are just a suggestion
	// feel free to add/remove private methods as necessary
	/*int pool_size()
	{
		
	}
	
	Node* allocate(const T& object, Node* next)
	// returns a node from the pool or allocates a new one if the pool is empty
	{
	
	}
	
	void deallocate(Node* &remove)
	// decides whether a node should be deleted or added to the pool
	{
	
	}*/
	
	
	// class members
	Node* head;
	Node* free; // Note: it's also possible to just define an instance of LL as the free list
	Node* tail;
	
	public:
		LL() // constructor
		{
            head = NULL;
            tail = NULL;
            free = NULL;
		}
		
		LL(const LL& src) // copy constructor
		{
            this->head = NULL;
            this->tail = NULL;
            this->free = NULL;
            
            for(int i = 0; i < src.size(); i++) {
                this->push_back(src.item_at(i));
            }
		}
		
		~LL() // destructor
		{
            clear();
            delete head;
            delete tail;
            delete free;
		}
		
		/*LL& operator=(const LL& src) // overloading the = operator
		{
			
		}*/
		
		void insert(int position, const T& object)
		{
            Node* current = head;
            Node* previous = NULL;
            
            if(this->size() == 0) {
                push_front(object);
            }
            else {
                for(int i = 0; i < position; i++) {
                    previous = current;
                    current = current->next;
                }
                Node* n = new Node(object, NULL);
                previous->next = n;
                n->next = current;
            }
		}
		
		T remove(int position)
		{
            Node* current = head;
            Node* previous = NULL;
            for(int i = 0; i < position; i++) {
                previous = current;
                current = current->next;
            }
            
            previous->next = current->next;
            T data = current->object;
            delete current;
            return data;
		}
		
		int size() const
		{
            int size = 1;
            if (head == NULL) {
                return 0;
            }
            else {
                Node* current = head;
                while (current != NULL) {
                    current = current->next;
                    size++;
                }
                return size;
            }
            
		}
		
		T item_at(int position) const
		{
            Node* current = head;
            if (size() == 0) {
                return head->object;
            }
            else {
                for(int i = 0; i < position; i ++) {
                    current = current->next;
                }
                return current->object;
            }
        }
    
		
		// new methods for added functionality
		T replace(int position, const T& object)
		{
		
		}
		
		void push_front(const T& object)
		{
            Node* current = head;
            head = new Node(object, current);
		}
		
		void push_back(const T& object)
		{
		
		}
		
		T pop_front()
		{
		
		}
		
		T pop_back()
		{
		
		}
		
		bool is_empty() const
		{
		
		}
		
		void clear()
		{
		
		}
		
		void print(std::ostream& out) const
		{
			// use paremeter "out" just as you would cout
			// example: out << item_at(0);
			// use '\n' for new lines
			// to call this method externally and print to the screen:
			//     LL.print(std::cout);
		}
		
		// the following two methods are substantially more diffiult to implement
		// don't worry if you can't get them
		// they are not necessary for PA2
		
		/*void reverse()
		{
			
		}
		
		bool contains(const T& element, bool equals(const T& a, const T& b )) const
		// this method takes a function pointer to a method to check equality for a given type T
		{
		
		}*/
};

