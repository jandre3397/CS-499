#include <iostream>
#include <string>
#include <algorithm> // For std::max
using namespace std;

struct Node {
    string bidId;
    string title;
    double amount;
    Node* left;
    Node* right;
    int height;

    Node() : amount(0.0), left(nullptr), right(nullptr), height(1) {}
    Node(string id, string t, double a) : bidId(id), title(t), amount(a), left(nullptr), right(nullptr), height(1) {}
};

class BinarySearchTree {
private:
    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insert(Node* node, string bidId, string title, double amount) {
        if (node == nullptr) {
            return new Node(bidId, title, amount);
        }

        if (bidId < node->bidId) {
            node->left = insert(node->left, bidId, title, amount);
        } else if (bidId > node->bidId) {
            node->right = insert(node->right, bidId, title, amount);
        } else {
            return node;
        }

        updateHeight(node);
        int balance = getBalance(node);

        if (balance > 1 && bidId < node->left->bidId)
            return rotateRight(node);

        if (balance < -1 && bidId > node->right->bidId)
            return rotateLeft(node);

        if (balance > 1 && bidId > node->left->bidId) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && bidId < node->right->bidId) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->bidId << " | " << node->title << " | $" << node->amount << endl;
            inOrder(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void Insert(string bidId, string title, double amount) {
        root = insert(root, bidId, title, amount);
    }

    void DisplayInOrder() {
        inOrder(root);
    }
};
