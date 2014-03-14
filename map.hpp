#ifndef MAP_H_
#define MAP_H_
#include<iostream>
#include<utility>
#include<string>
#include<iterator>
#include<cassert>
#include<initializer_list>
#include<stdexcept>
#include<sstream>
#include <random>
#include <chrono>


//using Key = std::string;
//using const_Key = const std::string;
//using Value =int;
template <typename T,typename H>
class Map{
    using Key = T;
    using const_Key = const T;
    using Value = H;
    using const_Value = const H;
    using value_type = std::pair<const Key, Value>;
    using const_value_type = const std::pair<const Key,Value>;
    public:
    Map();
    ~Map();
    Map(std::initializer_list<std::pair<Key,Value>>);
    
    class Node{
        public:
            Node* left = nullptr;
            Node* right = nullptr;
            Node* parent = nullptr;
            Node* next_iter = nullptr;
            Node* prev_iter = nullptr;
            char type = 'e';//right or left child
            value_type* pair_obj= nullptr;
            Node();
            Node(const value_type &obj);
            Node(value_type &&obj);
            ~Node();
    };
    class Iterator 
    {
        public:
            Node *iter_node;
            Iterator(Node *n);//ctor
            /*
               Iterator(const Iterator& copy);//copy ctor
               Iterator(Iterator &&copy);//move ctor
               Iterator& operator= (const Iterator&);//copy assignment operator.
               Iterator& operator=(Iterator&&);//Move Assignment operator.
               ~Iterator();
               */
            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator--();
            Iterator operator--(int);
            value_type& operator*() const;
            bool operator ==(const Iterator& other) const;
            bool operator !=(const Iterator& other) const;
            //bool operator ==(const Iterator& other) const;
            //bool operator !=(const Iterator& other) const;
    };
    class ConstIterator{
        public:
            const Node *iter_node;
            ConstIterator(const Node *n);//ctor
            ConstIterator(const Iterator&);//non const to constant Iter
            ConstIterator& operator++();
            ConstIterator operator++(int);
            ConstIterator& operator--();
            ConstIterator operator--(int);
            const_value_type& operator*() const;
            bool operator==(const ConstIterator& other) const;
            bool operator!=(const ConstIterator& other) const;

    };
    class ReverseIterator{
        public:
            const Node *iter_node;
            ReverseIterator(Node *n);//ctor 
            ReverseIterator& operator++();
            ReverseIterator operator++(int);
            ReverseIterator& operator--();
            ReverseIterator operator--(int);
            value_type& operator*() const;
            bool operator==(const ReverseIterator& other) const;
            bool operator!=(const ReverseIterator& other) const;

    };        
    Iterator insert(const_value_type &obj);
    Iterator insert(value_type &&obj);
    void erase(Iterator i);
    void set_pointer_after_delete(Iterator i);
    void remove(const_Key&);
    Node* find_position(Node* ,Key k);
    void delete_all_nodes(Node* n);
    void delete_node(Node*n);
    Map(const Map&);//copy ctor
    void copy_map(Node*n);
    Map(Map&&);//move ctor
    Map& operator=(const Map&);//assignment operator
    Map& operator=(Map&&);
    Iterator begin();
    Iterator end();
    ConstIterator begin()const;
    ConstIterator end()const;
    ReverseIterator rbegin() const;
    ReverseIterator rend() const;
    friend bool operator==(const ConstIterator& a,const Iterator& b){return(a==b);}
    friend bool operator!=(const ConstIterator& a,const Iterator& b){return (a!=b);}   
    friend bool operator==(const Iterator& a,const ConstIterator& b){return (a==b);}
    friend bool operator!=(const Iterator& a,const ConstIterator& b){return (a!=b);}
    std::size_t size() const;
    bool empty() const; 
    void clear();
    Iterator find(const_Key&);
    ConstIterator find(const_Key&) const;
    Value& at(const_Key&);
    const_Value& at(const_Key&) const;
    Value& operator[](const_Key&); 
    bool operator==(const Map&)const;
    bool operator!=(const Map&)const;
    void print_tree();
    void print_tree_h(Node *n);
    private:
    Node *root = nullptr;
    Node *head = new Node();
    Node *tail = new Node();
    std::size_t length = 0;
    Iterator insert_helper(Node *);
};
template<typename T,typename H>
Map<T,H>::Map(){}
template<typename T,typename H>
Map<T,H>::~Map()
{
    //this->print_tree();
    if(this->root!=nullptr)
    {
        this->delete_all_nodes(this->root);
        //this->delete_all_nodes(this->root->right);
    }
    //assert(this->head!=nullptr);
    //delete_node(this->head);
    //assert(this->tail!=nullptr);
    //delete_node(this->tail);
    //delete_node(this->root);
}

