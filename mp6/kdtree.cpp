/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if(first[curDim] == second[curDim]) 
        return first < second;
     else 
        return first[curDim] < second[curDim];
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
    int diff_potential = 0;
    int diff_currentBest = 0;
    for(int i = 0; i < Dim; i++){
        diff_potential += (potential[i]-target[i])*(potential[i]-target[i]);
        diff_currentBest += (currentBest[i]-target[i])*(currentBest[i]-target[i]);
    }

    if(diff_potential == diff_currentBest){
        return potential < currentBest;
    }
    else
        return diff_potential < diff_currentBest;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
     if(newPoints.empty())
        return;
    size_t size = newPoints.size();

    points = newPoints;
    buildTree(0, size - 1, 0);
}

//helper function buildTree for KDTree
template<int Dim>
void KDTree<Dim>::buildTree(int left, int right, int d){
    if(left >= right){
        return;
    }
    if(left < right){
        int mid = (left + right)/2;
        quickSelect(left, right, mid, d);
        if(left < mid)
            buildTree(left, mid-1, (d+1)%Dim);
        if(mid < right)
            buildTree(mid+1, right, (d+1)%Dim);
    }
}

//helper function quickSelect for KDTree
template<int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int mid, int d){
    if(left >= right){
        return;
    }

    int pivot = left;
    int newPivot = partition(left, right, pivot, d);

    if(newPivot == mid){
        return;
    }
    else{
        if(newPivot < mid){
            quickSelect(newPivot+1, right, mid, d);
        }
        else{
            quickSelect(left, newPivot-1, mid, d);
        }
    }
}

//helper function partition for quickSelect
template<int Dim>
int KDTree<Dim>::partition(int left, int right, int pivot, int d){
    Point<Dim> value = points[pivot];

    swap(pivot, right);

    int store = left;
    for(int i = left; i < right; i++){
        if(smallerDimVal(points[i], value, d) || points[i] == value){
            swap(i, store);
            store++;
        }
    }
    swap(right, store);
    return store;
}

//helper function swap for partition
template<int Dim>
void KDTree<Dim>::swap(int left, int right){
    Point<Dim> temp = points[left];
    points[left] = points[right];
    points[right] = temp;
}


template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
   if(points.empty()){
    return Point<Dim>();
   }

   Point<Dim> x = points[(points.size()-1)/2];
   return findNearestNeighbor(query, x, 0, points.size()-1, 0);
}

//helper function for findNearestNeighbor

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> &query, const Point<Dim> &x, int left, int right, int d) const{
    Point<Dim> currBest = x;
    if(left == right){
        if(shouldReplace(query, currBest, points[left])){
            currBest = points[left];
            return currBest;
        }
        currBest = x;
        return currBest;
    }

    bool leftTree = true;
    int mid = (left+right)/2;

    if (smallerDimVal(query, points[mid], d) && (left < mid)){
        currBest = findNearestNeighbor(query, currBest, left, mid-1, (d+1)%Dim);
        leftTree = true;
    }
    if (smallerDimVal(points[mid], query, d) && (right > mid)){
        currBest = findNearestNeighbor(query, currBest, mid+1, right, (d+1)%Dim);
        leftTree = false;
    }

    if (shouldReplace(query, currBest, points[mid])){
        currBest = points[mid];
    }

    int a = (points[mid][d]-query[d])*(points[mid][d]-query[d]);
    //calculate distance between query and currBest
    int b = 0;
    for(int i = 0; i < Dim; i++){
        b = b + (query[i]-currBest[i])*(query[i]-currBest[i]);
    }

    if (a <= b)
    {
        if (leftTree && (right > mid))
            currBest = findNearestNeighbor(query, currBest, mid+1, right, (d+1)%Dim);
        if (!leftTree && (left < mid))
            currBest = findNearestNeighbor(query, currBest, left, mid-1, (d+1)%Dim);
    }
    return currBest;
}
