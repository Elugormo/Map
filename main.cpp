#include<iostream>
#include<utility>
#include<string>
#include<cassert>
#include<initializer_list>
using Key = std::string;
using const_Key = const std::string;
using Value =int;
class Map{
    public:
        Map();
        ~Map();
        Map(std::initializer_list<std::pair<Key,Value>>);
        void insert(std::pair<Key,Value> &obj);
        class Node{
            public:
                Node* left;
                Node* right;
                Node* parent;
                short type;//right or left child
                std::pair<Key,Value> pair_obj;
                Node(std::pair<Key,Value> &obj);
                ~Node();
        };
        Node* find_position(Node* ,Key k);
        void delete_all_nodes();
        void delete_all_nodes(Node* n);
        Node *root;
        Node *begin;
        Node *end;
};

Map::Map():root(nullptr),begin(nullptr),end(nullptr){}

Map::~Map()
{
    this->delete_all_nodes();
}

void Map::delete_all_nodes()
{
    this->delete_all_nodes(this->root);
}

void Map::delete_all_nodes(Node *n)
{   if(n == nullptr)
        return;
    delete_all_nodes(n->left);
    delete_all_nodes(n->right);
    delete n;
}

Map::Node::Node(std::pair<Key,Value> &obj):left(nullptr),right(nullptr),parent(nullptr),type(0),pair_obj(obj){}

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


Map::Node* Map::find_position(Map::Node* n ,Key k)
{
    assert(n!=nullptr);
    if(n->pair_obj.first == k)return n;
    else if(n->pair_obj.first < k)
    {
        if(n->right ==  nullptr)
            return n;
        else
            return find_position(n->right,k);
    }
    else if(n->pair_obj.first > k)
    {
        if(n->left == nullptr)
            return n;
        else
            return find_position(n->left,k);
    }

}

void Map::insert(std::pair<Key,Value> &obj)
{    
    //Node *n1 = new Node(obj);
    if(this->root == nullptr)
    {   Node *n1 = new Node(obj); 
        this->root = n1;
        return;
    }
    else
    {   
        Node* n = find_position(this->root,obj.first); 
        if(n->pair_obj.first == obj.first)
        {  
            return;
        }
        else if(n->pair_obj.first < obj.first)
        { 
            Node *n1 = new Node(obj);
            n->type = 0;//right node
            n->right =n1; 
            n1->parent = n;
        }
        else if(n->pair_obj.first > obj.first)
        {   
            Node *n1 = new Node(obj);
            n->type = 1;//left node
            n->left = n1;
            n1->parent = n;
        }
    }
}



int main()
{
    Map m{{"n",1},{"i",2},{"k",3},{"h",4},{"i",5},{"l",6}};  
    return 0;
}