template<typename T,typename H>
void Map<T,H>::delete_node(Node*n)
{
   // if (n == nullptr) return;
    //delete_node(n->left);
    //delete_node(n->right);
    //delete n;
    //n = nullptr;
#if 1
    //assert(n != nullptr);
    if(n == nullptr)return;
    //if(n->pair_obj!= nullptr)return;
    if(n->type == 'h')
    {
        this->head->next_iter=this->tail;
        this->tail->prev_iter=this->head;
    } 
    if(n!=nullptr)
    delete n;
    n = nullptr;//how can i make the this pointer as null n is copy 
#endif
}
template<typename T,typename H>
void Map<T,H>::delete_all_nodes(Node *n)
{   
    if(n == nullptr)
        return;
    delete_all_nodes(n->left);
    delete_all_nodes(n->right);
    delete_node(n);
}
template<typename T,typename H>
void Map<T,H>::clear()
{
    delete_all_nodes(this->root->left);
    delete_all_nodes(this->root->right);
    this->head->next_iter=this->tail;
    this->tail->prev_iter=this->head;
    this->root = nullptr;
}
template<typename T,typename H>
Map<T,H>::Node::Node():pair_obj(nullptr){}//new value_type()){}
//node ctor
template<typename T,typename H>
Map<T,H>::Node::Node(const_value_type &obj):pair_obj(new value_type(obj)){}

//mov ctor
template<typename T,typename H>
Map<T,H>::Node::Node(value_type && other):pair_obj(&other)
{
    //pair_obj = &other;
   //other = nullptr;
}

//I dont need to write the node destructor;
template<typename T,typename H>
Map<T,H>::Node::~Node(){
    delete this->pair_obj;
}
//add const key 
template<typename T,typename H>
Map<T,H>::Map(std::initializer_list<std::pair<Key,Value>> list)
{
    for(auto i :list)
    {      
        this->insert(i);
    }
}
//copy constructor
template<typename T,typename H>
Map<T,H>::Map(const Map& copy)
{
    copy_map(copy.root);
}
//copy constructor helper function.
template<typename T,typename H>
void Map<T,H>::copy_map(Node*n)
{
    if(n == nullptr)return;
    this->insert(*n->pair_obj); 
    copy_map(n->left);
    copy_map(n->right);
}
//Move ctor
template<typename T,typename H>
Map<T,H>::Map(Map&& copy):root(copy.root),head(copy.head),tail(copy.tail)
{
    copy.root = nullptr;
}
//Assignment operator
template<typename T,typename H>
Map<T,H>& Map<T,H>::operator=(const Map<T,H>& other) 
{   
    //std::cout<<"Call"<<'\n';
    if(this!=&other)
    {
        this->delete_all_nodes(this->root);
        copy_map(other.root);
    }
    return *this;
}

//Move assignment operator
template<typename T,typename H>
Map<T,H>& Map<T,H>::operator=(Map<T,H>&&other)
{
    if(this!=&other)
    {
        this->delete_all_nodes(this->root);
        this->root = other.root;
        this->head->next_iter = other.head->next_iter;
        this->tail->prev_iter = other.tail->prev_iter;
        other.root=nullptr; 
        other.head->next_iter = nullptr;
        other.tail->prev_iter = nullptr;
    }
    return *this;
}

