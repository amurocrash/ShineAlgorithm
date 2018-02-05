//
// Created by Amuro on 2018/1/30.
//

#include "NativeAlgorithmBinarySearch.h"
#include "LogUtils.h"
#include <string.h>
#include <iostream>
#include <queue>

using namespace std;

template<typename Key, typename Value>
class BST
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value)
        {
            this->key = key;
            this->value = value;
            this->left = NULL;
            this->right = NULL;
        }

        Node(Node* node)
        {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };

    Node *root;
    int count;

    Node* _insert(Node *node, Key key, Value value)
    {
        if (node == NULL)
        {
            count++;
            node = new Node(key, value);
        }

        if (key == node->key)
        {
            node->value = value;
        }
        else if (key > node->key)
        {
            node->right = _insert(node->right, key, value);
        }
        else
        {
            node->left = _insert(node->left, key, value);
        }

        return node;
    }

    bool _contain(Node *node, Key key)
    {
        if (node == NULL)
        {
            return false;
        }

        if (key == node->key)
        {
            return true;
        }
        else if (key > node->key)
        {
            return _contain(node->right, key);
        }
        else
        {
            return _contain(node->left, key);
        }
    }

    Value *_search(Node *node, Key key)
    {
        if (node == NULL)
        {
            return NULL;
        }

        if (key == node->key)
        {
            return &(node->value);
        }
        else if (key > node->key)
        {
            return _search(node->right, key);
        }
        else
        {
            return _search(node->left, key);
        }
    }

    void _preOrder(Node *node, void(*pF)(Node*))
    {
        if (node == NULL)
        {
            return;
        }

        pF(node);
        _preOrder(node->left, pF);
        _preOrder(node->right, pF);
    }

    void _inOrder(Node *node, void(*pF)(Node*))
    {
        if (node == NULL)
        {
            return;
        }

        _inOrder(node->left, pF);
        pF(node);
        _inOrder(node->right, pF);

    }

    void _postOrder(Node* node, void(*pF)(Node*))
    {
        if (node == NULL)
        {
            return;
        }

        _postOrder(node->left, pF);
        _postOrder(node->right, pF);

        pF(node);
    }

    void _levelOrder(Node* node, void(*pF)(Node*))
    {
        queue<Node*> q;
        q.push(node);

        while(!q.empty())
        {
            Node* node = q.front();
            q.pop();
            pF(node);

            if(node->left)
            {
                q.push(node->left);
            }

            if(node->right)
            {
                q.push(node->right);
            }

        }
    }

    Node* _findMaxNode(Node* node)
    {
        if(node->right == NULL)
        {
            return node;
        }

        return _findMaxNode(node->right);
    }

    Node* _findMinNode(Node* node)
    {
        if(node->left == NULL)
        {
            return node;
        }

        return _findMinNode(node->left);
    }

    Node* _deleteMaxNode(Node* node)
    {
        if(node->right == NULL)
        {
            Node* leftNode = node->left;
            delete node;
            count--;

            return leftNode;
        }

        node->right = _deleteMaxNode(node->right);
        return node;
    }

    Node* _deleteMinNode(Node* node)
    {
        if(node->left == NULL)
        {
            Node* rightNode = node->right;
            delete node;
            count--;

            return rightNode;
        }

        node->left = _deleteMinNode(node);
        return node;
    }

    void deleteMaxNode()
    {
        if(root)
        {
            root = _deleteMaxNode(root);
        }
    }

    void deleteMinNode()
    {
        if(root)
        {
            root = _deleteMinNode(root);
        }
    }

    Node* _deleteNodeByKey(Node* node, Key key)
    {
        if(node == NULL)
        {
            return NULL;
        }

        if(key < node->key)
        {
            node->left = _deleteNodeByKey(node->left, key);
            return node;
        }
        else if(key > node->key)
        {
            node->right = _deleteNodeByKey(node->right, key);
            return node;
        }
        else
        {
            if(node->left == NULL)
            {
                Node* rightNode = node->right;
                delete node;
                count--;

                return rightNode;
            }

            if(node->right == NULL)
            {
                Node* leftNode = node->left;
                delete node;
                count--;

                return leftNode;
            }

            Node* minNodeInRight = new Node(_findMinNode(node->right));
            minNodeInRight->left = node->left;
            minNodeInRight->right = _deleteMinNode(node->right);
            delete node;

            return minNodeInRight;
        }

    }

    static void showKey(Node* node)
    {
        LogUtils::w("key -> %d", node->key);
    }

    static void destroy(Node* node)
    {
        LogUtils::w("destroy -> %d", node->key);
        delete node;
    }


