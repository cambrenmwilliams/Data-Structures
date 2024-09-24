#include <iostream>
#include <string>

using namespace std;

class Chip {
    private:
        char chipType;    // Type of the chip (A: Addition, etc)
        string id;        // Unique identifier for the chip
        Chip* input1;     // pointer to the first input chip
        Chip* input2;     // pointer to the second input chip (can be NULL)
        Chip* output;     // pointer to the output chip (can be NULL)
        double inputValue; // for the input chip

    public:
        // Constructor
        Chip(char type, const string& id);

        // Method prototypes
        void setInput1(Chip* inputChip);  // Sets the first input chip
        void setInput2(Chip* inputChip);  // Sets the second input chip (can be NULL)
        void setOutput(Chip* outputChip); // Sets the output chip (can be NULL)
        void compute();                   // Performs thej operation based on the chip type

        void display() const;             // Displays the chip information
            //example: I6, Output = S600 --- for the input Chip
            //example: O50, Input 1 = S600 --- for the output Chip
            //example: A100, Input 1 = I1, Input 2 = I2, Output = M300
        string getId() const; // Returns the chip id

        //******* OTHER METHODS AS NECESSARY ********
        // Destructor
        ~Chip();
        // Getter
        Chip* getInput1();
        Chip* getInput2();
        // Setter
        void setInputValue(double value);

};

// Constructor
Chip::Chip(char type, const string& id) {
    chipType = type;  // Set the chip type
    this->id = id;  // Set the chip id
    input1 = NULL;  // Set the input1 to NULL
    input2 = NULL;  // Set the input2 to NULL
    inputValue = 0;  // Set the input value to 0
}

// Setters
void Chip::setInput1(Chip* inputChip) {  // Set the first input chip
    input1 = inputChip;  // Set the input1 to the inputChip
}

void Chip::setInput2(Chip* inputChip) {  // Set the second input chip
    input2 = inputChip;  // Set the input2 to the inputChip
}

void Chip::setOutput(Chip* outputChip) {  // Set the output chip
    output = outputChip;  // Set the output to the outputChip
}

void Chip::setInputValue(double value) {  // Set the input value
    inputValue = value;
}

//Getter
string Chip::getId() const {
    return id;
}

Chip* Chip::getInput1() {
    return input1;
}

Chip* Chip::getInput2() {
    return input2;
}


// Other methods
void Chip::compute() {
    // Perform the operation based on the chip type
    // For example, if the chip type is A, then add the two inputs
    // and store the result in the output chip
    if(chipType == 'O') {
        if(input1!=nullptr) {
            input1->compute();
            cout << "The output value from this circuit is " << input1->inputValue << endl;
        }
    }
    if(chipType == 'A') {  // Addition
        if(input1!=nullptr) {  // Checks if input1 is not NULL before preforming addition
            input1->compute();  // Uses recursion to compute the input1 chip
        }
        if(input2!=nullptr) {  // Checks if input2 is not NULL before preforming addition
            input2->compute();  // Uses recursion to compute the input2 chip
        }
        if(input1 !=nullptr && input2 !=nullptr) {  // Checks if input1 and input2 are not NULL
            inputValue = input1->inputValue + input2->inputValue;  // Adds the input1 and input2 values
        }
    }
    if(chipType == 'S') { // Subtraction
        if(input1!=nullptr) {  // Checks if input1 is not NULL before preforming subtraction
            input1->compute();  // Uses recursion to compute the input1 chip
        }
        if(input2!=nullptr) {  // Checks if input2 is not NULL before preforming subtraction
            input2->compute();  // Uses recursion to compute the input2 chip
        }
        if(input1 !=nullptr && input2 !=nullptr) {  // Checks if input1 and input2 are not NULL
            inputValue = input1->inputValue - input2->inputValue;  // Subtracts the input1 and input2 values
        }  
    }
    if(chipType == 'M') {  // Multiplication
        if(input1!=nullptr) {  // Checks if input1 is not NULL before preforming multiplication
            input1->compute();  // Uses recursion to compute the input1 chip
        }
        if(input2!=nullptr) {  // Checks if input2 is not NULL before preforming multiplication
            input2->compute();  // Uses recursion to compute the input2 chip
        }
        if(input1 !=nullptr && input2 !=nullptr) {  // Checks if input1 and input2 are not NULL
            inputValue = input1->inputValue * input2->inputValue;  // Multiplies the input1 and input2 values
        }
    }
    if(chipType == 'D') {  // Division
        if(input1!=nullptr) {  // Checks if input1 is not NULL before preforming division
            input1->compute();  // Uses recursion to compute the input1 chip
        }
        if(input2!=nullptr) {  // Checks if input2 is not NULL before preforming division
            input2->compute();  // Uses recursion to compute the input2 chip
        }
        if(input1 !=nullptr && input2 !=nullptr) {  // Checks if input1 and input2 are not NULL
            inputValue = input1->inputValue / input2->inputValue;  // Divides the input1 and input2 values
        }
    }   
    if(chipType == 'N') {  // Negation 
        if(input1!=nullptr) {  // Checks if input1 is not NULL before preforming negation
            input1->compute();  // Uses recursion to compute the input1 chip
        }
        if(input1 !=nullptr) {  // Checks if input1 is not NULL
            inputValue = -input1->inputValue;  // Negates the input1 value
        }
    } 

}

