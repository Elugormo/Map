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
#include<map>


//using Key = std::string;
//using const_Key = const std::string;
//using Value =int;

class Map{
    using Key = std::string;
    using const_Key = const std::string;
    using Value = int;
    using const_Value = const int;
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
    std::size_t size() const;
    bool empty() const; 
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
};

Map::Map(){}

Map::~Map()
{
    this->print_tree();
    if(this->root!=nullptr)
    {
        this->delete_all_nodes(this->root);
    }
    assert(this->head!=nullptr);
    delete_node(this->head);
    assert(this->tail!=nullptr);
    delete_node(this->tail);
    delete_node(this->root);
}

void Map::delete_node(Node*n)
{
    //assert(n != nullptr);
    if(n == nullptr)
    {
        return;
    }
    if(n->pair_obj!= nullptr)return;
    if(n->type == 'h')
    {
        this->head->next_iter=this->tail;
        this->tail->prev_iter=this->head;
    } 
    if(n!=nullptr)
    delete n->pair_obj;
    delete n;
    n = nullptr;
}
void Map::delete_all_nodes(Node *n)
{   
    if(n == nullptr)
        return;
    delete_all_nodes(n->left);
    delete_all_nodes(n->right);
    delete_node(n);
}
Map::Node::Node():pair_obj(new value_type()){}
//node ctor
Map::Node::Node(const_value_type &obj):pair_obj(new value_type(obj)){}

//I dont need to write the node destructor;
Map::Node::~Node(){}
//add const key 
Map::Map(std::initializer_list<std::pair<Key,Value>> list)
{
    for(auto i :list)
    {      
        this->insert(i);
    }
}
//copy constructor
Map::Map(const Map& copy)
{
    copy_map(copy.root);
}
//copy constructor helper function.
void Map::copy_map(Node*n)
{
    if(n == nullptr)return;
    this->insert(*n->pair_obj); 
    copy_map(n->left);
    copy_map(n->right);
}
//Move ctor
Map::Map(Map&& copy):root(copy.root),head(copy.head),tail(copy.tail)
{
    copy.root = nullptr;
}
//Assignment operator
Map& Map::operator=(const Map& other) 
{
    if(this!=&other)
    {
        this->delete_all_nodes(this->root);
        copy_map(other.root);
    }
    return *this;
}

//Move assignment operator
Map& Map::operator=(Map&&other)
{
    if(this!=&other)
    {
        this->delete_all_nodes(this->root);
        this->root = other.root;
        this->head = other.head;
        this->tail = other.tail;
        other.root=other.tail=nullptr; 
    }
    return *this;
}

//Iter ctor
Map::Iterator::Iterator(Node *iter_node):iter_node(iter_node){}
//const Iter
Map::ConstIterator::ConstIterator(const Node *iter_node):iter_node(iter_node){}
//non constant iterator to iterator
Map::ConstIterator::ConstIterator(const Iterator& other):iter_node(other.iter_node){}
//reverse Iterator ctor
Map::ReverseIterator::ReverseIterator(Node*iter_node):iter_node(iter_node){}



/*
//copy ctor
Map::Iterator::Iterator(const Iterator& copy):iter_node(new Node(*copy.iter_node->pair_obj)){}
//move ctor
Map::Iterator::Iterator(Iterator &&copy):iter_node(copy.iter_node)
{
copy.iter_node =nullptr; 
}

*/
//Iter
Map::Iterator& Map::Iterator::operator++()
{   
    
    this->iter_node = this->iter_node->next_iter;
    return *this;
}
//const Iter
Map::ConstIterator& Map::ConstIterator::operator++()
{
  
    this->iter_node = this->iter_node->next_iter;
    return *this;
}
//reverse Iterator
Map::ReverseIterator& Map::ReverseIterator::operator++()
{

    this->iter_node = this->iter_node->prev_iter;
    return *this;
}
Map::Iterator Map::Iterator::operator++(int)
{

    Iterator temp(*this);
    ++(*this);    
    return temp;
}
//const
Map::ConstIterator Map::ConstIterator::operator++(int)
{

    ConstIterator temp(*this);
    ++(*this);    
    return temp;
}
//Reverse Iterator
Map::ReverseIterator Map::ReverseIterator::operator++(int)
{

    ReverseIterator temp(*this);
    ++(*this);    
    return temp;
}
Map::Iterator& Map::Iterator::operator--()
{
    this->iter_node = this->iter_node->prev_iter;
    return *this;
}

Map::Iterator Map::Iterator::operator--(int)
{
    Iterator temp(*this);
    --(*this);    
    return temp;
}
//const
Map::ConstIterator& Map::ConstIterator::operator--()
{
    this->iter_node = this->iter_node->prev_iter;
    return *this;
}

