#include<iostream>
#include<utility>
#include<string>
using Key = std::string;
using Value =int;
class Map{
    public:
        Map();
        ~Map();
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
        Node& find_position(Node& ,Key k);
        Node *root;
        Node *begin;
        Node *end;
};

Map::Map():root(nullptr),begin(nullptr),end(nullptr){}

Map::~Map()
{
    delete root;
    delete begin;
    delete end;
}

Map::Node::Node(std::pair<Key,Value> &obj):left(nullptr),right(nullptr),parent(nullptr),type(0),pair_obj(obj){}

Map::Node::~Node()
{
    delete Map::Node::left;
    delete Map::Node::right;
    delete Map::Node::parent;
}

Map::Node& Map::find_position(Map::Node& n ,Key k)
{
    if(n.pair_obj.first == k)return n;
    else if(n.pair_obj.first > k)
    {
        if(n.right ==  nullptr)
            return n;
        else
            return find_position(*n.left,k);
    }
    else if(n.pair_obj.first < k)
    {
        if(n.left == nullptr)
            return n;
        else
            return find_position(*n.right,k);
    }
}

void Map::insert(std::pair<Key,Value> &obj)
{
    if(this->root == nullptr)
    {   
        *this->root = obj;
    }
    else
    {   
        Key k ="Hello";
        Node& n = find_position(*this->root,k); 
        if(n.pair_obj.first == obj.first);
        else if(n.pair_obj.first > obj.first)
        {   
            n.type = 0;//right node
            *n.right =obj; 
        }
        else if(n.pair_obj.first < obj.first)
        {   
            n.type = 1;//left node
            *n.left = obj;
        }
        

    }
}



int main()
{




    return 0;
}
