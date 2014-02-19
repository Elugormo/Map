#include<iostream>
#include<utility>
#include<string>
class Map{
    public:
        Map();
        ~Map();
    private:
        class Node{
            public:
                Node* left;
                Node* right;
                Node* parent;
                short type;//right or left child
                std::pair<int,int> obj;
                //constructor
                Node(std::pair<int,int> &obj);
                //destructor
                ~Node();
        };
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

Map::Node::Node(std::pair<int,int> &obj):left(nullptr),right(nullptr),parent(nullptr),type(0),obj(obj){}

Map::Node::~Node()
{
    delete Map::Node::left;
    delete Map::Node::right;
    delete Map::Node::parent;
}

int main()
{




    return 0;
}