void Chip::display() const {
    // Display the chip information
    // For example, if the chip type is I, then display the input value
    // For example, if the chip type is O, then display the output value
    // For example, if the chip type is A, then display the two input values
    // and the output value
    if(chipType == 'I') {  // Input
        cout << id << ", Output = " << output->getId() << endl;  // Display the input value
    }
    if(chipType == 'O') {  // Output
        cout << id << ", Input 1 = " << input1->getId() << endl;  // Display the output value
    }
    if(chipType == 'A') {
        cout << id << ", Input 1 = " << input1->getId() << ", Input 2 = " << input2->getId() << ", Output = " << output->getId() << endl;
    }
    if(chipType == 'S') {
        cout << id << ", Input 1 = " << input1->getId() << ", Input 2 = " << input2->getId() << ", Output = " << output->getId() << endl;
    }
    if(chipType == 'M') {
        cout << id << ", Input 1 = " << input1->getId() << ", Input 2 = " << input2->getId() << ", Output = " << output->getId() << endl;
    }
    if(chipType == 'D') {
        cout << id << ", Input 1 = " << input1->getId() << ", Input 2 = " << input2->getId() << ", Output = " << output->getId() << endl;
    }
    if(chipType == 'N') {
        cout << id << ", Input 1 = " << input1->getId() << ", Input 2 = None, Output = " << output->getId() << endl;
    }
}

// Destructor
Chip::~Chip(){
    // This destructor also deletes the inputs to free space
    if(!(input1 == NULL)) {  // Check if input1 is not NULL
        delete input1;  // Delete the input1
    }
    if(!(input2 == NULL)) {  // Check if input2 is not NULL
        delete input2;  // Delete the input2
    }
}