//Iter ctor
template<typename T,typename H>
Map<T,H>::Iterator::Iterator(Node *iter_node):iter_node(iter_node){}
//const Iter
template<typename T,typename H>
Map<T,H>::ConstIterator::ConstIterator(const Node *iter_node):iter_node(iter_node){}
//non constant iterator to iterator
template<typename T,typename H>
Map<T,H>::ConstIterator::ConstIterator(const Iterator& other):iter_node(other.iter_node){}
//reverse Iterator ctor
template<typename T,typename H>
Map<T,H>::ReverseIterator::ReverseIterator(Node*iter_node):iter_node(iter_node){}
/*
//copy ctor
Map::Iterator::Iterator(const Iterator& copy):iter_node(new Node(*copy.iter_node->pair_obj)){}
//move ctor
Map::Iterator::Iterator(Iterator &&copy):iter_node(copy.iter_node)
{
copy.iter_node =nullptr; 
}*/
//Iter
template<typename T,typename H>
typename Map<T,H>::Iterator& Map<T,H>::Iterator::operator++()
{   
    
    this->iter_node = this->iter_node->next_iter;
    return *this;
}
//const Iter
template<typename T,typename H>
typename Map<T,H>::ConstIterator& Map<T,H>::ConstIterator::operator++()
{
  
    this->iter_node = this->iter_node->next_iter;
    return *this;
}
//reverse Iterator
template<typename T,typename H>
typename Map<T,H>::ReverseIterator& Map<T,H>::ReverseIterator::operator++()
{

    this->iter_node = this->iter_node->prev_iter;
    return *this;
}
template<typename T,typename H>
typename Map<T,H>::Iterator Map<T,H>::Iterator::operator++(int)
{

    Iterator temp(*this);
    ++(*this);    
    return temp;
}
//const
template<typename T,typename H>
typename Map<T,H>::ConstIterator Map<T,H>::ConstIterator::operator++(int)
{

    ConstIterator temp(*this);
    ++(*this);    
    return temp;
}
//Reverse Iterator
template<typename T,typename H>
typename Map<T,H>::ReverseIterator Map<T,H>::ReverseIterator::operator++(int)
{

    ReverseIterator temp(*this);
    ++(*this);    
    return temp;
}
template<typename T,typename H>
typename Map<T,H>::Iterator& Map<T,H>::Iterator::operator--()
{
    this->iter_node = this->iter_node->prev_iter;
    return *this;
}
template<typename T,typename H>
typename Map<T,H>::Iterator Map<T,H>::Iterator::operator--(int)
{
    Iterator temp(*this);
    --(*this);    
    return temp;
}
//const
template<typename T,typename H>
typename Map<T,H>::ConstIterator& Map<T,H>::ConstIterator::operator--()
{
    this->iter_node = this->iter_node->prev_iter;
    return *this;
}
template<typename T,typename H>
typename Map<T,H>::ConstIterator Map<T,H>::ConstIterator::operator--(int)
{
    ConstIterator temp(*this);
    --(*this);    
    return temp;
}
//reverse Iterator
template<typename T,typename H>
typename Map<T,H>::ReverseIterator& Map<T,H>::ReverseIterator::operator--()
{
    this->iter_node = this->iter_node->next_iter;
    return *this;
}
template<typename T,typename H>
typename Map<T,H>::ReverseIterator Map<T,H>::ReverseIterator::operator--(int)
{
    ReverseIterator temp(*this);
    --(*this);    
    return temp;
}
template<typename T,typename H>
bool Map<T,H>::Iterator::operator==(const Iterator& other) const
{
    return (this->iter_node == other.iter_node);
}
template<typename T,typename H>
bool Map<T,H>::Iterator::operator!=(const Iterator& other) const
{
    return !(this->iter_node == other.iter_node);
}
//const
template<typename T,typename H>
bool Map<T,H>::ConstIterator::operator==(const ConstIterator& other) const
{
    return (this->iter_node == other.iter_node);
}
template<typename T,typename H>
bool Map<T,H>::ConstIterator::operator!=(const ConstIterator& other) const
{
    return !(this->iter_node == other.iter_node);
}

//reverse
template<typename T,typename H>
bool Map<T,H>::ReverseIterator::operator==(const ReverseIterator& other) const
{
    return (this->iter_node == other.iter_node);
}
template<typename T,typename H>
bool Map<T,H>::ReverseIterator::operator!=(const ReverseIterator& other) const
{
    return !(this->iter_node == other.iter_node);
}


//friend function.
/*
template<typename T,typename H>
typename bool Map<T,H>operator==(const Map<T,H>::ConstIterator& c_iter,const Map<T,H>::Iterator &iter)
{
    return (c_iter==c_iter);
}
*/

