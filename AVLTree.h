
#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H



template<class T>
class AVLNode{
public:
    AVLNode<T> *left;
    AVLNode<T> *right;
    T data;
    int height;
    int sizeLeft;

    explicit AVLNode(T data1) : left(nullptr), right(nullptr), data(data1), height(0), sizeLeft(0) {}
};


template<class T, class Compare>
class AVLTree
{
public:
    AVLNode<T> * root;
    Compare compare;

    AVLTree():root(nullptr), compare() {}


    int calculateHeight(AVLNode<T> *node){

        if(node->left != nullptr && node->right != nullptr)
        {
            if (node->left->height < node->right->height)
                return node->right->height + 1;
            else
                return  node->left->height + 1;
        }
        else if(node->left != nullptr && node->right == nullptr)
        {
            return node->left->height + 1;
        }
        else if(node->left == nullptr && node->right != nullptr)
        {
            return node->right->height + 1;
        }
        return 0;

    }

    int getBalanceFactor(AVLNode<T> *node)
    {
        if(node == nullptr)
        {
            return -30;//impossible
        }
        if(node->left != nullptr && node->right != nullptr)
        {
            return node->left->height - node->right->height;
        }
        else if(node->left != nullptr && node->right == nullptr)
        {
            return node->left->height + 1;
        }
        else if(node->left == nullptr && node->right != nullptr)
        {
            return -1 - node->right->height;
        }
        else
        {
            return 0;
        }
    }

    AVLNode<T> * LLrotation(AVLNode<T> *node){
        AVLNode<T> *p;
        AVLNode<T> *temp;
        p = node;
        temp = p->left;

        p->left = temp->right;
        temp->right = p;

        p->height= calculateHeight(p);
        temp->height= calculateHeight(temp);

        p->sizeLeft = p->sizeLeft - temp->sizeLeft - 1;
        return temp;
    }


    AVLNode<T> * RRrotation(AVLNode<T> *node){
        AVLNode<T> *p;
        AVLNode<T> *temp;
        p = node;
        temp = p->right;

        p->right = temp->left;
        temp->left = p;

        p->height= calculateHeight(p);
        temp->height= calculateHeight(temp);

        temp->sizeLeft = p->sizeLeft + 1 + temp->sizeLeft;
        return temp;
    }


    AVLNode<T> * RLrotation(AVLNode<T> *node){
        AVLNode<T> *p;
        AVLNode<T> *temp1;
        AVLNode<T> *temp2;
        p = node;
        temp1 = p->right;
        temp2 = p->right->left;

        p -> right = temp2->left;
        temp1 ->left = temp2->right;
        temp2 ->left = p;
        temp2->right = temp1;

        p->height= calculateHeight(p);
        temp1->height= calculateHeight(temp1);
        temp2->height= calculateHeight(temp2);

        temp1->sizeLeft = temp1->sizeLeft - 1 - temp2->sizeLeft;
        temp2->sizeLeft = temp2->sizeLeft + p->sizeLeft + 1;


//        LLrotation(temp1);
//        temp2 = RRrotation(p);

        return temp2;
    }

    AVLNode<T> * LRrotation(AVLNode<T> *node){
        AVLNode<T> *p;
        AVLNode<T> *temp1;
        AVLNode<T> *temp2;
        p = node;
        temp1 = p->left;
        temp2 = p->left->right;

        p -> left = temp2->right;
        temp1 ->right = temp2->left;
        temp2 ->right = p;
        temp2->left = temp1;

        p->height= calculateHeight(p);
        temp1->height= calculateHeight(temp1);
        temp2->height= calculateHeight(temp2);

        p->sizeLeft = p->sizeLeft - 1 - temp1->sizeLeft - 1 - temp2->sizeLeft;
        temp2->sizeLeft += temp1->sizeLeft + 1;


//        RRrotation(temp1);
//        temp2 = LLrotation(p);

        return temp2;
    }

    AVLNode<T>* insert(AVLNode<T> *current, T data){

        if(current == nullptr){

            current = new AVLNode<T>(data);

            return current;
        }
        else
        {
            if(compare.isLeftSmaller(current->data, data))
            {
//                if(current->right == nullptr)
//                    compare.insertToRight(current->data, data);
                current->right = insert(current->right, data);
            }
            else
            {
//                if(current->left == nullptr)
//                    compare.insertToLeft(current->data, data);
                current->sizeLeft += 1;
                current->left = insert(current->left, data);
            }
        }

        current->height = calculateHeight(current);

        if(getBalanceFactor(current) == 2 &&
            (getBalanceFactor(current->left) == 1 || getBalanceFactor(current->left) == 0)){
            current = LLrotation(current);
        }
        else if(getBalanceFactor(current) == -2 &&
            (getBalanceFactor(current->right) == -1 || getBalanceFactor(current->right) == 0)){
            current = RRrotation(current);
        }
        else if(getBalanceFactor(current) == -2 && getBalanceFactor(current->right) == 1){
            current = RLrotation(current);
        }
        else if(getBalanceFactor(current) == 2 && getBalanceFactor(current->left) == -1){
            current = LRrotation(current);
        }


        return current;

    }