public:
    BST()
    {
        root = NULL;
        count = 0;
    }

    ~BST()
    {
        _postOrder(root, destroy);
        count = 0;
    }

    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    void insert(Key key, Value value)
    {
        root = _insert(root, key, value);
    }

    bool contain(Key key)
    {
        return _contain(root, key);
    }

    Value *search(Key key)
    {
        return _search(root, key);
    }

    static void display(Node* node)
    {
        LogUtils::w("node->%d", node->key);

        if(node->left)
        {
            LogUtils::w("left->%d", node->left->key);
        }
        else
        {
            LogUtils::w("left->null");
        }

        if(node->right)
        {
            LogUtils::w("right->%d", node->right->key);
        }
        else
        {
            LogUtils::w("right->null");
        }


    }

    void preOrder()
    {
        _preOrder(root, showKey);
    }

    void inOrder()
    {
        _inOrder(root, showKey);
    }

    void postOrder()
    {
        _postOrder(root, showKey);
    }

    void levelOrder()
    {
        _levelOrder(root, showKey);
    }

    Key findMaxKey()
    {
        if(count == 0)
        {
            return NULL;
        }

        return _findMaxNode(root)->key;
    }

    Key findMinKey()
    {
        if(count == 0)
        {
            return NULL;
        }

        return _findMinNode(root)->key;
    }

    void deleteNodeByKey(Key key)
    {
        root = _deleteNodeByKey(root, key);
    }
};


int _baseBinarySearch(int *arr, int left, int right, int target)
{
    if (left > right)
    {
        return -1;
    }

    int mid = (left + right) / 2;

    if (arr[mid] == target)
    {
        return mid;
    }
    else if (arr[mid] > target)
    {
        return _baseBinarySearch(arr, left, mid - 1, target);
    }
    else
    {
        return _baseBinarySearch(arr, mid + 1, right, target);
    }
}

int baseBinarySearch(JNIEnv *env, jclass type, jintArray origin, jint target)
{
    int length = env->GetArrayLength(origin);
    if (origin == NULL || length <= 0)
    {
        return -1;
    }

    jint *pOrigin = env->GetIntArrayElements(origin, NULL);

    int result = _baseBinarySearch(pOrigin, 0, length - 1, target);

    return result;
}

jstring searchWithBST(JNIEnv *env, jclass type, jint key)
{
    BST<int, std::string> *bst = new BST<int, std::string>();
    bst->insert(1, "amuro");
    bst->insert(2, "char");
    bst->insert(3, "kamiu");
    bst->insert(4, "judo");

    return env->NewStringUTF((bst->search(key))->c_str());
}

void orderTest(JNIEnv *env, jclass type)
{
    BST<int, std::string> *bst = new BST<int, std::string>();
    bst->insert(37, "amuro");
    bst->insert(28, "char");
    bst->insert(13, "kamiu");
    bst->insert(60, "judo");
    bst->insert(50, "haman");
    bst->insert(33, "wusou");
    bst->insert(15, "kira");
    bst->insert(58, "asran");
    bst->insert(22, "setsuna");
    bst->insert(41, "lala");

    bst->preOrder();

    delete bst;
}

static const char *const registerClassName =
        "com/zhaohui/core/algorithm/AlgorithmBinarySearch";

static const JNINativeMethod registerMethods[] = {
        {"binarySearchBase", "([II)I",                (int *) baseBinarySearch},
        {"searchWithBST",    "(I)Ljava/lang/String;", (jstring *) searchWithBST},
        {"orderTest",        "()V",                   (void *) orderTest}
};


int NativeAlgorithmBinarySearch::registerNatives(JNIEnv *env)
{
    jclass classForRegister = env->FindClass(registerClassName);

    if (classForRegister == NULL)
    {
        LogUtils::w("Algorithm heap sort can not find class");
        return -1;
    }

    jint isRegisterSuccess = env->RegisterNatives(
            classForRegister,
            registerMethods,
            sizeof(registerMethods) / sizeof(registerMethods[0]));

    if (isRegisterSuccess < 0)
    {
        LogUtils::w("Algorithm heap sort can not find methods");
        return -1;
    }

    return 0;
}