/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the left child.
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the right child.
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    /// @todo Update to return the index of the parent.
    if(currentIdx%2 == 1){
        return (currentIdx-1)/2;
    }
    else{
        return currentIdx/2;
    }
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    /// @todo Update to return whether the given node has a child
    bool flag = false;
    if(currentIdx*2 <= size){
        flag = true;
    }
    return flag;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);

    if(higherPriority(_elems[left], _elems[right])){
        return left;
    }
    else{
        return right;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
    /// @todo Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx)){
        size_t minChildIdx = maxPriorityChild(currentIdx);
        if( !higherPriority( _elems[ currentIdx ], _elems[ minChildIdx ] ) ){
            std::swap( _elems[ currentIdx ], _elems[ minChildIdx ] );
            heapifyDown( minChildIdx );
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
    size = 0;
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    /// @todo Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    size = 0;

    for(size_t i = 1; i < elems.size()+1; i++){
        _elems.push_back(elems[i-1]);
        size++;
    }
    for(size_t j = parent(size); j > 0; j--){
        heapifyDown(j);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    /// @todo Remove, and return, the element with highest priority
    T minVal = _elems[1];
    _elems[1] = _elems[size];
    _elems.pop_back();
    size--;
    heapifyDown(1);
    return minVal;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    /// @todo Add elem to the heap
    _elems.push_back(elem);
    size++;
    heapifyUp(size);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    /// @todo Determine if the heap is empty
    bool flag = false;
    if(size==0){
        flag = true;
    }
    return flag;
}