    template<class S>
    AVLNode<T>* findNode(AVLNode<T> *current, S data)
    {
        if(current == nullptr)
            return nullptr;

        if(compare.isEqual(current->data, data))
        {
            return current;
        }
        else if(compare.isLeftSmaller(current->data, data))
        {
            return findNode(current->right, data);
        }
        else
        {
            return findNode(current->left, data);
        }

    }

    template<class S>
    AVLNode<T>* findNodeInRange(AVLNode<T> *current, S min, S max)
    {
        if(current == nullptr)
            return nullptr;

        if(compare.isEqual(current->data, min) || compare.isEqual(current->data, max)
                || (compare.isLeftSmaller(current->data, max) && !compare.isLeftSmaller(current->data, min)) )
        {
            return current;
        }
        else if(compare.isLeftSmaller(current->data, min))
        {
            return findNodeInRange(current->right, min, max);
        }
        else //if(!compare.isLeftSmaller(current->data, max))
        {
            return findNodeInRange(current->left, min, max);
        }


    }

    template<class S>
    AVLNode<T> * deleteNode(AVLNode<T> *current, S data) //ALWAYS CHECK FIND BEFORE DELETE
    {
        bool deleteFlag = false;
        return deleteNodeAux(current,data,&deleteFlag);
    }

    template<class S>
    AVLNode<T> * deleteNodeAux(AVLNode<T> *current, S data, bool *deleteFlag)
    {

        if(current == nullptr)
            return nullptr;
        if(current->left == nullptr && current->right == nullptr){
            if(compare.isEqual(current->data, data))
            {
                if (current == this->root)
                    this->root = nullptr;
                current->left= nullptr;
                current->right= nullptr;

                if(*deleteFlag == false) {
//                    compare.handleDelete(current->data);
                    *deleteFlag = true;
                }
                delete current;
                return nullptr;
            }
            return current;
        }

        AVLNode<T> *temp;

        if(compare.isLeftSmaller(current->data, data)) //current->data < data
        {
            current->right = deleteNodeAux(current->right, data, deleteFlag);
        }
        else if(!compare.isEqual(current->data, data)) // checking current->data > data
        {
            current->sizeLeft -= 1;
            current->left = deleteNodeAux(current->left, data, deleteFlag);
        }
        else //they are equal
        {
            if(*deleteFlag == false)
            {
//                compare.handleDelete(current->data);
                *deleteFlag = true;
            }
            if(current->left != nullptr)
            {
                temp = findRightestSon(current->left);
                current->data = temp->data;

                current->sizeLeft -= 1;
                current->left=deleteNodeAux(current->left, temp->data, deleteFlag);
            }
            else
            {
                temp = findLeftestSon(current->right);
                current->data = temp->data;
//                current->data = current->right->data;
                current->right = deleteNodeAux(current->right,temp->data, deleteFlag);
            }
        }

        current->height= calculateHeight(current);

        //checking for rotations
        if(getBalanceFactor(current) == 2 &&
           (getBalanceFactor(current->left) == 0 || getBalanceFactor(current->left) == 1))
            current = LLrotation(current);
        else if(getBalanceFactor(current) == 2 && getBalanceFactor(current->left) == -1)
            current = LRrotation(current);
        else if(getBalanceFactor(current) == -2 &&
                (getBalanceFactor(current->right) == -1 || getBalanceFactor(current->right) == 0))
            current = RRrotation(current);
        else if(getBalanceFactor(current) == -2 && getBalanceFactor(current->right) == 1)
            current = RLrotation(current);


        return current;


    }

    AVLNode<T>* deleteRoot()
    {
        this->root = deleteNode(this->root, this->root->data);
        return this->root;
    }

    AVLNode<T>* findRightestSon(AVLNode<T>* node){
        if(node == nullptr)
            return nullptr;
        while(node->right != nullptr)
            node = node->right;
        return node;
    }

    AVLNode<T>* findLeftestSon(AVLNode<T>* node){
        if(node == nullptr)
            return nullptr;
        while(node->left != nullptr)
            node = node->left;

        return node;
    }

    T* getInOrder(int length)
    {
        T* arr = new T[length];
        int index = 0;
        inOrderAux(this->root, arr, length, &index);
        return arr;
    }

    void inOrderAux(AVLNode<T>* current, T* arr, int length, int* index)
    {
        if(current == nullptr)
            return;
        if(*index >= length)
            return;

        inOrderAux(current->left, arr, length, index);

        arr[*index] = current->data;
        (*index)++;

        inOrderAux(current->right, arr, length, index);

    }


    void deletePostorder(AVLNode<T>* node)
    {
        if (node == nullptr)
            return;

        //delete both subtrees
        deletePostorder(node->left);
        deletePostorder(node->right);

        //delete the node
        node->left = nullptr;
        node->right = nullptr;
        delete node;

    }


    ~AVLTree(){
        deletePostorder(root);
        root= nullptr;
    }
};



#endif //WET1_AVLTREE_H
