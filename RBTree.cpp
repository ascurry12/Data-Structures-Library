#include <iostream>
using namespace std;

template <typename keytype, typename valuetype>
class Node {
    public:
        Node *parent, *left, *right;
        bool color; // 0 = black, 1 = red
        keytype key;
        valuetype value;
        int subTreeSize;

        // default node
        Node() {
            parent = left = right = nullptr;
            color = 0;
            subTreeSize = 1;
        }
        // nil
        Node(int nilIndicator) {
            parent = left = right = nullptr;
            color = 0;
            subTreeSize = 0;
        } 
        // node w/ values 
        Node(keytype k, valuetype v) {
            parent = left = right = nullptr;
            key = k;
            value = v;
            color = 0;
            subTreeSize = 1;
        } 

        ~Node() {

        }
};

template <typename keytype, typename valuetype>
class RBTree {
    private:
        Node<keytype, valuetype> *root, *nil;

        void leftRotate(Node<keytype, valuetype> *x) {
            Node<keytype, valuetype> *y;
            y = x->right;
            x->right = y->left;
            if (y->left != nil) {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nil) {
                root = y;
            }
            else if (x == x->parent->left) {
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
            y->subTreeSize = x->subTreeSize;
            x->subTreeSize = x->left->subTreeSize + x->right->subTreeSize + 1;
        }
        
        void rightRotate(Node<keytype, valuetype> *x) {
            Node<keytype, valuetype> *y;
            y = x->left;
            x->left = y->right;
            if (y->right != nil) {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nil) {
                root = y;
            }
            else if (x == x->parent->right) {
                x->parent->right = y;
            }
            else {
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;
            y->subTreeSize = x->subTreeSize;
            x->subTreeSize = x->left->subTreeSize + x->right->subTreeSize + 1;
        }

        void insertFixup(Node<keytype, valuetype> *z) {
            Node<keytype, valuetype> *y;
            while (z->parent->color == 1) {
                if (z->parent == z->parent->parent->left) {
                    y = z->parent->parent->right;
                    if (y->color == 1) {
                        z->parent->color = 0;
                        y->color = 0;
                        z->parent->parent->color = 1;
                        z = z->parent->parent;
                    }
                    else {
                        if (z == z->parent->right) {
                            z = z->parent;
                            leftRotate(z);
                        }
                        z->parent->color = 0;
                        z->parent->parent->color = 1;
                        rightRotate(z->parent->parent);
                    }
                }
                else {
                    y = z->parent->parent->left;
                    if (y->color == 1) {
                        z->parent->color = 0;
                        y->color = 0;
                        z->parent->parent->color = 1;
                        z = z->parent->parent;
                    }
                    else {
                        if (z == z->parent->left) {
                            z = z->parent;
                            rightRotate(z);
                        }
                        z->parent->color = 0;
                        z->parent->parent->color = 1;
                        leftRotate(z->parent->parent);
                    }
                }
            }
            root->color = 0;
        }

        void deleteFixup(Node<keytype, valuetype> *x) {
            Node<keytype, valuetype> *w;
            while (x != root && x->color == 0) {
                if (x == x->parent->left) {
                    w = x->parent->right;
                    if (w->color == 1) {
                        w->color = 0;
                        x->parent->color = 1;
                        leftRotate(x->parent);
                        w = x->parent->right;
                    }
                    if (w->left->color == 0 && w->right->color == 0) {
                        w->color = 1;
                        x = x->parent;
                    }
                    else if (w->right->color == 0) {
                        w->left->color = 0;
                        w->color = 1;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
                else {
                    w = x->parent->left;
                    if (w->color == 1) {
                        w->color = 0;
                        x->parent->color = 1;
                        rightRotate(x->parent);
                        w = x->parent->left;
                    }
                    if (w->right->color == 0 && w->left->color == 0) {
                        w->color = 1;
                        x = x->parent;
                    }
                    else if (w->left->color == 0) {
                        w->right->color = 0;
                        w->color = 1;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
            x->color = 0;
        }

        void transplant(Node<keytype, valuetype> *u, Node<keytype, valuetype> *v) {
            if (u->parent == nil) {
                root = v;
            }
            else if (u == u->parent->left) {
                u->parent->left = v;
            }
            else {
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        Node<keytype, valuetype> *treeMinimum(Node<keytype, valuetype> *x) {
            while (x->left != nil) {
                x = x->left;
            }
            return x;
        }
        Node<keytype, valuetype> *treeMaximum(Node<keytype, valuetype> *x) {
            while (x->right != nil) {
                x = x->right;
            }
            return x;
        }

        Node<keytype, valuetype> *searchHelper(keytype k) {
            Node<keytype, valuetype> *y;
            y = root;
            while (y->key != k) {
                    if (y != nil) {
                        if (y->key > k) {
                            y = y->left;
                        }
                        else {
                            y = y->right;
                        }
                    }
                    if (y == nil) {
                        return nil;
                    }
                } 
            return y;
        }

        Node<keytype, valuetype> *findSuccessor(keytype k) {
            Node<keytype, valuetype> *suc = nil;
            Node<keytype, valuetype> *x = searchHelper(k);
            if (x->right != nil) {
                return treeMinimum(x->right);
            }
            suc = x->parent;
            while (suc != nil && x == suc->right) {
                x = suc;
                suc = suc->parent;
            }
            return suc;
        }
        Node<keytype, valuetype> *findPredecessor(keytype k) {
            Node<keytype, valuetype> *pre = nil;
            Node<keytype, valuetype> *x = searchHelper(k);
            if (x->left != nil) {
                return treeMaximum(x->left);
            }
            pre = x->parent;
            while (pre != nil && x == pre->left) {
                x = pre;
                pre = pre->parent;
            }
            return pre;
        }

        keytype selectHelper(Node<keytype, valuetype> *x, int i) {
            int r = x->left->subTreeSize + 1;
            if (i == r) {
                return x->key;
            }
            else if (i < r) {
                return selectHelper(x->left, i);
            }
            else {
                return selectHelper(x->right, i - r);
            }
        }

        int rankHelper(Node<keytype, valuetype> *x) {
            Node<keytype, valuetype> *y;
            int r = x->left->subTreeSize + 1;
            y = x;
            while (y != root) {
                if (y == y->parent->right) {
                    r = r + y->parent->left->subTreeSize + 1;
                }
                y = y->parent;
            }
            return r - 1;
        }

        void deleteTree(Node<keytype, valuetype> *tree) {
            while (tree != root) {
                deleteTree(tree->left);
                deleteTree(tree->right);
                delete tree;
            }
            root = NULL;
        }

        void preorderPrint(Node<keytype, valuetype> *x) {
            if (x != nil) {
                cout << x->key << " ";
                preorderPrint(x->left);
                preorderPrint(x->right);
            }
        } 
    
        void inorderPrint(Node<keytype, valuetype> *x) {
            if (x != nil) {
                inorderPrint(x->left);
                cout << x->key << " ";
                inorderPrint(x->right);    
            }
        }
    
        void postorderPrint(Node<keytype, valuetype> *x) {
            if (x == nil) {
                return;
            }
            postorderPrint(x->left);
            postorderPrint(x->right);
            cout << x->key << " ";
        }

        Node<keytype, valuetype> *copyTree(Node<keytype, valuetype> *x) {
            Node<keytype, valuetype> *copy;
            if (x != nil) {
                copy = new Node<keytype, valuetype>;
                copy->key = x->key;
                copy->value = x->value;
                copy->color = x->color;
                copy->left = copyTree(x->left);
                if (copy->left != nil) {
                    copy->left->parent = copy;
                }
                copy->right = copyTree(x->right);
                if (copy->right != nil) {
                    copy->right->parent = copy;
                }
            }
            else {
                copy = nil;
            }
            return copy;
        }
    public:
        RBTree() {
            nil = new Node<keytype, valuetype>(0);
            root = new Node<keytype, valuetype>();
            root = nil;
        }

        RBTree(keytype k[], valuetype v[], int s) {
            nil = new Node<keytype, valuetype>(0);
            root = new Node<keytype, valuetype>();
            root = nil;
            for(int i = 0; i < s; i++) {
                this->insert(k[i], v[i]);
            }
        }
        
        ~RBTree() {
            deleteTree(this->root);
            delete root;
            delete nil;
        }

        RBTree<keytype, valuetype>& operator=(RBTree<keytype, valuetype>& tree) {
            deleteTree(this->root);
            this->root = tree.root;
            this->arrayTree = tree.arrayTree;
            this->treeSize = tree.treeSize;
            this->nil = tree.nil;

            return *this;
        }

        RBTree(RBTree<keytype, valuetype>& tree) {
            this->nil = tree.nil;
            this->treeSize = tree.treeSize;
            this->arrayTree = tree.arrayTree;

            if (tree.root == nil) {
                this->root = nil;
            }
            else {
                this->root = copyTree(tree.root);
            }
        }

        valuetype* search(keytype k) {
            Node<keytype, valuetype> *y;
            y = root;
            while (y->key != k) {
                if (y != nil) {
                    if (y->key > k) {
                        y = y->left;
                    }
                    else {
                        y = y->right;
                    }
                }
                else {
                    return NULL;
                }
            } 
            return &y->value;
        }

        void insert(keytype k, valuetype v) {
            Node<keytype, valuetype> *y, *x;
            Node<keytype, valuetype> *z = new Node<keytype, valuetype>(k ,v);

            y = nil;
            x = root;

            while (x != nil) {
                y = x;
                if (z->key < x->key) {
                    x = x->left;
                }
                else {
                    x = x->right;
                }
            } 
            z->parent = y;
            if (y == nil) {
                root = z;
            }
            else if (z->key < y->key) {
                y->left = z;
            }
            else {
                y->right = z;
            }

            z->left = nil;
            z->right = nil;
            z->color = 1;

            insertFixup(z);
        }

        int remove(keytype k) {
            if (searchHelper(k) == nil) {
                return 0;
            }
            Node<keytype, valuetype> *z = searchHelper(k);
            Node<keytype, valuetype> *x, *y = new Node<keytype, valuetype>();
            y = z;
            bool yOGColor = y->color;
            if (z->left == nil) {
                x = z->right;
                transplant(z, z->right);
            }
            else if (z->right == nil) {
                x = z->left;
                transplant(z, z->left);
            }
            else {
                y = treeMinimum(z->right);
                yOGColor = y->color;
                x = y->right;
                if (y->parent == z) {
                    x->parent = y;
                }
                else {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            if (yOGColor == 0) {
                deleteFixup(x);
            }

            return 1;
        }

        int rank(keytype k) {
            return rankHelper(root);
        }

        keytype select(int pos) {
            return selectHelper(root, pos);
        }
        
        keytype* successor(keytype k) {
            Node<keytype, valuetype> *suc;
            suc = findSuccessor(k);
            return &suc->key;
        }
        keytype* predecessor(keytype k) {
            Node<keytype, valuetype> *pre;
            pre = findPredecessor(k);
            return &pre->key; 
        }

        int size() {
            return root->subTreeSize;
        }

        void preorder() {
            preorderPrint(root);
            cout << endl;
        }
        void inorder() {
            inorderPrint(root);
            cout << endl;
        } 
        void postorder() {
            postorderPrint(root);
            cout << endl;
        }
};