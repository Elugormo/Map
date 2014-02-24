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
                Node* left = nullptr;
                Node* right = nullptr;
                Node* parent = nullptr;
                Node* next_iter = nullptr;
                Node* prev_iter = nullptr;
                char type = 'e';//right or left child
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
        Node *root = nullptr;
        Node *begin = nullptr;
        Node *end = nullptr;
        std::size_t length = 0;
};

Map::Map(){}

Map::~Map()
{
    this->delete_all_nodes(this->root);
    delete begin;
    delete end;
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
Map::Node::Node(const value_type &obj):pair_obj(new value_type(obj)){}

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


//Map::Node* find_iterator(Map::Node)



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

    Node *new_node = new Node(obj);
    ++this->length;
    if(this->root == nullptr)
    {   //root added.
        Node *begin = new Node(obj);
        Node *end = new Node(obj);
        this->root = new_node;
        new_node->type = 'h';
        //next_iter point to begin and end node. with type = e.
        new_node->next_iter = end;
        new_node->prev_iter = begin;
        return;
    }
    else
    {   
        Node* n = find_position(this->root,obj.first); 
        if(n->pair_obj->first == obj.first)
        {  //if duplicate 
            {//create a delete node function for this 
            --this->length;
            delete new_node->pair_obj;
            delete new_node;
            }
            return;
        }
        else if(n->pair_obj->first < obj.first)
        { //add to right
            //Node *n1 = new Node(obj);
            //n->type = 'r';//right node
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
            
        }
        else if(n->pair_obj->first > obj.first)
        {   //add to left
            //Node *n1 = new Node(obj);
            //n->type = 'l';//left node
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
#endif
        }
    }
    //traverse all the way left to set the begin node.
}

int main()
{
    Map m{{"50",50},{"20",20},{"10",10},{"30",30},{"25",25},{"40",40},{"23",23},{"27",27},{"70",70},{"65",65},{"66",66},{"67",67},{"63",63}};  
    Map m1 {{"50",50},{"65",65}};
    //Map m1(std::move(m));
    //Map m1 = m;

    return 0;
}