//Map::Node* find_iterator(Map::Node)
template<typename T,typename H>
typename Map<T,H>::Iterator Map<T,H>::begin()
{
    return Iterator(this->head->next_iter);
}
template<typename T,typename H>
typename Map<T,H>::Iterator Map<T,H>::end()
{
    return Iterator(this->tail);
}
//const
template<typename T,typename H>
typename Map<T,H>::ConstIterator Map<T,H>::begin() const
{
    return ConstIterator(this->head->next_iter);
}
template<typename T,typename H>
typename Map<T,H>::ConstIterator Map<T,H>::end() const
{
    return ConstIterator(this->tail);
}
template<typename T,typename H>
typename Map<T,H>::ReverseIterator Map<T,H>::rbegin() const
{
    return ReverseIterator(this->tail->prev_iter);
}
template<typename T,typename H>
typename Map<T,H>::ReverseIterator Map<T,H>::rend() const
{
    return ReverseIterator(this->head);
}
template<typename T,typename H>
typename Map<T,H>::value_type& Map<T,H>::Iterator::operator*() const
{
    return *(this->iter_node->pair_obj);
}
//const
template<typename T,typename H>
typename Map<T,H>::const_value_type& Map<T,H>::ConstIterator::operator*() const
{
    return *(this->iter_node->pair_obj);
}
//reverse
template<typename T,typename H>
typename Map<T,H>::value_type& Map<T,H>::ReverseIterator::operator*() const
{
    return *(this->iter_node->pair_obj);
}
template<typename T,typename H>
std::size_t Map<T,H>::size() const
{
    //auto length = std::distance(this->begin(),this->end());
    return this->length;
}
template<typename T,typename H>
bool Map<T,H>::empty() const
{
    return(this->root == nullptr ?true:false);
}

template<typename T,typename H>
bool Map<T,H>::operator==(const Map<T,H>& other)const
{
    //std::cout<<"Equality Test\n";
    if(this->size()!=other.size())
    {   
        //std::cout<<"Size not equal\n";
        return false;
    }
    Map::ConstIterator i =other.begin();
    Map::ConstIterator j = this->begin();
    size_t count = this->size();
    while(count!=0)
    {
        if(i.iter_node->pair_obj->first!=j.iter_node->pair_obj->first ||
                i.iter_node->pair_obj->second!=i.iter_node->pair_obj->second)
        {
            //std::cout<<"FALSE\n";
            return false; 
        }
        ++i;
        ++j;
        --count;
    }
    return true;
}
template<typename T,typename H>
bool Map<T,H>::operator!=(const Map<T,H>& other)const
{
    if(*this == other)return false;
    return true;
}

template<typename T,typename H>
typename Map<T,H>::Iterator Map<T,H>::find(const_Key& other)
{
    Node *n  = this->root;
    while(n!=nullptr)
    {
        if(n->pair_obj->first > other)
        {
            n = n->left;
        }
        else if(n->pair_obj->first < other)
        {
            n = n->right;
        }
        else if(n->pair_obj->first == other)
        {
            return (Iterator(n));
        }

    }
    return Iterator(this->tail);
}
template<typename T,typename H>
typename Map<T,H>::ConstIterator Map<T,H>::find(const_Key& other) const
{
    Node *n  = this->root;
    while(n!=nullptr)
    {
        if(n->pair_obj->first > other)
        {
            n = n->left;
        }
        else if(n->pair_obj->first < other)
        {
            n = n->right;
        }
        else if(n->pair_obj->first == other)
        {
            return (ConstIterator(n));
        }
    } 
    return ConstIterator(this->tail);
}
template<typename T,typename H>
typename Map<T,H>::Value& Map<T,H>::at(const_Key& other)
{   
    //std::cout<<"Non Constant At\n";
    Iterator i = find(other);
    if( i == Iterator(this->tail))
    {
        throw std::out_of_range("Value Not Present\n");
    }
    else
    {
        return (i.iter_node->pair_obj->second);
    }
}
template<typename T,typename H>
typename Map<T,H>::const_Value& Map<T,H>::at(const_Key& other) const
{
    //std::cout<<"Constant At\n";
    ConstIterator i = find(other);
    if( i == ConstIterator(this->tail))
    {   
        //std::cout<<"OUT of Range"<<'\n';
        throw std::out_of_range("Value Not Present\n");
    }
    else
    {
        return (i.iter_node->pair_obj->second);
    }
}
template<typename T,typename H>
typename Map<T,H>::Value& Map<T,H>::operator[](const_Key& other)
{    
    Iterator i = find(other);
    if( i == Iterator(this->tail))
    {
       // i = this->insert(std::make_pair(other,0));//need to default construct the value
         i = this->insert({other,Value{}});
    }
    return (i.iter_node->pair_obj->second);
}