int main () {
    //**** ALL THE VARIABLES YOU NEED FOR THIS MAIN FUNCTION *****//
    cout << "Computation Starts" << endl;
    int numChips;  // Number of chips
    Chip** allChips;  // Array of Chip objects pointers
    int numCommands;  // Number of commands

    cin >> numChips;  // Read the number of chips
    //create an array Chip objects pointers
    allChips = new Chip*[numChips]; // Creates an array of Chip objects pointers
    //each array location is a pointer to a Chip Object
    
    for (int i=0; i < numChips; i++) {
        //read the chip ID based on the first letter to determine its type
        //create the chip object and initialize it appropriately
        //store the chip object in the allChips array
        char type;      //type of the chip
        cin >> type;    //read the type of the chip
        string id;      //id of the chip
        cin >> id;      //read the id of the chip
        id = type + id; //add the type to the id
        Chip* chip = new Chip(type, id); //create the chip object
        allChips[i] = chip; //store the chip object in the allChips array
    }
    
    cin >> numCommands; //read the number of commands
    for (int i=0; i < numCommands; i++) {
        // read from input the links and make the appropriate
        //connections. You may need to search the array allChips
        //to find the chip that is referred and connect.
        // If the first letter is an O, then execute the compute method
        // on the object referred.
        string command;  // stores the command
        string input;    // stores the input
        string chipId;   // stores the chip id
        double value;    // stores the value if possible
        cin >> command;  // reads in the command
        if(command == "A") {  // If the command is Association, this will associate the input chip with the output chip
            cin >> input >> chipId; // Reads in the input and chip id
            //find the chip with the id chipId
            int indexOfInput; 
            int indexOfOutput; 
            for(int a = 0; a < numChips; a++) { // Loops through the allChips array to find the input and output chip
                if(allChips[a]->getId() == input) {
                    indexOfInput = a; // Sets the index of the input chip
                }
                if(allChips[a]->getId() == chipId) {
                    indexOfOutput = a; // Sets the index of the output chip
                }
            }
            if(allChips[indexOfOutput]->getInput1() == NULL) { // Checks if the input1 of the output chip is NULL
                allChips[indexOfOutput]->setInput1(allChips[indexOfInput]); // Sets the input1 of the output chip to the input chip
            }
            else {
                allChips[indexOfOutput]->setInput2(allChips[indexOfInput]); // Sets the input2 of the output chip to the input chip
            }
            allChips[indexOfInput]->setOutput(allChips[indexOfOutput]); // Sets the output of the input chip to the output chip
            
        }
        else if(command == "I") { // If the command is Input, this will set the input value of the chip
            cin >> chipId >> value; // Reads in the chip id and value
            //find the chip with the id chipId
            for(int j=0; j < numChips; j++) { // Loops through the allChips array to find the chip
                if(allChips[j]->getId() == chipId) { // Checks if the chip id is equal to the chip id in the allChips array
                    //connect the input value to the chip
                    allChips[j]->setInput1(allChips[j]); // Sets the input1 of the chip to the chip
                    allChips[j]->setInputValue(value); // Sets the input value of the chip
                    break;
                }
            }
        }
        else if(command == "O") {
            cin >> chipId;
            //find the chip with the id chipId
            for(int j=0; j < numChips; j++) {
                if(allChips[j]->getId() == chipId) {
                    //execute the compute method on the chip
                    allChips[j]->compute(); 
                    break;
                }
            }
        }
    }
    cout << "***** Showing the connections that were established" << endl;
    //for each component created call the display () method
    Chip* outputChip;
    for(int c = 0; c < numChips; c++) {
        if(allChips[c]->getId()[0] == 'O') {
            outputChip = allChips[c];
        }
        else {
            allChips[c]->display();
        }
    }
    outputChip->display();
    delete outputChip;
    //delete the memory allocated for the chip objects
    for(int d = 0; d < numChips; d++) {
        delete allChips[d];
    }
    delete[] allChips;
    return 0;
}

/********************Documentation *******************/
// LLM Usage



// Debugging and Testing
/*
    Incremental Development

    1. Created the construtor and destructor for the Chip class.

    2. Wrote the main function to read the input and create the Chip objects.
       This was tested by running the program with an input to check if chip
       were created successfully.

    3. Wrote the main fuction section that creates connections between the chips.
       This was tested by running the program with an input to check if the connections
       were established successfully. During this test run, an cout statement was added
       to display the connections that were established.

    4. Wrote the compute method for the Chip class. It works by checking input1 and input2
       for NULL values. If they are NULL, the compute method is called recursively. This was
       tested by running the program with an input to check if the compute method was working
       correctly. After testing, I realized that the pointer to the output chip was not being
       set.

    5. Corrected the pointer to the output chip, but the compute method would not work correctly.
       To be more specific, the output for the input1.txt sample file was outputing
       17 rather than 136. I asked CoPilot what the issue with the compute method was and it
       corrected the error.

    6. Checked everything was working correctly with all the sample input files.

    7. Added the display method to the Chip class. After running a for loop in main to test
       the display method, I realized the display method was outputing the address rather
       than the id of the chip. I corrected this by calling getId().

    8. Called the destructor in the main function to delete the memory allocated for the chip objects.



*/
