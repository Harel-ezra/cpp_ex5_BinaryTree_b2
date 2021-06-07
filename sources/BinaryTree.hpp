#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ariel {

    enum move_order {
        pre, // root, left, right
        in, // left, root, right
        post // left, right, root
    };

    template<typename T>
    class BinaryTree {
    private:


        struct Node {
            T value;
            Node *left;
            Node *right;
            //Node *father;

            Node(T &val, Node *f = nullptr) : value(val), right(nullptr), left(nullptr) {
            }

            ~Node() {
                delete left;
                delete right;
            }

            Node(const Node *&n) : value(n->value), right(nullptr), left(nullptr) {
                if (n->left != nullptr) {
                    this->left = new Node(n->left);
                }
                if (n->right != nullptr) {
                    this->right = new Node(n->right);
                }
            }

            Node(Node &&n) noexcept {
                this->value = n.value;
                this->right = n.right;
                this->left = n.left;
                n.value = nullptr;
                n.left = nullptr;
                n.right = nullptr;
            }

//            bool operator==(Node &n) {
//                if (this== nullptr && n== nullptr)
//                {
//                    return true;
//                }
//                if(this!= nullptr && n!= nullptr)
//                {
//                    return this->value==n.value;
//                }
//                return false;
//            }

            Node &operator==(Node &&n) noexcept {
                return *this;
            }

        };


        Node *root = nullptr;


    public:

        class iterator {

        private:
            typename vector<Node *>::iterator pointer_to_current_node;
            typename vector<Node *>::iterator it_node;
            vector<Node *> v;


            void preorder(Node *root) {
                if (root == nullptr) {
                    return;
                }
                v.push_back(root);
                preorder(root->left);
                preorder(root->right);
            }

            void inorder(Node *root) {
                if (root == nullptr) {
                    return;
                }
                inorder(root->left);
                v.push_back(root);
                inorder(root->right);
            }

            void postorder(Node *root) {
                if (root == nullptr) {
                    return;
                }
                postorder(root->left);
                postorder(root->right);
                v.push_back(root);
            }

        public:

            iterator(Node *ro = nullptr, move_order o = in) {
                if (o == in) {
                    inorder(ro);
                } else if (o == pre) {
                    preorder(ro);
                } else {
                    postorder(ro);
                }
                if (ro == nullptr) {
                    pointer_to_current_node = v.end();
                } else {
                    pointer_to_current_node = v.begin();
                }
                //it_node = v.begin();
            }

            // Note that the method is const as this operator does not
            // allow changing of the iterator.
            // Note that it returns T& as it allows to change what it points to.
            // A const_iterator class will return const T&
            // and the method will still be const
            T &operator*() const {
//                if(v.begin()==v.end())
//                {
//                    return nullptr;
//                }
                Node *n = *pointer_to_current_node;
                return n->value;
            }

            T *operator->() const {
                Node *n = *pointer_to_current_node;
                return &(n->value);
                //return &(v[pointer_to_current_node]);
            }

            // ++i;
            iterator &operator++() {
                //++pointer_to_current_node;
                if (pointer_to_current_node != v.end()) {
                    pointer_to_current_node++;
                }
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const iterator operator++(int) {
                iterator tmp = *this;
                if (pointer_to_current_node != v.end()) {
                    pointer_to_current_node++;
                }
                return tmp;
            }

            bool operator==(const iterator &rhs) const {
//                if(v.size()!=rhs.v.size())
//                {
//                    return false;
//                }
                if (rhs.pointer_to_current_node == rhs.v.end() && pointer_to_current_node != v.end()) {
                    return false;
                }
                if (rhs.pointer_to_current_node != rhs.v.end() && pointer_to_current_node == v.end()) {
                    return false;
                }
                if (rhs.pointer_to_current_node == rhs.v.end() && pointer_to_current_node == v.end()) {
                    return true;
                }
                Node *n1 = *pointer_to_current_node;
                Node *n2 = *(rhs.pointer_to_current_node);
                return n1 == n2;
//                if (this == nullptr && rhs == nullptr) {
//                    return true;
//                }
//                if (this != nullptr && rhs != nullptr) {
//                //return v[pointer_to_current_node]->value == *rhs;
//            }
//                return false;
            }

            bool operator!=(const iterator &rhs) const {
                if (rhs.pointer_to_current_node == rhs.v.end() && pointer_to_current_node != v.end()) {
                    return false;
                }
                if (rhs.pointer_to_current_node != rhs.v.end() && pointer_to_current_node == v.end()) {
                    return false;
                }
                if (rhs.pointer_to_current_node == rhs.v.end() && pointer_to_current_node == v.end()) {
                    return true;
                }
                Node *n1 = *pointer_to_current_node;
                Node *n2 = *rhs.pointer_to_current_node;
                return n1 != n2;
//                return !(*this == rhs);
//                return false;
            }
        };  // END OF CLASS ITERATOR


        //empty constructor
        BinaryTree() : root(nullptr) {
        }

        //copy constructor
        BinaryTree(BinaryTree<T>
                   &other) {
            for (auto it = other.begin(); it != other.end(); ++it) {
//                this->add_left(*it);
//                this->add_right(*it, );
            }

        }

        //move constructor
        BinaryTree(BinaryTree<T>
                   &&binaryTree) noexcept {

        }

        //destructor
        ~BinaryTree() {


        }

        BinaryTree &operator=(BinaryTree &other) {
            return *this;

        }

        BinaryTree &&operator=(BinaryTree &&other) noexcept {
            return *this;

        }

        // replace or set the root tree node
        BinaryTree<T> &add_root(T r) {
            if (root == nullptr) {
                root = new Node(r);
            } else {
                root->value = r;
            }
            return *this;
        }

        Node *find_node(Node *n, const T &t) {
            if (n == nullptr) {
                return nullptr;
            }
            if (n->value == t) {
                return n;
            }
            Node *temp = find_node(n->left, t);
            if (temp != nullptr) {
                return temp;
            }
            return find_node(n->right, t);
        }

        BinaryTree<T> &add_left(T e, T a) {
            Node *temp = find_node(root, e);
            if (temp == nullptr) {
                throw ("cant add to null ");
            }
            if (temp->left == nullptr) {
                temp->left = new Node(a);
            } else {
                temp->left->value = a;
            }
            return *this;
        }

//        void add_l(Node* node,T e, T a)
//        {
//            if(node== nullptr)
//            {
//                return;
//            }
//            if(node->value==e)
//            {
//                node->value=a;
//            }
//        }

        BinaryTree<T> &add_right(T e, T a) {
            Node *temp = find_node(root, e);
            if (temp == nullptr) {
                throw ("cant add to null ");
            }
            if (temp->right == nullptr) {
                temp->right = new Node(a);
            } else {
                temp->right->value = a;
            }
            return *this;
        }

        iterator begin() {
            return iterator(root);
        }

        iterator end() {

            return iterator();
        }

        iterator begin_preorder() {
            return iterator(root, pre);
        }

        iterator end_preorder() {
            return iterator();
        }


        iterator begin_inorder() {
            return iterator(root, in);
        }

        iterator end_inorder() {
            return iterator();
        }

        iterator begin_postorder() {
            return iterator(root, post);
        }

        iterator end_postorder() {
            return iterator();
        }

        friend std::ostream &operator<<(std::ostream &output, const BinaryTree<T> &bt) {
            return output;
        }
    };
}