#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
  class list;

  template <class Type>
  class list_iterator
  {
  public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator()
      : m_node(NULL)
    {
    }

    list_iterator(const list_iterator& other)
      : m_node(other.m_node)
    {
    }

    list_iterator& operator = (const list_iterator& other)
    {
        if (this != &other) {
            m_node = other.m_node;
        }
        return *this;
    }

    bool operator == (const list_iterator& other) const
    {
        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        return m_node != other.m_node;
    }

    reference operator * ()
    {
        return m_node->value;
    }

    pointer operator -> ()
    {
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        auto temp = *this;
        m_node = m_node->next;
        return temp;
    }
  private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
      : m_node(p)
    {
    }

    node<Type>* m_node;
  };

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
      if (!empty()) clear();
    }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

    void push_back(const value_type& value)
    {
        node<Type> *temp = new node<Type>(value, nullptr, nullptr);
        if (!empty()) { 
            temp->prev= m_tail;
            m_tail->next = temp;
            m_tail = temp;
        } else { 
            m_head = temp;
            m_tail = temp;
        }
    }

    void push_front(const value_type& value)
    {
        node<Type> *temp = new node<Type>(value, nullptr, nullptr);
        if(!empty()) {
            temp->next = m_head;
            m_head->prev = temp;
            m_head = temp;
        } else {
            m_head = temp;
            m_tail = temp;
        }
    }
    
    void pop_front()
    {
        if(!empty()) {
            
            if (m_head == m_tail){
               delete m_head;
               m_head = nullptr;
               m_tail = nullptr;
            } else {
                node<Type>* temp = m_head->next;
                delete m_head;
                m_head = temp;
                m_head->prev = nullptr;
            }
            
        }
    }

    void pop_back()
    {
        if(!empty()) { 
            
            if (m_head == m_tail){
                delete m_head;
                m_head = nullptr;
                m_tail = nullptr;
            } else {
                node<Type>* temp = m_tail->prev;
                delete m_tail;
                m_tail = temp;
                m_tail->next = nullptr;
            }
            
        }
    }
      
    iterator insert(iterator pos, const Type& value)
    {
        if (pos.m_node == nullptr){
            push_back(value);
            return iterator(m_tail);
        }
        if (pos == begin()){
            push_front(value);
            return begin();
        }
        
        pos.m_node->prev->next = new node<Type>(value, pos.m_node, pos.m_node->prev);
        pos.m_node->prev = pos.m_node->prev->next;
        return pos.m_node->prev;
    }

    iterator erase(iterator pos)
    {
        if (pos.m_node == m_head) {
			pop_front();
			return iterator(m_head);
		}
		else if (pos.m_node == m_tail) {
			pop_back();
			return iterator(m_tail);
		}

		pos.m_node->prev->next = pos.m_node->next;
		pos.m_node->next->prev = pos.m_node->prev;

		iterator next = pos.m_node->next;
		delete pos.m_node;
		return iterator(next);
    }

    void clear()
    {
        node<Type>* temp;
           
        while(m_head != nullptr){
            temp = m_head->next;
            delete m_head; 
            m_head = temp;
        }
        
        m_head = nullptr;
        m_tail = nullptr;
    }
      
    bool empty() const
    {
      if (size() == 0) return true;
      else return false;
    }
      
    size_t size() const
    {
        node<Type>* temp = m_head;
        size_t size = 0;
        
        while(temp != nullptr) {
            size++;
            temp = temp->next;
        }
        return size;
    }
    
    reference front()
    {
       return m_head->value;
    }

    reference back()
    {
      return m_tail->value;
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
