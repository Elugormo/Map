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
    else if(n.pair_obj.first < k)
    {
        if(n.right ==  nullptr)
            return n;
        else
            return find_position(*n.right,k);
    }
    else if(n.pair_obj.first > k)
    {
        if(n.left == nullptr)
            return n;
        else
            return find_position(*n.left,k);
    }
}

void Map::insert(std::pair<Key,Value> &obj)
{    
    Node *n1 = new Node(obj);
    if(this->root == nullptr)
    {   
        std::cout<<"hie"<<'\n';
       // Node *n1 = new Node(obj);
        this->root = n1;
        return;
    }
    else
    {   
        Key k ="Hello";
        Node& n = find_position(*this->root,obj.first); 
        if(n.pair_obj.first == obj.first);
        else if(n.pair_obj.first < obj.first)
        {   
            n.type = 0;//right node
            n.right =n1; 
        }
        else if(n.pair_obj.first > obj.first)
        {   
            n.type = 1;//left node
            n.left = n1;
        }
    }
}



int main()
{
    Map m;
    std::pair<Key,Value> p1("x",14);
    std::pair<Key,Value> p2("e",13);
    std::pair<Key,Value> p3("y",14);
    std::pair<Key,Value> p4("i",13);
    std::pair<Key,Value> p5("j",14);
    std::pair<Key,Value> p6("f",13);
    std::pair<Key,Value> p7("d",14);
    std::pair<Key,Value> p8("a",13);
 
 
    //std::cout<<"Value::"<<p1.first<<'\n';
    m.insert(p1);
    m.insert(p2);
    m.insert(p3);
    m.insert(p4);
    m.insert(p5);
    m.insert(p6);
    m.insert(p7);
    m.insert(p8);
    
    std::cout<<m.root->pair_obj.first<<'\n';
    std::cout<<m.root->left->pair_obj.first<<'\n';
    

    return 0;
}
