/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
    ListNode *temp;
    while(tail!=NULL){
        temp = tail->prev;
        delete tail;
        tail = temp;
    }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    /// @todo Graded in MP3.1
    ListNode *temp = new ListNode(ndata);
    if(length != 0){
        head->prev = temp;
        temp->prev = NULL;
        temp->next = head;
        head = temp;
    }
    else{
        head = temp;
        tail = temp;
        head->prev = NULL;
        tail->next = NULL;
    }
    length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    /// @todo Graded in MP3.1
    ListNode *temp = new ListNode(ndata);
    if(length!=0){
        tail->next = temp;
        temp->next = NULL;
        temp->prev = tail;
        tail = temp;
    }
    else{
        head = temp;
        tail = temp;
        head->prev = NULL;
        tail->next = NULL;
    }
    length++;
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
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
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    /// @todo Graded in MP3.1
    if(startPoint==NULL)
        return;

    ListNode *curr = startPoint;
   
    ListNode *next1 = NULL;
    ListNode *temp1 = NULL;
    ListNode *temp2 = NULL;
     
    if(startPoint->prev!=NULL){  
        temp1 = startPoint->prev;
        startPoint->prev = NULL;
        temp1->next = NULL;      
    }
    if(endPoint->next != NULL){
        temp2 = endPoint->next;
        endPoint->next = NULL;
        temp2->prev = NULL;
        
    }

    while(startPoint!=NULL && startPoint!=endPoint->next){
        next1 = startPoint->prev;
        startPoint->prev = startPoint->next;
        startPoint->next = next1;
        startPoint = startPoint->prev;
    }
    startPoint = curr;
    next1 = endPoint;
    endPoint = startPoint;
    startPoint = next1;
    
    if(temp1!=NULL){
        startPoint->prev = temp1;
        temp1->next = startPoint;          
    }
    if (temp2!=NULL){
        endPoint->next = temp2;
        temp2->prev = endPoint;
    }
        
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
    /// @todo Graded in MP3.1
    if (n==0)
        return;
    int l=length;
    ListNode* endPoint=head;
    ListNode* startPoint=head;
     
    while(l>0){
        if (n<l){
            for (int i = n; i > 1; i--)
                endPoint=endPoint->next;
 
            if (startPoint!=head)
                reverse(startPoint,endPoint);
            else
                reverse(head,endPoint);
            startPoint=endPoint->next;
            endPoint=startPoint;
            l-=n;
        }
        else
        {
            if (startPoint!=head)
     
                reverse(startPoint,tail);
            else
                reverse(head,tail);
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
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if(empty() || head==tail || length<=1)
        return;

    ListNode *temp = head;
    ListNode *remove;
    ListNode *temp2;
    while (temp->next!=NULL && temp->next!=tail){
        remove = temp->next;
        temp->next = remove->next;
        temp2 = remove->next;
        temp2->prev = temp;
        tail->next = remove;
        remove->prev = tail;
        remove->next = NULL;
        tail = remove;
        temp = temp2;
    }
}


/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    /// @todo Graded in MP3.2
    ListNode *temp,  *nodeBefore;
    nodeBefore = start;
    if (splitPoint == 0)
        return start;

    for (int i = 0; i < splitPoint-1; i++){
        if (nodeBefore->next != NULL){
            nodeBefore = nodeBefore->next;
        }
    }

    temp = nodeBefore->next;
    temp->prev = NULL;

    nodeBefore->next = NULL;
    return temp;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
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
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    /// @todo Graded in MP3.2

    ListNode *temp, *start;
    if(first == NULL && second == NULL){
        return NULL;
    }
    if (first == NULL)
        return second;
    if (second == NULL)
        return first;

    if (first->data < second->data){
        start = first;
        start->next = merge(first->next, second);
        temp = start->next;
        if (temp!=NULL){
            temp->prev = start;
        }
    }
    else{
        start = second;
        start->next = merge(second->next, first);
        temp = second->next;
        if (temp!=NULL){
            temp->prev = start;
        }
    }
    return start;

}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
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
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
    if (chainLength == 1){
        return start;
    }

    int templength = chainLength/2;
    ListNode *halfNode;
    halfNode = split(start, templength);

    start = mergesort(start, templength);
    halfNode = mergesort(halfNode, chainLength-templength);
    start = merge(start, halfNode);
    return start;
}
