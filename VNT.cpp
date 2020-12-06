// Chevano Gordon
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <limits.h>
#include <math.h>

using namespace std;

template <typename T>
void print(T [], int);

template <typename T> class SA;
template <typename T> ostream& operator<< (ostream& os, const SA<T>& s);

template <typename T>
class SA {
  private:
    int low, high, size;
    T* p;

  public:
    SA();
    SA(int);
    SA(int,int);
    SA(const SA&);
    ~SA();

    int length();

    T& operator[](int);
    SA & operator=(const SA &);
    operator T*();

    friend ostream& operator<< <T>(ostream& os, const SA<T>& s);
};

template <typename T>
class Matrix {
  private:
    SA< SA<T> > matrix;
    int row1, row2;
    int col1, col2;

  public:
    Matrix();
    Matrix(int,int);
    Matrix(int,int,int,int);

    SA<T>& operator[](int);
    operator SA<T>*();
};

template <typename T>
class VNT : public Matrix<T> {
    private:
        Matrix<T> vnt;
        int row1, row2;
        int col1, col2;
        int min;

    public:
        // Constructors
        VNT(int,int);
        VNT(int,int,int,int);

        void init();
        void add(T);
        T getMin();
        bool find(T);
        void sort();
        void sort(T [], int);
        void print();

        SA<T>& operator[](int);
        operator SA<T>*();
};

int main() {

    VNT<int> r(2,2);
    int A[4] = {55,2,11,77};
    int size = sizeof(A)/sizeof(A[0]);

    cout << "Array before sorting" << endl;
    print(A,size);
    cout << endl;

    r.sort(A,size);

    cout << "Array after sorting" << endl;
    print(A,size);
    cout << endl;

    VNT<int> m(2,3);

    m.add(4);
    m.add(2);
    m.add(22);
    m.add(211);
    m.add(333);
    m.add(15);

    cout << "Printing VNT" << endl;
    m.print();
    cout << endl;

    int element = 4;

    if( m.find(element) )
        cout << "Element " << element << " Found!" << endl << endl;
        
    else
        cout << "Element " << element << " not Found!" << endl << endl;

    int min = m.getMin();
    cout << "min = " << min << endl << endl;
    
    cout << "Printing VNT" << endl;
    m.print();

    return 0;
}

