// AVL tree implementation in C++

#include <iostream>
using namespace std;

class AVLNode
{
public:
    int key;
    AVLNode *left;
    AVLNode *right;
    int height;
};

int max(int a, int b);

// Calculate height
int height(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// New AVLNode creation
AVLNode *newAVLNode(int key)
{
    AVLNode *AVLNode = new AVLNode();
    AVLNode->key = key;
    AVLNode->left = NULL;
    AVLNode->right = NULL;
    AVLNode->height = 1;
    return (AVLNode);
}

// Rotate right
AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    return x;
}

// Rotate left
AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    return y;
}

// Get the balance factor of each AVLNode
int getBalanceFactor(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) -
           height(N->right);
}

// Insert a AVLNode
AVLNode *insertAVLNode(AVLNode *AVLNode, int key)
{
    // Find the correct postion and insert the AVLNode
    if (AVLNode == NULL)
        return (newAVLNode(key));
    if (key < AVLNode->key)
        AVLNode->left = insertAVLNode(AVLNode->left, key);
    else if (key > AVLNode->key)
        AVLNode->right = insertAVLNode(AVLNode->right, key);
    else
        return AVLNode;

    // Update the balance factor of each AVLNode and
    // balance the tree
    AVLNode->height = 1 + max(height(AVLNode->left),
                              height(AVLNode->right));
    int balanceFactor = getBalanceFactor(AVLNode);
    if (balanceFactor > 1)
    {
        if (key < AVLNode->left->key)
        {
            return rightRotate(AVLNode);
        }
        else if (key > AVLNode->left->key)
        {
            AVLNode->left = leftRotate(AVLNode->left);
            return rightRotate(AVLNode);
        }
    }
    if (balanceFactor < -1)
    {
        if (key > AVLNode->right->key)
        {
            return leftRotate(AVLNode);
        }
        else if (key < AVLNode->right->key)
        {
            AVLNode->right = rightRotate(AVLNode->right);
            return leftRotate(AVLNode);
        }
    }
    return AVLNode;
}

// AVLNode with minimum value
AVLNode *AVLNodeWithMimumValue(AVLNode *AVLNode)
{
    AVLNode *current = AVLNode;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a AVLNode
AVLNode *deleteAVLNode(AVLNode *root, int key)
{
    // Find the AVLNode and delete it
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteAVLNode(root->left, key);
    else if (key > root->key)
        root->right = deleteAVLNode(root->right, key);
    else
    {
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            AVLNode *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            AVLNode *temp = AVLNodeWithMimumValue(root->right);
            root->key = temp->key;
            root->right = deleteAVLNode(root->right,
                                        temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each AVLNode and
    // balance the tree
    root->height = 1 + max(height(root->left),
                           height(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1)
    {
        if (getBalanceFactor(root->left) >= 0)
        {
            return rightRotate(root);
        }
        else
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1)
    {
        if (getBalanceFactor(root->right) <= 0)
        {
            return leftRotate(root);
        }
        else
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

// Print the tree
void printTree(AVLNode *root, string indent, bool last)
{
    if (root != nullptr)
    {
        cout << indent;
        if (last)
        {
            cout << "R----";
            indent += "   ";
        }
        else
        {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main()
{
    AVLNode *root = NULL;
    root = insertAVLNode(root, 33);
    root = insertAVLNode(root, 13);
    root = insertAVLNode(root, 53);
    root = insertAVLNode(root, 9);
    root = insertAVLNode(root, 21);
    root = insertAVLNode(root, 61);
    root = insertAVLNode(root, 8);
    root = insertAVLNode(root, 11);
    printTree(root, "", true);
    root = deleteAVLNode(root, 13);
    cout << "After deleting " << endl;
    printTree(root, "", true);
}