Map::ConstIterator Map::ConstIterator::operator--(int)
{
    ConstIterator temp(*this);
    --(*this);    
    return temp;
}
//reverse Iterator
Map::ReverseIterator& Map::ReverseIterator::operator--()
{
    this->iter_node = this->iter_node->next_iter;
    return *this;
}

Map::ReverseIterator Map::ReverseIterator::operator--(int)
{
    ReverseIterator temp(*this);
    --(*this);    
    return temp;
}
bool Map::Iterator::operator==(const Iterator& other) const
{
    return (this->iter_node == other.iter_node);
}

bool Map::Iterator::operator!=(const Iterator& other) const
{
    return !(this->iter_node == other.iter_node);
}
//const
bool Map::ConstIterator::operator==(const ConstIterator& other) const
{
    return (this->iter_node == other.iter_node);
}

bool Map::ConstIterator::operator!=(const ConstIterator& other) const
{
    return !(this->iter_node == other.iter_node);
}

//reverse
bool Map::ReverseIterator::operator==(const ReverseIterator& other) const
{
    return (this->iter_node == other.iter_node);
}

bool Map::ReverseIterator::operator!=(const ReverseIterator& other) const
{
    return !(this->iter_node == other.iter_node);
}




//Map::Node* find_iterator(Map::Node)
Map::Iterator Map::begin()
{
    return Iterator(this->head->next_iter);
}

Map::Iterator Map::end()
{
    return Iterator(this->tail);
}
//const
Map::ConstIterator Map::begin() const
{
    return ConstIterator(this->head->next_iter);
}

Map::ConstIterator Map::end() const
{
    return ConstIterator(this->tail);
}

Map::ReverseIterator Map::rbegin() const
{
    return ReverseIterator(this->tail->prev_iter);
}

Map::ReverseIterator Map::rend() const
{
    return ReverseIterator(this->head);
}


Map::value_type& Map::Iterator::operator*() const
{
    return *(this->iter_node->pair_obj);
}
//const
Map::const_value_type& Map::ConstIterator::operator*() const
{
    return *(this->iter_node->pair_obj);
}
//reverse
Map::value_type& Map::ReverseIterator::operator*() const
{
    return *(this->iter_node->pair_obj);
}

std::size_t Map::size() const
{
    //auto length = std::distance(this->begin(),this->end());
    return this->length;
}

bool Map::empty() const
{
    return(this->root == nullptr ?true:false);
}


bool Map::operator==(const Map& other)const
{
    std::cout<<"Equality Test\n";
    if(this->size()!=other.size())
    {   
        std::cout<<"Size not equal\n";
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
            std::cout<<"FALSE\n";
            return false; 
        }
        ++i;
        ++j;
        --count;
    }
    return true;
}

bool Map::operator!=(const Map& other)const
{
    if(*this == other)return false;
    return true;
}


Map::Iterator Map::find(const_Key& other)
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

Map::ConstIterator Map::find(const_Key& other) const
{
    return ConstIterator(this->find(other));
}

