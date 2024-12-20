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
        friend ostream& operator<< (ostream& s, const SparseRow); //ostream method, 
        //other methods that are necessary such as get and set
        //Getters
        int getRow() const ; //The const is added because ostream requires it
        int getCol() const ; //This also ensures that the method does not change the object
        int getValue() const ;
        //Setters
        void setRow(int r);
        void setCol(int c);
        void setValue(int v);
};

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
        ~SparseMatrix(); //Deconstructor
        SparseMatrix* Transpose (); //Matrix Transpose
        SparseMatrix* Multiply (SparseMatrix& M);
        SparseMatrix* Add (SparseMatrix& M);
        friend ostream& operator<< (ostream& s, const SparseMatrix& sm); //ostream method
        void displayMatrix (); //Display the matrix in its original format
        void displaySparseMatrix (); //Display the matrix in its sparse format
        //other methods that are necessary such as get and set
        
        //Getters
        int getNoRows() const;
        int getNoCols() const ;
        int getCommonValue() const;
        int getNoNonSparseValues() const;
        SparseRow* getMyMatrix() const;

        //Setters
        void setNoRows(int n);
        void setNoCols(int m);
        void setCommonValue(int cv);
        void setNoNonSparseValues(int noNSV);
        void setMyMatrix(SparseRow* m);
}; 

//write the methods after the class definition

//Methods for SparseRow
SparseRow::SparseRow() { //Default constructor here
    row = -1;
    col = -1;
    value = 0;
}

void SparseRow::display() {  //Display method here
    cout << row << ", " << col << ", " << value << endl;
}

int SparseRow::getRow() const {
    return row;
}

int SparseRow::getCol() const {
    return col;
}

