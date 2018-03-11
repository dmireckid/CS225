/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t = temp;
    t->height = 1 + max(heightOrNeg1(t->right), heightOrNeg1(t->left));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t = temp;
    t->height = 1 + max(heightOrNeg1(t->right), heightOrNeg1(t->left));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if(subtree == NULL){
      return;
    }
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    int cbalance;
    Node* temp = NULL;
    if(balance == -2){
      temp = subtree->left;
      cbalance = heightOrNeg1(temp->right) - heightOrNeg1(temp->left);
      if(cbalance == -1){
        rotateRight(subtree);
      }
      else if(cbalance == 1){
        rotateLeftRight(subtree);
      }
    }
    else if(balance == 2){
      temp = subtree->right;
      cbalance = heightOrNeg1(temp->right) - heightOrNeg1(temp->left);
      if(cbalance == 1){
        rotateLeft(subtree);
      }
      else if(cbalance == -1){
        rotateRightLeft(subtree);
      }
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
    if(subtree->left != NULL){
      subtree->left->height = 1 + max(heightOrNeg1(subtree->left->right), heightOrNeg1(subtree->left->left));
    }
    if(subtree->right != NULL){
      subtree->right->height = 1 + max(heightOrNeg1(subtree->right->right), heightOrNeg1(subtree->right->left));
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if(subtree == NULL){
      subtree = new Node(key, value);
      //return;
    }
    else if(key < subtree->key){
        insert(subtree->left, key, value);
        /*int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
        int lBalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if(balance <= -2){
          if(lBalance <= -1){
            rotateRight(subtree);
          }
          else{
            rotateLeftRight(subtree);
          }
        }*/
        rebalance(subtree);
    }
    else if(key > subtree->key){
        insert(subtree->right, key, value);
        /*int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
        int rBalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if(balance >= 2){
          if(rBalance >= 1){
            rotateLeft(subtree);
          }
          else{
            rotateRightLeft(subtree);
          }
        }*/
        rebalance(subtree);
    }
    //subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            // no-child remove
            //cout << "no child" << endl;
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            // two-child remove
            //cout << "2 child" << endl;
            Node* temp = subtree->left;
            while(temp->right != NULL){
              temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, temp->key);
            temp = NULL;
            rebalance(subtree);
        } else {
            // one-child remove
            Node* temp = subtree->right ? subtree->right : subtree->left;
            swap(subtree, temp);
            subtree->right = temp->right;
            subtree->left = temp->left;

            delete temp;
            temp = NULL;
            rebalance(subtree);
        }

    }
    /*if(subtree == NULL){
      return;
    }*/
    /*subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    int balance = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
    if(balance >= 2 && key < subtree->left->key){
      rotateRight(subtree);
    }
    else if(balance <= -2 && key > subtree->right->key){
      rotateLeft(subtree);
    }
    else if(balance >= 2 && key > subtree->left->key){
      rotateLeftRight(subtree);
    }
    else if(balance <= -2 && key < subtree->right->key){
      rotateRightLeft(subtree);
    }*/
    //rebalance(subtree);
}