Map::Value& Map::at(const_Key& other)
{
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

Map::const_Value& Map::at(const_Key& other) const
{
    //std::cout<<"return";
    ConstIterator i = find(other);
    if( i == ConstIterator(this->tail))
    {
        throw std::out_of_range("Value Not Present\n");
    }
    else
    {
        return (i.iter_node->pair_obj->second);
    }
}
Map::Value& Map::operator[](const_Key& other)
{    
    Iterator i = find(other);
    if( i == Iterator(this->tail))
    {
        i = this->insert(make_pair(other,0));//need to default construct the value

    }
    return (i.iter_node->pair_obj->second);
}



Map::Node* Map::find_position(Map::Node* n ,Key k)
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

Map::Iterator Map::insert(const_value_type &obj)
{   
    Node *new_node = new Node(obj);
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
        Node* n = find_position(this->root,obj.first); 
        if(n->pair_obj->first == obj.first)
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
        else if(n->pair_obj->first < obj.first)
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
        else if(n->pair_obj->first > obj.first)
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
}
void Map::remove(const_Key& key)
{
    std::cout<<"Remove\n";
    Iterator i  = find(key);
    if( i == Iterator(this->tail))
    {
        throw std::out_of_range("Value Not Present\n");
    }    
    if(i!=this->end())
        erase(i);
}

void Map::print_tree()
{
print_tree_h(this->root);
std::cout<<std::endl;
}

void Map::print_tree_h(Node *n)
{
    if(n == nullptr)return;
    print_tree_h(n->left);
    std::cout<<n->pair_obj->first<<n->type<<" \n";
    print_tree_h(n->right);
}
void Map::erase(Iterator i)
{
    assert(i.iter_node!=this->tail);
    Node* parent = i.iter_node->parent;
    if(i.iter_node->left == nullptr && i.iter_node->right == nullptr)//0 child
    {
        std::cout<<"zero child";
        if(i.iter_node->type == 'l')
        {   
            assert(parent!=nullptr);
            i.iter_node->parent = nullptr;
            parent->left = nullptr;
            std::cout<<"end";

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
        std::cout<<"1 child"<<'\n';
        if(i.iter_node->type == 'l' && i.iter_node->left == nullptr)
        {   
            std::cout<<"Case1"<<'\n';   
            assert(parent!=nullptr);
            parent->left = i.iter_node->right;
            i.iter_node->right->parent = parent;
            i.iter_node->right->type = 'l';
        }
        else if(i.iter_node->type == 'l' && i.iter_node->right == nullptr)
        {   
            std::cout<<"Case2"<<'\n';   
            assert(parent!=nullptr);
            parent->left = i.iter_node->left;
            i.iter_node->left->parent = parent;
            i.iter_node->left->type = 'l';
            std::cout<<"endhere"<<'\n';
        }
        else if(i.iter_node->type == 'r' && i.iter_node->left == nullptr)
        {   
            std::cout<<"Case3"<<'\n';   
            assert(parent!=nullptr);
            parent->right = i.iter_node->right;
            i.iter_node->right->parent = parent;
            i.iter_node->right->type = 'r';
        }
        else if(i.iter_node->type == 'r' && i.iter_node->right == nullptr)
        {   
            std::cout<<"Case4"<<'\n';   
            assert(parent!=nullptr);
            parent->right = i.iter_node->left;
              i.iter_node->left->parent = parent;  
            i.iter_node->left->type = 'r';

        }
        else if(i.iter_node->type == 'h' && i.iter_node->left == nullptr)
        {   
            std::cout<<"Case5"<<'\n'; 
            this->root->right->type ='h';
            Node *temp = i.iter_node->right;
            this->root = temp;
         }
        else if(i.iter_node->type == 'h' && i.iter_node->right == nullptr)
        {
            std::cout<<"Case6"<<'\n';
            this->root->left->type ='h';
            Node *temp = i.iter_node->left;
            this->root = temp;
        }
    }
    else if(i.iter_node->left != nullptr && i.iter_node->right != nullptr)//two child
    {   
        std::cout<<"2 child" ;  
        value_type *temp = i.iter_node->pair_obj;
        i.iter_node->pair_obj = i.iter_node->next_iter->pair_obj;
        i.iter_node->next_iter->pair_obj = temp;
        erase(i.iter_node->next_iter);
        return;
    }
    set_pointer_after_delete(i);
}
void Map::set_pointer_after_delete(Iterator i)
{   
    std::cout<<"set pointer";
    std::cout<<i.iter_node->pair_obj->first;
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
    delete_node(i.iter_node);
}

void stress(int stress_size) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<unsigned int> dist(0, 122223);

    Map m;

    for(int i = 0; i < stress_size; ++i) {
        auto g = dist(gen);
        m.insert({std::to_string(g), g});
    }
    m.print_tree();
    int num_erases = gen() % m.size();
    for(int i = 0; i < num_erases; ++i) {
        //select a random element
        int choice = gen() % m.size();
        auto iter = std::begin(m);
        for (int j = 0; j < choice; ++j) {
           
            ++iter;
        }

        m.erase(iter);
        auto g = dist(gen);
        m.insert({std::to_string(g), g});
        m.print_tree();
    }
        
        for(int i = 0 ;i < 100 ;i++)
        {
            auto g = dist(gen);
            m[std::to_string(g)] = g;
        }
        m.print_tree();
}

int main()
{
#if 0
    Map m{{"50",1},{"20",2},{"10",3},{"30",4},{"25",5},{"40",6},{"23",7},{"27",27},{"70",7},{"65",6},{"66",6},{"67",7},{"63",3}};  
    
    int count = 14;
    m.remove("20");
    auto i = m.begin();
    std::cout<<"\nIterator Printing::\n";
    while(1)
    {
        --count;
        if(count == 0)break;
        std::cout<<(*i).first<<" ";
        i++;
    }
    std::cout<<"\nRecursive Printitng::\n";
    m.print_tree();
    std::cout<<"20 removed";
    m.remove("23");
    m.remove("25");
    m.remove("27");
    m.remove("30");
    m.remove("40");
    m.remove("50");
    m.remove("65");
    //std::cout<<"lllll";
    i = m.begin();
    std::cout<<"\nIterator Printing::\n";
    while(1)
    {
        --count;
        if(count == 0)break;
        std::cout<<(*i).first<<"\n ";
        if(i == m.end())break;
        i++;
    }
    std::cout<<"\nRecursive Printitng::\n";
    m.print_tree();
#endif
    stress(5);
    //access_by_key();
    return 0;
    }
