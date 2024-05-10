#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Node {
public:
    Node(int data) {
        _data = data;
        _next = nullptr;
        _prev = nullptr;
    }
    int _data;
    Node * _next;
    Node * _prev;
};

class CircularLinkedList {
public:
    void game(int num_nodes, int num_moves);
    CircularLinkedList();
    ~CircularLinkedList();
private:
    Node * _head;
    Node * _tail;
    int _size;
    Node * get_node(int i);      // Returns Node at index i
    void place_stone(int i);
    void play_clockwise(int i);
    void play_anticlockwise(int i);
    void start_board(int num_nodes);
    int get(int i);              // Gets data at index i
    void insert(int i, int x);   // Inserts a new node with value x at i
    void display(int num_nodes);              // Prints the linked list
};

/**
 * @brief default constructor for Circular Linked List Class
 */
CircularLinkedList::CircularLinkedList() {
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}
/**
 * @brief destructor
 */
CircularLinkedList::~CircularLinkedList() {
    Node * curr = _head;
    for (int i = 0; i < _size - 1; i++) {
        Node * next_node = curr->_next;
        delete curr;
        curr = next_node;
    }
    delete curr;
}

/**
 * @brief Returns Node pointer to Node at index i in this linked list
 * 
 * @param i - index
 * @return Node* - node at index i
 */
Node * CircularLinkedList::get_node(int i) {
    Node * curr = _head;
    for (; i > 0; i--) {
        curr = curr->_next;
    }
    return curr;
}

/**
 * @brief Get the int at index i
 * 
 * @param i - index
 * @return int - value at index i
 */
int CircularLinkedList::get(int i) {
    return get_node(i)->_data;
}

/**
 * @brief Inserts a new Node at index i that has value x
 * 
 * @param i index for placing
 * @param x value of placement
 */
void CircularLinkedList::insert(int i, int x) {
    _size++;
    Node * new_node = new Node(x);
    //if the new node is the first node in the linked list
    if (_head == nullptr) {
        _head = new_node;
        _tail = new_node;
        new_node->_next = _tail;
        new_node->_prev = _head;
    }
    //if placing at beginning of linked list
    else if (i == 0) {
        new_node->_next = _head;
        new_node->_prev = _tail;
        _head->_prev = new_node;
        _tail->_next = new_node;
        _head = new_node;
    }
    //if placing at end of linked list
    else if ((_size - 1) == i) {
        //inserting at end of cll
        _tail->_next = new_node;
        new_node->_next = _head;
        new_node->_prev = _tail;
        _tail = new_node;
        _head->_prev = _tail;
        _tail->_next = _head;
    }
    //placing in the middle
    else {
        Node * before = get_node(i - 1);
        Node * after = before->_next;
        before->_next = new_node;
        new_node->_prev = before;
        new_node->_next = after;
        after->_prev = new_node;
    }
}

/**
 * @brief Creates the starting board for the stone game
 * 
 * @param num_nodes number of nodes the game will be played with
 */
void CircularLinkedList::start_board(int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        insert(i,1);
    }
}

/**
 * @brief places a stone for the game
 * @param i - index
 */
void CircularLinkedList::place_stone(int i) {
    Node * curr = get_node(i);
    curr->_data++;
}

/**
 * @brief takes stones from index, and adds them to the next nodes clockwise
 * @param i - index
 */
void CircularLinkedList::play_clockwise(int i) {
    Node * curr = get_node(i);
    int count = curr->_data; //set count to data at node
    curr->_data = 0;
    while (count != 0) { //iterate through linked list while count != 0
        curr = curr->_next;
        if (curr->_data == 0 && count == 1) { //if last stone is placed in empty spot
            count--;
        }
        else {
            curr->_data++;
            count--;
        }
    }
}

/**
 * @brief takes stones from index, and adds them to the next nodes anticlockwise
 * 
 * @param i - index
 */
void CircularLinkedList::play_anticlockwise(int i) {
    Node * curr = get_node(i);
    int count = curr->_data; //set count to data at node
    curr->_data = 0;
    while (count != 0) {
        curr = curr->_prev;
        if (curr->_data == 0 && count == 1) { //if last stone is placed in empty spot
            count--;
        }
        else {
            curr->_data++;
            count--;
        }
    }
}

/**
 * @brief creates the game, and follows the input commands, outputs the final board
 * 
 * @param num_nodes - number of nodes in game
 * @param num_moves - number of moves for the game
 */
void CircularLinkedList::game(int num_nodes, int num_moves) {
    start_board(num_nodes);
    string command;
    int arg;
    while (num_moves != 0) {
        cin >> command >> arg;
        if (command == "place") {
            place_stone(arg);
        }
        else if (command == "clock") {
            play_clockwise(arg);
        } 
        else { 
            (command == "anti");
            play_anticlockwise(arg);
        }
        num_moves--;
    }
    display(num_nodes);
}

/**
 * @brief Prints the linked list
 * @param num_nodes - number of nodes in linked list
 */
void CircularLinkedList::display(int num_nodes) {
    Node * curr = _head;
    for (int i = 0; i < num_nodes; i++) {
        cout << curr->_data;
        if (curr != _tail)
            cout << " ";
        curr = curr->_next;
        if (curr == _head)
            break;
    }
    cout << endl;
}

int main() {
    CircularLinkedList cll;
    string node;
    int num_nodes = 0;
    cin >> node >> num_nodes;
    int num_moves = 0;
    string move;
    cin >> move >> num_moves;
    cll.game(num_nodes, num_moves);
    return 0;
}