template<typename T,typename H>
typename Map<T,H>::Node* Map<T,H>::find_position(Map::Node* n ,Key k)
{
    assert(n!=nullptr);
    if(n->pair_obj->first == k)return n;
    else if(n->pair_obj->first < k)
    {
        if(n->right ==  nullptr)
            return n;
        else
            return find_position(n->right,k);
    }
    else if(n->pair_obj->first > k)
    {
        if(n->left == nullptr)
            return n;
        else
            return find_position(n->left,k);
    }
    return nullptr;
}

template <typename T, typename H>
typename Map<T,H>::Iterator Map<T,H>::insert_helper(Node *new_node)
{
    ++this->length;
    if(this->root == nullptr)
    {   //root added.
        this->root = new_node;
        new_node->type = 'h';        
        new_node->next_iter = this->tail;
        new_node->prev_iter = this->head;
        this->tail->prev_iter = this->root;//line added on monday moring
        this->head->next_iter = this->root; 
        return Iterator(new_node);
    }
    else
    {   
        Node* n = find_position(this->root,new_node->pair_obj->first); 
        if(n->pair_obj->first == new_node->pair_obj->first)
        {  //if duplicate 
            {//create a delete node function for this 
                --this->length;
                delete_node(new_node);
                /*
                   delete new_node->pair_obj;
                   delete new_node;
                   */
            }
            return Iterator(n);
        }
        else if(n->pair_obj->first < new_node->pair_obj->first)
        { //add to right
            n->right =new_node; 
            new_node->parent = n;
            new_node->type= 'r';
            //code to set the prev_iter.
            new_node->prev_iter = n;
            Node *temp = n->next_iter;
            temp->prev_iter = new_node;

            //code to set the next_iter.
            new_node->next_iter = n->next_iter;
            n->next_iter = new_node;
            return Iterator(new_node);

        }
        else if(n->pair_obj->first > new_node->pair_obj->first)
        {   //add to left
            n->left = new_node;
            new_node->parent = n;
            new_node->type = 'l';
#if 1
            //code to set the next_iter.
            new_node->next_iter = n;
            Node* traverse = new_node; 
            do
            {
                traverse = traverse->parent;
            }while(traverse->type == 'l');
            if(traverse->type == 'h')
            {    
                Node *n = new_node->parent->prev_iter ;//begin->next_iter = new_node;//not sure if correct..?   
                n->next_iter = new_node;
                //do notthing
            }
            else if(traverse->type == 'r')
            {
                traverse = traverse->parent;
                if(traverse->pair_obj->first < new_node->pair_obj->first)
                {
                    traverse->next_iter = new_node;
                }
            }

            //code to set the prev_iter
            new_node->prev_iter = n->prev_iter;
            n->prev_iter = new_node;
            return Iterator(new_node);
#endif      
        }
    }
    //traverse all the way left to set the begin node.
    //never reached here.
    throw std::runtime_error("I should never have gotten here");
    exit(0);
}
template<typename T,typename H>
typename Map<T,H>::Iterator Map<T,H>::insert(const_value_type &obj)
{   
    //std::cout<<++i<<'\n';
    Node *new_node = new Node(obj);
    return insert_helper(new_node);
}
#if 0
    ++this->length;
    if(this->root == nullptr)
    {   //root added.
        this->root = new_node;
        new_node->type = 'h';        
        new_node->next_iter = this->tail;
        new_node->prev_iter = this->head;
        this->tail->prev_iter = this->root;//line added on monday moring
        this->head->next_iter = this->root; 
        return Iterator(new_node);
    }
    else
    {   
        Node* n = find_position(this->root,new_node->pair_obj->first); 
        if(n->pair_obj->first == new_node->pair_obj->first)
        {  //if duplicate 
            {//create a delete node function for this 
                --this->length;
                //delete_node(new_node);
                /*
                   delete new_node->pair_obj;
                   delete new_node;
                   */
            }
            return Iterator(n);
        }
        else if(n->pair_obj->first < new_node->pair_obj->first)
        { //add to right
            n->right =new_node; 
            new_node->parent = n;
            new_node->type= 'r';
            //code to set the prev_iter.
            new_node->prev_iter = n;
            Node *temp = n->next_iter;
            temp->prev_iter = new_node;

            //code to set the next_iter.
            new_node->next_iter = n->next_iter;
            n->next_iter = new_node;
            return Iterator(new_node);

        }
        else if(n->pair_obj->first > new_node->pair_obj->first)
        {   //add to left
            n->left = new_node;
            new_node->parent = n;
            new_node->type = 'l';
#if 1
            //code to set the next_iter.
            new_node->next_iter = n;
            Node* traverse = new_node; 
            do
            {
                traverse = traverse->parent;
            }while(traverse->type == 'l');
            if(traverse->type == 'h')
            {    
                Node *n = new_node->parent->prev_iter ;//begin->next_iter = new_node;//not sure if correct..?   
                n->next_iter = new_node;
                //do notthing
            }
            else if(traverse->type == 'r')
            {
                traverse = traverse->parent;
                if(traverse->pair_obj->first < new_node->pair_obj->first)
                {
                    traverse->next_iter = new_node;
                }
            }

            //code to set the prev_iter
            new_node->prev_iter = n->prev_iter;
            n->prev_iter = new_node;
            return Iterator(new_node);
#endif      
        }
    }
    //traverse all the way left to set the begin node.
    //never reached here.
    //throw std::runtime_error("I should never have gotten here");
}
#endif


