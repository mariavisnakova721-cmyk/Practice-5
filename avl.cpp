#include "avl.h"
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
int avlHeight(AVLNode* p) { return p ? p->height : 0; }
static void update(AVLNode* p) { p->height = 1 + max(avlHeight(p->left), avlHeight(p->right)); }
static int balance(AVLNode* p) { return avlHeight(p->right) - avlHeight(p->left); }
static AVLNode* rotateLeft(AVLNode* p) {
    AVLNode* q = p->right;
    p->right = q->left;
    q->left = p;
    update(p); update(q);
    return q;
}
static AVLNode* rotateRight(AVLNode* p) {
    AVLNode* q = p->left;
    p->left = q->right;
    q->right = p;
    update(p); update(q);
    return q;
}
static AVLNode* fix(AVLNode* p) {
    update(p);
    if (balance(p) == 2) {
        if (balance(p->right) < 0) p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (balance(p) == -2) {
        if (balance(p->left) > 0) p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p;
}
AVLNode* insertAVL(AVLNode* p, int x) {
    if (!p) return new AVLNode(x);
    if (x < p->value) p->left = insertAVL(p->left, x);
    else if (x > p->value) p->right = insertAVL(p->right, x);
    else return p;
    return fix(p);
}
static AVLNode* minimum(AVLNode* p) {
    while (p->left) p = p->left;
    return p;
}
AVLNode* removeAVL(AVLNode* p, int x) {
    if (!p) return nullptr;
    if (x < p->value) p->left = removeAVL(p->left, x);
    else if (x > p->value) p->right = removeAVL(p->right, x);
    else {
        if (!p->left || !p->right) {
            AVLNode* child = p->left ? p->left : p->right;
            delete p;
            return child;
        }
        AVLNode* next = minimum(p->right);
        p->value = next->value;
        p->right = removeAVL(p->right, next->value);
    }
    return fix(p);
}
bool findAVL(AVLNode* p, int x) {
    while (p) {
        if (p->value == x) return true;
        p = x < p->value ? p->left : p->right;
    }
    return false;
}
void deleteAVL(AVLNode* p) {
    if (!p) return;
    deleteAVL(p->left); deleteAVL(p->right); delete p;
}
vector<int> breadthFirst(AVLNode* root) {
    vector<int> result;
    if (!root) return result;
    queue<AVLNode*> q;
    q.push(root);
    while (!q.empty()) {
        AVLNode* p = q.front(); q.pop();
        result.push_back(p->value);
        if (p->left) q.push(p->left);
        if (p->right) q.push(p->right);
    }
    return result;
}
vector<int> preorderAVL(AVLNode* root) {
    vector<int> result;
    if (!root) return result;
    stack<AVLNode*> st; st.push(root);
    while (!st.empty()) {
        AVLNode* p = st.top(); st.pop();
        result.push_back(p->value);
        if (p->right) st.push(p->right);
        if (p->left) st.push(p->left);
    }
    return result;
}
vector<int> inorderAVL(AVLNode* root) {
    vector<int> result;
    stack<AVLNode*> st;
    AVLNode* p = root;
    while (p || !st.empty()) {
        while (p) { st.push(p); p = p->left; }
        p = st.top(); st.pop();
        result.push_back(p->value);
        p = p->right;
    }
    return result;
}
vector<int> postorderAVL(AVLNode* root) {
    vector<int> result;
    stack<AVLNode*> st;
    AVLNode* p = root;
    AVLNode* last = nullptr;
    while (p || !st.empty()) {
        if (p) { st.push(p); p = p->left; }
        else {
            AVLNode* top = st.top();
            if (top->right && last != top->right) p = top->right;
            else { result.push_back(top->value); last = top; st.pop(); }
        }
    }
    return result;
}
