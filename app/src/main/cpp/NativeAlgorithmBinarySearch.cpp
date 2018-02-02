//
// Created by Amuro on 2018/1/30.
//

#include "NativeAlgorithmBinarySearch.h"
#include "LogUtils.h"
#include <string.h>
#include <iostream>
using namespace std;

template <typename Key, typename Value>
class BST {
private:
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = NULL;
            this->right = NULL;
        }
    };

    Node *root;
    int count;

    Node *insert(Node *node, Key key, Value value) {
        if (node == NULL) {
            count++;
            node = new Node(key, value);
        }

        if (key == node->key) {
            node->value = value;
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->left = insert(node->left, key, value);
        }

        return node;
    }

    bool _contain(Node *node, Key key) {
        if (node == NULL) {
            return false;
        }

        if (key == node->key) {
            return true;
        } else if (key > node->key) {
            return _contain(node->right, key);
        } else {
            return _contain(node->left, key);
        }
    }

    Value* _search(Node* node, Key key)
    {
        if(node == NULL)
        {
            return NULL;
        }

        if(key == node->key)
        {
            return &(node->value);
        }
        else if(key > node->key)
        {
            return _search(node->right, key);
        }
        else
        {
            return _search(node->left, key);
        }
    }

    void _preOrder(Node* node)
    {
        if(node == NULL)
        {
            return;
        }

        LogUtils::w("key -> %d", node->key);

        _preOrder(node->left);
        _preOrder(node->right);
    }

    void _inOrder(Node* node)
    {
        if(node == NULL)
        {
            return;
        }

        _inOrder(node->left);
        LogUtils::w("key -> %d", node->key);
        _inOrder(node->right);

    }

    void _postOrder(Node* node)
    {
        if(node == NULL)
        {
            return;
        }

        _postOrder(node->left);
        _postOrder(node->right);

        LogUtils::w("key -> %d", node->key);
    }

public:
    BST() {
        root = NULL;
        count = 0;
    }

    ~BST() {

    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    void insert(Key key, Value value) {
        root = insert(root, key, value);
    }

    bool contain(Key key) {
        return _contain(root, key);
    }

    Value* search(Key key)
    {
        return _search(root, key);
    }

    void preOrder()
    {
        _preOrder(root);
    }

    void inOrder()
    {
        _inOrder(root);
    }

    void postOrder()
    {
        _postOrder(root);
    }
};

int _baseBinarySearch(int* arr, int left, int right, int target)
{
    if(left > right)
    {
        return -1;
    }

    int mid = (left + right) / 2;

    if(arr[mid] == target)
    {
        return mid;
    }
    else if(arr[mid] > target)
    {
        return _baseBinarySearch(arr, left, mid - 1, target);
    }
    else
    {
        return _baseBinarySearch(arr, mid + 1, right, target);
    }
}

int baseBinarySearch(JNIEnv* env, jclass type, jintArray origin, jint target)
{
    int length = env->GetArrayLength(origin);
    if(origin == NULL || length <= 0)
    {
        return -1;
    }

    jint* pOrigin = env->GetIntArrayElements(origin, NULL);

    int result = _baseBinarySearch(pOrigin, 0, length - 1, target);

    return result;
}

jstring searchWithBST(JNIEnv* env, jclass type, jint key)
{
    BST<int, std::string>* bst = new BST<int, std::string>();
    bst->insert(1, "amuro");
    bst->insert(2, "char");
    bst->insert(3, "kamiu");
    bst->insert(4, "judo");

    return env->NewStringUTF((bst->search(key))->c_str());
}

void orderTest(JNIEnv* env, jclass type)
{
    BST<int, std::string>* bst = new BST<int, std::string>();
    bst->insert(37, "amuro");
    bst->insert(28, "char");
    bst->insert(13, "kamiu");
    bst->insert(60, "judo");
    bst->insert(50, "judo");
    bst->insert(33, "judo");
    bst->insert(15, "judo");
    bst->insert(58, "judo");
    bst->insert(22, "judo");
    bst->insert(41, "judo");

    bst->inOrder();
}

static const char* const registerClassName =
        "com/zhaohui/core/algorithm/AlgorithmBinarySearch";

static const JNINativeMethod registerMethods[] = {
        {"binarySearchBase", "([II)I", (int*)baseBinarySearch},
        {"searchWithBST", "(I)Ljava/lang/String;", (jstring*)searchWithBST},
        {"orderTest", "()V", (void*)orderTest}
};


int NativeAlgorithmBinarySearch::registerNatives(JNIEnv *env)
{
    jclass classForRegister = env->FindClass(registerClassName);

    if(classForRegister == NULL)
    {
        LogUtils::w("Algorithm heap sort can not find class");
        return -1;
    }

    jint isRegisterSuccess = env->RegisterNatives(
            classForRegister,
            registerMethods,
            sizeof(registerMethods) / sizeof(registerMethods[0]));

    if(isRegisterSuccess < 0)
    {
        LogUtils::w("Algorithm heap sort can not find methods");
        return -1;
    }

    return 0;
}