int SparseRow::getValue() const {
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

ostream& operator<< (ostream& s, const SparseRow& sr) {
    s << static_cast<const SparseRow&>(sr).getRow() << ", " << static_cast<const SparseRow&>(sr).getCol() << ", " << static_cast<const SparseRow&>(sr).getValue();
    return s;
}

// Methods for SparseMatrix
SparseMatrix::SparseMatrix() {   //Default Constructor
    noRows = 0;
    noCols = 0;
    commonValue = 0;
    noNonSparseValues = 0;
    myMatrix = NULL;
}

SparseMatrix::SparseMatrix(int n, int m, int cv, int noNSV) {   //Constructor
    //  Sets up the variables
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;
    myMatrix = new SparseRow[noNonSparseValues];
}

SparseMatrix::~SparseMatrix() { //Deconstructor
    delete[] myMatrix;
}

SparseMatrix* SparseMatrix::Transpose() {  //Method for matrix Transposal
    SparseMatrix* temp = new SparseMatrix(noCols, noRows, commonValue, noNonSparseValues); //Creates a new matrix
    
    for(int i = 0; i < noNonSparseValues; i++) { //For loop to go through all values
        temp->myMatrix[i].setRow(myMatrix[i].getCol()); //Sets row
        temp->myMatrix[i].setCol(myMatrix[i].getRow()); //Sets col
        temp->myMatrix[i].setValue(myMatrix[i].getValue()); //Sets value
    }

    return temp; //Returns the transposed matrix
}

SparseMatrix* SparseMatrix::Add(SparseMatrix& M) { //Method for matrix addition
    int maxNNSV = noNonSparseValues+M.noNonSparseValues; //Variable to store the maximum number of non-sparse values
    SparseMatrix* temp = new SparseMatrix(noRows, noCols, commonValue, maxNNSV); //Creates a new matrix
    int count = 0; //Variable to keep track of the number of non-sparse values in the new matrix
    for(int i = 0; i < noRows; i++) {
        for(int j = 0; j < noCols; j++) {
            bool found1 = false; //Flag to check if the value is found in the matrix
            bool found2 = false; //Flag to check if the value is found in the M matrix
            int tempValue = 0; //Variable to store the value
            int tempValue2 = 0; //Variable to store the value
            for(int k = 0; k < noNonSparseValues; k++){
                if(myMatrix[k].getRow() == i && myMatrix[k].getCol() == j) { //Checks if the value is in the first matrix
                    found1 = true; //Set the flag to true
                    tempValue = k;
                }
                if(M.myMatrix[k].getRow() == i && M.myMatrix[k].getCol() == j) { //Checks if the value is in the second matrix
                    found2 = true; //Set the flag to true
                    tempValue2 = k;
                   
                }
                if(found1 || found2) { //If the value is found in both matrices
                    break; //Exit the loop
                }
            }
            if(found1 && found2) { 
                temp->myMatrix[count].setRow(i); //Sets row
                temp->myMatrix[count].setCol(j); //Sets col
                temp->myMatrix[count].setValue(myMatrix[tempValue].getValue() + M.myMatrix[tempValue2].getValue()); //Sets value
                count++; //Increments the count
            } else if(found1) {
                temp->myMatrix[count].setRow(i); //Sets row
                temp->myMatrix[count].setCol(j); //Sets col
                temp->myMatrix[count].setValue(myMatrix[tempValue].getValue()); //Sets value
                count++; //Increments the count
            } else if(found2) {
                temp->myMatrix[count].setRow(i); //Sets row
                temp->myMatrix[count].setCol(j); //Sets col
                temp->myMatrix[count].setValue(M.myMatrix[tempValue2].getValue()); //Sets value
                count++; //Increments the count
            }
        }
    }   
    temp->setNoNonSparseValues(count); //Sets the number of non-sparse values in the new matrix
    return temp; //Returns the new matrix
}

SparseMatrix* SparseMatrix::Multiply(SparseMatrix& M) { //Method for matrix multiplication
    SparseMatrix* temp = new SparseMatrix(); //Creates a new matrix
    temp->setNoRows(noRows); //Sets noRows to temp
    temp->noCols = M.noCols; //Sets noCols to temp
    temp->commonValue = commonValue; //Sets commonValue to temp
    temp->noNonSparseValues = noNonSparseValues; //Sets noNonSparseValues to temp
    temp->myMatrix = new SparseRow[noNonSparseValues]; //Creates a new matrix

    for(int i = 0; i < noNonSparseValues; i++) { //For loop to go through all values
        temp->myMatrix[i].setRow(myMatrix[i].getRow()); //Sets row
        temp->myMatrix[i].setCol(M.myMatrix[i].getCol()); //Sets col
        temp->myMatrix[i].setValue(myMatrix[i].getValue() * M.myMatrix[i].getValue()); //Sets value
    }
    return temp; //Returns the new matrix
}

ostream& operator<< (ostream& s, const SparseMatrix& sm) { //Method for ostream
    for(int i = 0; i < sm.getNoNonSparseValues(); i++) { //For loop to go through all values
        s << sm.myMatrix << endl;
    }
    return s; //Returns the ostream
}


void SparseMatrix::displayMatrix() { //Method to display the matrix
    int i = 0; //Variable to count the values
    for(int k = 0; k < noRows; k++) { //For loop to go through all rows
        for(int j = 0; j < noCols; j++) { //For loop to go through all columns
            bool found = false; //Flag to check if the value is found in the matrix
            for(int l = 0; l < noNonSparseValues; l++) { //Loop through all non-sparse values
                if(myMatrix[l].getRow() == k && myMatrix[l].getCol() == j) { //Checks if the value is in the matrix
                    cout << myMatrix[l].getValue() << " "; //Prints the value
                    found = true; //Set the flag to true
                    break; //Exit the loop
                }
            }
            if(!found) { //If the value is not found in the matrix
                cout << commonValue << " "; //Prints the common value
            }
        }
        cout << endl; //Prints a new line
    }
}

void SparseMatrix::displaySparseMatrix() { //Method to display the sparse matrix
    for(int i = 0; i < noNonSparseValues; i++) { //For loop to go through all values
        cout << myMatrix[i].getRow() << ", " << myMatrix[i].getCol() << ", " << myMatrix[i].getValue() << endl; //Prints the value
    }
}

//Getters
int SparseMatrix::getNoRows() const {
    return noRows;
}
int SparseMatrix::getNoCols() const {
    return noCols;
}
int SparseMatrix::getCommonValue() const {
    return commonValue;
}
int SparseMatrix::getNoNonSparseValues() const {
    return noNonSparseValues;
}
SparseRow* SparseMatrix::getMyMatrix() const {
    return myMatrix;
}

//Setters
void SparseMatrix::setNoRows(int n) {
    noRows = n;
}
void SparseMatrix::setNoCols(int m) {
    noCols = m;
}
void SparseMatrix::setCommonValue(int cv) {
    commonValue = cv;
}
void SparseMatrix::setNoNonSparseValues(int noNSV) {
    noNonSparseValues = noNSV;
}
void SparseMatrix::setMyMatrix(SparseRow* m) {
    myMatrix = m;
}


//  Main function

int main () {

    int n, m, cv, noNSV;
    SparseMatrix* temp;

    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int value;
            cin >> value;
            if(value != cv) {
                firstOne->getMyMatrix()[count].setValue(value);
                firstOne->getMyMatrix()[count].setCol(j);
                firstOne->getMyMatrix()[count].setRow(i);
                count++;
            }
        }
    }
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);
    
    //Write the Statements to read in the second matrix
    //repeated code from above
    count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int value;
            cin >> value;
            if(value != cv) {
                secondOne->getMyMatrix()[count].setValue(value);
                secondOne->getMyMatrix()[count].setCol(j);
                secondOne->getMyMatrix()[count].setRow(i);
                count++;
            }
        }
    }

    cout << "First one in matrix format" << endl;
    (*firstOne).displayMatrix();
    
    cout << "First one in sparse matrix format" << endl;
    (*firstOne).displaySparseMatrix();
    
    
    cout << "Second one in matrix format" << endl;
    (*secondOne).displayMatrix();
    
    cout << "Second one in sparse matrix format" << endl;
    (*secondOne).displaySparseMatrix();
    
    cout << "Transpose of the first one in matrix" << endl;
    (*(*firstOne).Transpose()).displaySparseMatrix();
    
    cout << "Matrix Addition Result" << endl;
    
    (*(*firstOne).Add(*secondOne)).displayMatrix();
    
    cout << "Matrix Multiplication Result" << endl;
    
    temp = firstOne->Multiply(*secondOne);
    cout << temp;
    (*temp).displayMatrix();
    
    delete firstOne;
    delete secondOne;
    delete temp;

    return 0;
}

/*
    LLM and GitHub Copilot Usage

    Prompt: generate an ostream method for this method header: 
        ostream& operator<< (ostream& s, const SparseRow);
    
    Explanation: I was unsure on how the ostream method worked
        so I asked Copilot to generate a method and edited it 
        to fit the requirements.

    Prompt: this display matrix method only works in sorted 
        matrixes, adjust it for unsorted matrixes as well

    Explanation: My display matrix method failed to display 
        unsorted matrixes correctly when running the transpose 
        method. I asked Copilot how to adjust it.

    



*/
/*
    Debugging and Testing Plan




*/