template<typename T,typename H>
typename Map<T,H>::Iterator Map<T,H>::insert(value_type &&obj)
{   
    //std::cout<<++i<<'\n';
    Node *new_node = new Node(obj);
    return insert_helper(new_node);
}
#if 0
    ++this->length;
    if(this->root == nullptr)
    {   //root added.
        this->root = new_node;
        new_node->type = 'h';        
        new_node->next_iter = this->tail;
        new_node->prev_iter = this->head;
        this->tail->prev_iter = this->root;//line added on monday moring
        this->head->next_iter = this->root; 
        return Iterator(new_node);
    }
    else
    {   
        Node* n = find_position(this->root,new_node->pair_obj->first); 
        if(n->pair_obj->first == new_node->pair_obj->first)
        {  //if duplicate 
            {//create a delete node function for this 
                --this->length;
                //delete_node(new_node);
                /*
                   delete new_node->pair_obj;
                   delete new_node;
                   */
            }
            return Iterator(n);
        }
        else if(n->pair_obj->first < new_node->pair_obj->first)
        { //add to right
            n->right =new_node; 
            new_node->parent = n;
            new_node->type= 'r';
            //code to set the prev_iter.
            new_node->prev_iter = n;
            Node *temp = n->next_iter;
            temp->prev_iter = new_node;

            //code to set the next_iter.
            new_node->next_iter = n->next_iter;
            n->next_iter = new_node;
            return Iterator(new_node);

        }
        else if(n->pair_obj->first > new_node->pair_obj->first)
        {   //add to left
            n->left = new_node;
            new_node->parent = n;
            new_node->type = 'l';
#if 1
            //code to set the next_iter.
            new_node->next_iter = n;
            Node* traverse = new_node; 
            do
            {
                traverse = traverse->parent;
            }while(traverse->type == 'l');
            if(traverse->type == 'h')
            {    
                Node *n = new_node->parent->prev_iter ;//begin->next_iter = new_node;//not sure if correct..?   
                n->next_iter = new_node;
                //do notthing
            }
            else if(traverse->type == 'r')
            {
                traverse = traverse->parent;
                if(traverse->pair_obj->first < new_node->pair_obj->first)
                {
                    traverse->next_iter = new_node;
                }
            }

            //code to set the prev_iter
            new_node->prev_iter = n->prev_iter;
            n->prev_iter = new_node;
            return Iterator(new_node);
#endif      
        }
    }
    //traverse all the way left to set the begin node.
    //never reached here.
    //throw std::runtime_error("I should never have gotten here");
}
#endif
template<typename T,typename H>
void Map<T,H>::remove(const_Key& key)
{
    //std::cout<<"Remove\n";
    Iterator i  = find(key);
    if( i == Iterator(this->tail))
    {
        throw std::out_of_range("Value Not Present\n");
    }    
    if(i!=this->end())
        erase(i);
}
template<typename T,typename H>
void Map<T,H>::print_tree()
{
print_tree_h(this->root);
std::cout<<std::endl;
}
template<typename T,typename H>
void Map<T,H>::print_tree_h(Node *n)
{
    if(n == nullptr)return;
    print_tree_h(n->left);
    //std::cout<<n->pair_obj->first<<n->type<<" \n";
    print_tree_h(n->right);
}
template<typename T,typename H>
void Map<T,H>::erase(Iterator i)
{
    assert(i.iter_node!=this->tail);
    Node* parent = i.iter_node->parent;
    if(i.iter_node->left == nullptr && i.iter_node->right == nullptr)//0 child
    {
        //std::cout<<"zero child";
        if(i.iter_node->type == 'l')
        {   
            assert(parent!=nullptr);
            i.iter_node->parent = nullptr;
            parent->left = nullptr;
            //std::cout<<"end";

        }
        else if(i.iter_node->type == 'r')
        {  
            assert(parent!=nullptr);
            i.iter_node->parent = nullptr;
            parent->right = nullptr;
            
        }
        else if(i.iter_node->type == 'h')
        {
            Node *n = this->root;
            this->root = nullptr;
            delete_node(n);
            --this->length;
            return; 
        }
    }
    else if(i.iter_node->left == nullptr || i.iter_node->right == nullptr)//1 child
    {      
        //std::cout<<"1 child"<<'\n';
        if(i.iter_node->type == 'l' && i.iter_node->left == nullptr)
        {   
            //std::cout<<"Case1"<<'\n';   
            assert(parent!=nullptr);
            parent->left = i.iter_node->right;
            i.iter_node->right->parent = parent;
            i.iter_node->right->type = 'l';
        }
        else if(i.iter_node->type == 'l' && i.iter_node->right == nullptr)
        {   
            //std::cout<<"Case2"<<'\n';   
            assert(parent!=nullptr);
            parent->left = i.iter_node->left;
            i.iter_node->left->parent = parent;
            i.iter_node->left->type = 'l';
            //std::cout<<"endhere"<<'\n';
        }
        else if(i.iter_node->type == 'r' && i.iter_node->left == nullptr)
        {   
            //std::cout<<"Case3"<<'\n';   
            assert(parent!=nullptr);
            parent->right = i.iter_node->right;
            i.iter_node->right->parent = parent;
            i.iter_node->right->type = 'r';
        }
        else if(i.iter_node->type == 'r' && i.iter_node->right == nullptr)
        {   
            //std::cout<<"Case4"<<'\n';   
            assert(parent!=nullptr);
            parent->right = i.iter_node->left;
              i.iter_node->left->parent = parent;  
            i.iter_node->left->type = 'r';

        }
        else if(i.iter_node->type == 'h' && i.iter_node->left == nullptr)
        {   
            //std::cout<<"Case5"<<'\n'; 
            this->root->right->type ='h';
            Node *temp = i.iter_node->right;
            this->root = temp;
         }
        else if(i.iter_node->type == 'h' && i.iter_node->right == nullptr)
        {
            //std::cout<<"Case6"<<'\n';
            this->root->left->type ='h';
            Node *temp = i.iter_node->left;
            this->root = temp;
        }
    }
    else if(i.iter_node->left != nullptr && i.iter_node->right != nullptr)//two child
    {   
        //std::cout<<"2 child" ;  
        value_type *temp = i.iter_node->pair_obj;
        i.iter_node->pair_obj = i.iter_node->next_iter->pair_obj;
        i.iter_node->next_iter->pair_obj = temp;
        erase(i.iter_node->next_iter);
        return;
    }
    set_pointer_after_delete(i);
}
template<typename T,typename H>
void Map<T,H>::set_pointer_after_delete(Iterator i)
{   
    //std::cout<<"set pointer";
    //std::cout<<i.iter_node->pair_obj->first;
    --this->length; 
    assert(i.iter_node!=this->head);
    assert(i.iter_node!=this->tail);
    Node *prev = i.iter_node->prev_iter;
    Node *next = i.iter_node->next_iter;
    Node *current = i.iter_node;    
    assert(next !=nullptr);
    assert(prev!=nullptr);
    prev->next_iter = current->next_iter;
    next->prev_iter = current->prev_iter;
    //delete_node(i.iter_node);
}

#endif//MAP_H_
