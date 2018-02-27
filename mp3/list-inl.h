/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  ListNode* temp = head_;
  while(temp != NULL){
    temp = temp->next;
    delete head_;
    head_ = temp;
  }
  length_ = 0;
  tail_ = NULL;
  head_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  ListNode* temp = new ListNode(ndata);
  if(head_ != NULL){
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
  }
  else{
    temp->next = NULL;
    temp->prev = NULL;
    head_ = temp;
    tail_ = head_;
  }
  length_ += 1;
  //delete temp;
  temp = NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  ListNode* temp = new ListNode(ndata);
  if(tail_ != NULL){
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
  }
  else{
    temp->next = NULL;
    temp->prev = NULL;
    head_ = temp;
    tail_ = head_;
  }
  length_ += 1;
  temp=NULL;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if(!startPoint || !endPoint || startPoint==endPoint){
    return;
  }
  ListNode *tempStart=startPoint;
  ListNode *tempPrev=startPoint->prev;
  ListNode *tempEnd=endPoint;
  ListNode *tempNext=endPoint->next;
  ListNode *temp = NULL;
  while(startPoint != endPoint){
    temp = startPoint->prev;
    startPoint->prev = startPoint->next;
    startPoint->next = temp;
    startPoint = startPoint->prev;
  }
  temp = startPoint->prev;
  startPoint->prev = tempPrev;
  startPoint->next = temp;
  endPoint = tempStart;
  endPoint->next = tempNext;
  if(tempPrev){
    tempPrev->next = startPoint;
  }
  else{
    head_ = startPoint;
  }
  if(tempNext){
    tempNext->prev = endPoint;
  }
  else{
    tail_ = endPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  if(head_ == NULL){
    return;
  }
  ListNode* start = head_;
  ListNode* end = head_;
  while(start->next && end->next){
    //cout << "beginning" << endl;
    end=start;
    for(int i=0; i < (n-1); i++){
      if(end->next){
        end = end->next;
      }
    }     //rant: this should be working and i have no clue
          //why the f*ck not, like bruhhhhhhhhhhhhhh
          //end rant
    //cout << "pre reverse" << endl;
    reverse(start, end);
    //cout << "post reverse" << endl;
    start = end->next;
    //cout << "wat" << endl;
    if(!start){
      return;
    }
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  if(!head_ || !head_->next){
    return;
  }
  ListNode* temp = head_;
  ListNode* tempn = head_->next;
  while(temp->next && temp->next->next){
    temp = temp->next;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    tempn = temp->next;
    tail_->next = temp;
    temp->prev = tail_;
    temp->next = NULL;
    tail_ = temp;
    temp = tempn;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  ListNode* temp = head_;
  if(!start || splitPoint==0){
    return start;
  }
  for(int i=0; i<splitPoint; i++){
    temp = temp->next;
  }
  temp->prev->next = NULL;
  temp->prev = NULL;
  return temp;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  if(!first || !second){
    return NULL;
  }
  if(first == second){
    return first;
  }
  ListNode* tempHead = first;
  ListNode* tempFirst = first;
  ListNode* tempSecond = second;
  ListNode* temp = NULL;
  if(first->data < second->data){
    //tempHead = first;
    tempFirst = tempFirst->next;
  }
  else{
    tempHead = second;
    tempSecond = tempSecond->next;
  }
  temp = tempHead;
  while(tempFirst && tempSecond){
    if(tempSecond->data < tempFirst->data){
      temp->next = tempSecond;
      tempSecond->prev = temp;
      temp = tempSecond;
      tempSecond = tempSecond->next;
    }
    else{
      temp->next = tempFirst;
      tempFirst->prev = temp;
      temp = tempFirst;
      tempFirst = tempFirst->next;

    }
  }
  if(tempFirst){
    temp->next = tempFirst;
    tempFirst->prev = temp;
  }
  else{
    temp->next = tempSecond;
    tempSecond->prev = temp;
  }
  //second = NULL;
  return tempHead;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  ListNode* temp = start;
  ListNode* temp2 = NULL;
  int half = chainLength/2;
  if(chainLength == 1){
    start->next = NULL;
    start->prev = NULL;
    return start;
  }
  else{
    temp2 = start;
    for(int i=0; i< half; i++){
      temp2 = temp2->next;
    }
    temp2->prev->next = NULL;
    temp2->prev = NULL;
    start = mergesort(start, half);
    temp2 = mergesort(temp2, (chainLength-half));
    temp = merge(start, temp2);
  }
  return temp;
}