/******************************
  * Prints the elements of
  * an array
******************************/
template<typename T>
void print(T A[], int size) {
    for(int i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << endl;
}

/******************************
  *  Default Constructor
******************************/
template<typename T>
SA<T>::SA() {
    low = 0; 
    high = -1;
    size = 0;
    p = NULL;
}

/******************************
  *  Generic Constructor 1
******************************/
template<typename T>
SA<T>::SA(int low, int high){   
    if((high-low+1) <= 0) {
        cout<< "constructor error in bounds definition" << endl;
        exit(1);
    }
    
    this->low = low;
    this->high = high;
    size = high-low+1;
    p = new T[size];
}

/******************************
  *  Generic Constructor 2
******************************/
template<typename T>
SA<T>::SA(int i) {
    low = 0;
    high = i-1;
    size = i;
    p = new T[size];
}

/******************************
  *     Copy Constructor
******************************/
template<typename T>
SA<T>::SA(const SA& s){
    size = s.high - s.low + 1;
    p = new T[size];

    for(int i = 0; i < size; i++)
        p[i] = s.p[i];
    low = s.low;
    high = s.high;
}

/*************************
  *  Destructor
**************************/
template<typename T>
SA<T>::~SA() {
    delete [] p;
}

/******************************
  * Overload [] lets us write
  * SA r(12,31); r[14] = 1
******************************/
template<typename T>
T& SA<T>::operator[](int i) {
    if(i < low || i > high) {
        cout << "index "<< i <<" out of range" << endl;
        exit(1);
    }

    size = i - low;
    return p[size];
}

/******************************
  * Overload = lets us assign
  * one SA object to another
******************************/
template<typename T>
SA<T>& SA<T>::operator=(const SA & s){
    if(this == &s)
        return *this;

    delete [] p;
    size = s.high - s.low + 1;
    p = new T[size];

    for(int i = 0; i < size; i++)
        p[i] = s.p[i];

    low = s.low;
    high = s.high;

    return *this;
}

/******************************
  * Returns the number of 
  * elements in SA
******************************/
template<typename T>
int SA<T>::length() {
    return size;
}

/******************************
  * Conversion function
******************************/
template<typename T>
SA<T>::operator T*() {
    return p;
}

/**********************************
  * Overloading operator << allows
  * us to display SA objects
***********************************/
template <typename T>
ostream& operator<<(ostream& os, const SA<T>& s) {
    int size = s.high - s.low + 1;

    for(int i = 0; i < size; i++)
        os << s.p[i];
    return os;
}

/******************************
  *  Default Constructor
******************************/
template<typename T>
Matrix<T>::Matrix() {

}

/******************************
  *  Generic Constructor 1
******************************/
template<typename T>
Matrix<T>::Matrix(int row, int col) {
    matrix = SA< SA<T> >(0, row-1);
    
    for(int i = 0; i < row; i++)
        matrix[i] = SA<T>(0, col-1);
}

/******************************
  * Generic Constructor 2
*******************************/
template<typename T>
Matrix<T>::Matrix(int row1, int row2, int col1, int col2) {
    matrix = SA< SA<T> >(row1, row2-1);
    
    for(int i = row1; i < row2; i++)
        matrix[i] = SA<T>(col1, col2-1);
}

/******************************
  * Overload [] lets us write
  * Matrix r(12,31); r[1][14] = 1
******************************/
template<typename T>
SA<T>& Matrix<T>::operator[](int r) {
    return matrix[r];
}

/******************************
  * Conversion Function
******************************/
template<typename T>
Matrix<T>::operator SA<T>*() {
    return matrix;
}

/******************************
  * Generic Constructor 1
******************************/
template<typename T>
VNT<T>::VNT(int row1, int row2, int col1, int col2) : Matrix<T>(row1,row2,col1,col2) {
    vnt = Matrix<T>(row1,row2,col1,col2);

    this->row1 = row1;
    this->row2 = row2;
    this->col1 = col1;
    this->col2 = col2;

    init();
}

/******************************
  * Generic Constructor 2
******************************/
template<typename T>
VNT<T>::VNT(int row, int col) : Matrix<T>(row,col) {
    vnt = Matrix<T>(row,col);

    this->row1 = 0;
    this->row2 = row;
    this->col1 = 0;
    this->col2 = col;

    init();
}

/******************************
  * Insert elements in the VNT
  * while maintaining making sure
  * that the elements are sort
  * in ascending order
******************************/
template<typename T>
void VNT<T>::add(T element) {
    
    for(int i = row1; i < row2; i++) {
        for(int j = col1; j < col2; j++) {
            if(vnt[i][j] == INT_MAX) {
                vnt[i][j] = element;
                sort();
                return;
            }
        }
    }
} 

/******************************
  * Fills the VNT with values
  * of INT_MAX as a way to mark
  * that the VNT is empty
******************************/
template<typename T>
void VNT<T>::init() {
    min = INT_MAX;

    for(int i = row1; i < row2; i++) {
        for(int j = col1; j < col2; j++)
            vnt[i][j] = INT_MAX;
    }
}

/******************************
  * Overload [] lets us write
  * VNT r(12,31); r[1][14] = 1
******************************/
template<typename T>
SA<T>& VNT<T>::operator[](int r) {
    return vnt[r];
}

/******************************
  * Conversion Function
******************************/
template<typename T>
VNT<T>::operator SA<T>*() {
    return vnt;
}

/******************************
*   Extracts the smallest element
*   from the VNT while maintaining 
*   its VNTnest (order).
******************************/
template<typename T>
T VNT<T>::getMin() {
    min = vnt[0][0];
    vnt[0][0] = INT_MAX;
    sort();
    return min;
}

/******************************
*   Checks whether an element is
*   in the VNT or not.
******************************/
template<typename T>
bool VNT<T>::find(T element) {

    for(int i = row1; i < row2; i++)
        for(int j = col1; j < col2; j++)
            if(element == vnt[i][j])
                return true;

    return false;
}

/******************************
*   Sorts the VNT which is an
*   underlying 2D Array
******************************/
template<typename T>
void VNT<T>::sort() {
    // Represents the 2D Array (vnt) as a 1D Array
    int rowSize = row2 - row1;
    int colSize = col2 - col1;

    T* A = new T[rowSize * colSize];
    int index = 0;

    for(int i = row1; i < row2; i++)
        for(int j = col1; j < col2; j++)
            A[index++] = vnt[i][j];

    // Sorting the 1D Array in Ascending Order
    int temp;

    for(int i = 0; i < (rowSize * colSize)-1; i++) {
        for(int j = i+1; j < (rowSize * colSize); j++) {
            if(A[i] > A[j]) {
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
            }
        }
    }

    // Converting the 1D Array back to a 2D Array
    index = 0;

    for(int i = row1; i < row2; i++)
        for(int j = col1; j < col2; j++)
            vnt[i][j] = A[index++];

    delete [] A;
}

/******************************
*   Sorts a 1D array with the
*   using a VNT
******************************/
template<typename T>
void VNT<T>::sort(T A[], int size) {
    // VNT(sqrt(size),sqrt(size)); Use if size is a perfect square
    VNT(2,size); // Behaves as a 1D array 
    int index = 0;
    
    while(index < size)
        add(A[index++]);

    for(int i = 0; i < size; i++)
        A[i] = getMin();
}

/******************************
*   Prints the elements of a
*   VNT in a row, column fashion
******************************/
template<typename T>
void VNT<T>::print() {
    for(int i = row1; i < row2; i++) {
        for(int j = col1; j < col2; j++) {
            cout << vnt[i][j] << "\t";
        }
        cout << endl;
    }
}