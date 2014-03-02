#include<iostream>
#include<utility>
#include<string>
#include<iterator>
#include<cassert>
#include<initializer_list>
#include<stdexcept>

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
        const_Value at(const_Key&) const;
        Value& operator[](const_Key&) const;
    private:
        Node *root = nullptr;
        Node *head = new Node();
        Node *tail = new Node();

        std::size_t length = 0;
};

Map::Map(){}

Map::~Map()
{
    this->delete_all_nodes(this->root);
    /*delete head->pair_obj;
    delete tail->pair_obj;
    delete head;
    delete tail;*/
    delete_node(head);
    delete_node(tail);
}

void Map::delete_node(Node*n)
{
    n->left = nullptr;
    n->right = nullptr;
    n->parent = nullptr;
    n->next_iter = nullptr;
    n->prev_iter = nullptr;
    delete n->pair_obj;
    delete n;
}
void Map::delete_all_nodes(Node *n)
{   if(n == nullptr)
    return;
    delete_all_nodes(n->left);
    delete_all_nodes(n->right);
    delete_node(n);
    /*
    delete n->pair_obj;
    delete n;
    */
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
    return(this->size() == 0 ?true:false);
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
            //new_node->next_iter = n;
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
    Node* parent = i.iter_node->parent;
    //condition need to be handled:
    //if tree has only root;
    //if tree has only 2 element
    //if tree has only 3 element
    if(i.iter_node->left == nullptr && i.iter_node->right == nullptr)//0 child
    {
        std::cout<<"Zero Child\n";
        if(i.iter_node->type == 'l')
        {   
            parent->left = nullptr;
        }
        else if(i.iter_node->type == 'r')
        {   
            parent->right = nullptr;
        }
        else if(i.iter_node->type == 'h')
        {
            this->head->next_iter = nullptr;
            this->tail->prev_iter = nullptr;
        }
    }
    if(i.iter_node->left == nullptr || i.iter_node->right == nullptr)//1 child
    {   
        if(i.iter_node->type == 'l' && i.iter_node->left == nullptr)
        {
            parent->left = i.iter_node->right;
        }
        else if(i.iter_node->type == 'l' && i.iter_node->right == nullptr)
        {
            parent->left = i.iter_node->left;
        }
        else if(i.iter_node->type == 'r' && i.iter_node->left == nullptr)
        {
            parent->right = i.iter_node->right;
        }
        else if(i.iter_node->type == 'r' && i.iter_node->right == nullptr)
        {
            parent->right = i.iter_node->left;
        }
        else if(i.iter_node->type == 'h' && i.iter_node->left == nullptr)
        {
            this->root = i.iter_node->right;
            i.iter_node->type = 'h';
        }
        else if(i.iter_node->type == 'r' && i.iter_node->right == nullptr)
        {
            this->root = i.iter_node->left;
            i.iter_node->type = 'h';
        }
        //delete_node(i.iter_node);
    }
    if(i.iter_node->left != nullptr && i.iter_node->right != nullptr)//two child
    {   
        value_type *temp = i.iter_node->pair_obj;
        i.iter_node->pair_obj = i.iter_node->next_iter->pair_obj;
        //i.iter_node->next_iter->pair_obj = nullptr;
        //erase(i.iter_node->next_iter);
        
    }
    Node *prev = i.iter_node->prev_iter;
    Node *next = i.iter_node->next_iter;
    Node *current = i.iter_node;
    prev->next_iter = current->next_iter;
    next->prev_iter = current->prev_iter;

    //delete_node(i.iter_node);
}










int main()
{
    Map m{{"50",50},{"20",20},{"10",10},{"30",30},{"25",25},{"40",40},{"23",23},{"27",27},{"70",70},{"65",65},{"66",66},{"67",67},{"63",63}};  
    using Key = std::string;
    using Value = int;

    using type = std::pair<const Key, Value>;
    //type a = *(++m.begin());
    //std::cout<<"Iter::"<<a.first;
    //a++;
    //std::cout<<"Iter::"<<a.first;
    //Map m1 {{"50",50},{"65",65}};
    //Map m1(std::move(m));
    //Map m1 = m;
    auto i = m.rbegin();
    auto j = m.rend();
    for(;;)
    {   
        std::cout<<(*i).first<<'\n';
        i++;
        if(i == j)break;
        if(i != j)continue;
    }
    std::cout<<"SIze::"<<m.size()<<'\n';
    //auto k = m.find("a");
    //std::cout<<"Find"<<(*k).second<<'\n';
    //std::cout<<"Value at"<<m.at("a")<<'\n';
    m.remove("10");
    std::cout<<"After removing 10\n";
    i = m.rbegin();
    j = m.rend();
    for(;;)
    {   
        std::cout<<(*i).first<<'\n';
        i++;
        if(i == j)break;
        if(i != j)continue;
    }
    std::cout<<"SIze::"<<m.size()<<'\n';
    m.remove("30");
    std::cout<<"After removing 66\n";
    i = m.rbegin();
    j = m.rend();
    for(;;)
    {   
        std::cout<<(*i).first<<'\n';
        i++;
        if(i == j)break;
        if(i != j)continue;
    }
    std::cout<<"SIze::"<<m.size()<<'\n';
    /*Map m1{{"40",40}};
    //m1.insert({{"30"},{30}});
    //Map::Iteratot j;
    i = m1.begin();
    j = m1.end();
    for(;;)
    {   
        std::cout<<(*i).first<<'\n';
        i++;
        if(i == j)break;
        if(i != j)continue;
    }
*/
    return 0;
}
