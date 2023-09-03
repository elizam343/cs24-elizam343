class MyGrove {
public:
    MyGrove(const char* str);
    MyGrove();
    ~MyGrove();

    void create(const char* str);
    MyGrove* concat(const MyGrove* other) const;
    char charAt(int index) const;
    int len() const;
    MyGrove* substr(int start, int end) const;
    void print() const;

private:
    class Node {
    public:
        Node(const char* data);
        Node(Node* leftNode, Node* rightNode);
        ~Node();

        Node* left;
        Node* right;
        char* data;
        int length;
    };

    Node** nodes;
    int nodeCount;
    int nodeCapacity;
    static const int INITIAL_CAPACITY = 10;

    char charAtNode(const Node* node, int index) const;
    Node* substrNode(const Node* current, int start, int end) const;
};
