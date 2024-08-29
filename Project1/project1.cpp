#include <iostream>

using namespace std;

class SparseRow {
    protected:
        int row; //Row#
        int col; //Column#
        int value; //We will assume that all our values will be integers
    public:
        SparseRow (); //default constructor; row=-1;col=-1;value=0
        void display(); // print Row#, Column#, value
        ostream& operator<< (ostream& s, const SparseRow);
        //other methods that are necessary such as get and set
        //Getters
        int getRow();
        int getCol();
        int getValue();
        //Setters
        void setRow(int r);
        void setCol(int c);
        void setValue(int v);
};

SparseRow::SparseRow() { //Default constructor here
    row = -1;
    col = -1;
    value = 0;
}

void SparseRow::display() {  //Display method here
    cout << row << ", " << col << ", " << value << endl;
}

ostream& SparseRow::operator<< (ostream&s, const SparseRow) {

}

int SparseRow::getRow() {
    return row;
}

int SparseRow::getCol() {
    return col;
}

int SparseRow::getValue() {
    return value;
}

void SparseRow::setRow(int r) {
    row = r;
}

void SparseRow::setCol(int c) {
    col = c;
}

void SparseRow::setValue(int v) {
    value = v;
}

SparseRow::~SparseRow() {     //Deconstructor

}

class SparseMatrix {
    protected:
        int noRows; //Number of rows of the original matrix
        int noCols; //Number of columns of the original matrix
        int commonValue; //read from input
        int noNonSparseValues;
        SparseRow* myMatrix; //Array
    public:
        SparseMatrix ();
        SparseMatrix (int n, int m, int cv, int noNSV);
        SparseMatrix* Transpose (); //Matrix Transpose
        SparseMatrix* Multiply (SparseMatrix& M);
        SparseMatrix* Add (SparseMatrix& M);
        ostream& operator<< (ostream& s, const SparseMatrix& sm);
        void displayMatrix (); //Display the matrix in its original format
        //other methods that are necessary such as get and set
}; 

//write the methods after the class definition
SparseMatrix::SparseMatrix() {   //Default Constructor
    noRows = 0;
    noCols = 0;
    commonValue = 0;
    noNonSparseValues = 0;
}

SparseMatrix::SparseMatrix(int n, int m, int cv, int noNSV) {   //Constructor
    //  Sets up the variables
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;

    //  For loop to make the sparse matrix
    for(int i = 0; i < noNonSparseValues; i++) {
        
    }

}


int main () {

    int n, m, cv, noNSV;
    SparseMatrix* temp;

    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
    
    //Write the Statements to read in the first matrix
    
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);
    
    //Write the Statements to read in the second matrix
    
    cout << “First one in matrix format” << endl;
    (*firstOne).displayMatrix();
    
    cout << “First one in sparse matrix format” << endl;
    cout << (*firstOne);
    
    cout << “Second one in matrix format” << endl;
    (*secondOne).displayMatrix();
    
    cout << “Second one in sparse matrix format” << endl;
    cout << (*secondOne);
    
    cout << “Transpose of the first one in matrix” << endl;
    cout << (*(*firstOne).Transpose());
    
    cout << “Matrix Addition Result” << endl;
    
    temp = (*(*firstOne).Addition(secondOne));
    cout << temp;
    (*temp).displayMatrix();
    
    cout << “Matrix Multiplication Result” << endl;
    
    temp = (*(*firstOne).Multiply(secondOne));
    cout << temp;
    (*temp).displayMatrix();
}

/*
    LLM and GitHub Copilot Usage




*/
/*
    Debugging and Testing Plan




*/
