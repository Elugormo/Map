#include<iostream>
#include<utility>
#include<string>
#include<cassert>
#include<initializer_list>
//using Key = std::string;
//using const_Key = const std::string;
//using Value =int;
class Map{
    using Key = std::string;
    using Value = int;
    using value_type = std::pair<const Key, Value>;
    using const_value_type = const std::pair<const Key,Value>;
    public:
        Map();
        ~Map();
        Map(std::initializer_list<std::pair<Key,Value>>);
        class Node{
            public:
                Node* left;
                Node* right;
                Node* parent;
                short type;//right or left child
                value_type* pair_obj;
                Node(const value_type &obj);
                ~Node();
        };
        class Iterator{
            public:
            Node *iter_node;
            Iterator(Node *n);//ctor
            Iterator(const Iterator& copy);//copy ctor
            Iterator(Iterator &&copy);//move ctor
            Iterator& operator= (const Iterator&);//copy assignment operator.
            Iterator& operator=(Iterator&&);//Move Assignment operator.
            ~Iterator();
        };
        void insert(const_value_type &obj);
        Node* find_position(Node* ,Key k);
        void delete_all_nodes(Node* n);
        Map(const Map&);//copy ctor
        void copy_map(Node*n);
        Map(Map&&);//move ctor
        Map& operator=(const Map&);//assignment operator
        Map& operator=(Map&&);
    private:
        Node *root;
        Node *begin;
        Node *end;
};

Map::Map():root(nullptr),begin(nullptr),end(nullptr){}

Map::~Map()
{
    this->delete_all_nodes(this->root);
   // delete root;
    delete begin;
    delete end;
    //delete this;
}

void Map::delete_all_nodes(Node *n)
{   if(n == nullptr)
    return;
    delete_all_nodes(n->left);
    delete_all_nodes(n->right);
    delete n->pair_obj;
    delete n;
}
//node ctor
Map::Node::Node(const value_type &obj):left(nullptr),right(nullptr),parent(nullptr),type(0),pair_obj(new value_type(obj)){}

//I dont need to write the node destructor;
Map::Node::~Node(){}
//add const key 
Map::Map(std::initializer_list<std::pair<Key,Value>> list):root(nullptr),begin(nullptr),end(nullptr)
{
    for(auto i :list)
    {      
        this->insert(i);
    }
}
//copy constructor
Map::Map(const Map& copy):root(nullptr),begin(nullptr),end(nullptr)
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
Map::Map(Map&& copy):root(copy.root),begin(copy.begin),end(copy.end)
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
        this->begin = other.begin;
        this->end = other.end;
        other.root=other.begin=other.end=nullptr; 
    }
    return *this;
}
/*
//Iter ctor
Map::Iterator::Iterator(Node *iter_node):iter_node(iter_node){}
//copy ctor
Map::Iterator::Iterator(const Iterator& copy):iter_node(new Node(*copy.iter_node->pair_obj)){}
//move ctor
Map::Iterator::Iterator(Iterator &&copy):iter_node(copy.iter_node)
{
    copy.iter_node =nullptr; 
}
*/
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

void Map::insert(const_value_type &obj)
{    
    Node *n1 = new Node(obj);
    if(this->root == nullptr)
    {   //Node *n1 = new Node(obj); 
        this->root = n1;
        return;
    }
    else
    {   
        Node* n = find_position(this->root,obj.first); 
        if(n->pair_obj->first == obj.first)
        {   
            {//create a delete node function.
            delete n1->pair_obj;
            delete n1;
            }
            return;
        }
        else if(n->pair_obj->first < obj.first)
        { 
            //Node *n1 = new Node(obj);
            n->type = 0;//right node
            n->right =n1; 
            n1->parent = n;
        }
        else if(n->pair_obj->first > obj.first)
        {   
            //Node *n1 = new Node(obj);
            n->type = 1;//left node
            n->left = n1;
            n1->parent = n;
        }
    }
}

int main()
{
    Map m{{"n",1},{"i",2},{"k",3},{"h",4},{"i",5},{"l",6}};  
    //Map m1(std::move(m));
    Map m1 = m;

    return 0;
}
