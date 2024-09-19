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

};

// Constructor
Chip::Chip(char type, const string& id) {
    chipType = type;
    this->id = id;
    input1 = NULL;
    input2 = NULL;
    inputValue = 0;
}

// Setters
void Chip::setInput1(Chip* inputChip) {
    input1 = inputChip;
}

void Chip::setInput2(Chip* inputChip) {
    input2 = inputChip;
}

void Chip::setOutput(Chip* outputChip) {
    output = outputChip;
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
        if(input1==NULL) {
            input1->compute();
        }
        cout << "The output value from this circuit is " << input1->inputValue << endl;
    }
    if(chipType == 'A') {
        if(input1==NULL) {
            input1->compute();
        }
        if(input2==NULL) {
            input2->compute();
        }
        if(input1 != NULL && input2 != NULL) {
            output->inputValue = input1->inputValue + input2->inputValue;
        }
        cout << "ADD" << endl;
    }
    if(chipType == 'S') {
        if(input1==NULL) {
            input1->compute();
        }
        if(input2==NULL) {
            input2->compute();
        }
        if(input1 != NULL && input2 != NULL) {
            output->inputValue = input1->inputValue - input2->inputValue;
        }
        cout << "SUB" << endl;
    }
    if(chipType == 'M') {
        if(input1==NULL) {
            input1->compute();
        }
        if(input2==NULL) {
            input2->compute();
        }
        if(input1 != NULL && input2 != NULL) {
            output->inputValue = input1->inputValue * input2->inputValue;
        }
        cout << "MUL" << endl;
    }
    if(chipType == 'D') {
        if(input1==NULL) {
            input1->compute();
        }
        if(input2==NULL) {
            input2->compute();
        }
        if(input1 != NULL && input2 != NULL) {
            output->inputValue = input1->inputValue / input2->inputValue;
        }
        cout << "DIV" << endl;
    }   
    if(chipType == 'N') {
        if(input1==NULL) {
            input1->compute();
        }
        if(input1 != NULL) {
            output->inputValue = -input1->inputValue;
        }
        cout << "NEG" << endl;
    } 

}

void Chip::display() const {
    // Display the chip information
    // For example, if the chip type is I, then display the input value
    // For example, if the chip type is O, then display the output value
    // For example, if the chip type is A, then display the two input values
    // and the output value
}

// Destructor
Chip::~Chip(){
    if(!(input1 == NULL)) {
        delete input1;
    }
    if(!(input2 == NULL)) {
        delete input2;
    }
}

int main () {
    //**** ALL THE VARIABLES YOU NEED FOR THIS MAIN FUNCTION *****//
    cout << "Computation Starts" << endl;
    int numChips;
    Chip** allChips;
    int numCommands;

    cin >> numChips;
    //create an array Chip objects pointers
    allChips = new Chip*[numChips];
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
    cout << "***** Showing the chips that were created" << endl;
    
    cin >> numCommands; //read the number of commands
    for (int i=0; i < numCommands; i++) {
        // read from input the links and make the appropriate
        //connections. You may need to search the array allChips
        //to find the chip that is referred and connect.
        // If the first letter is an O, then execute the compute method
        // on the object referred.
        string command;
        string input;
        string chipId;
        double value;
        cin >> command;
        if(command == "A") {
            cin >> input >> chipId;
            //find the chip with the id chipId
            int indexOfInput;
            int indexOfOutput;
            for(int a = 0; a < numChips; a++) {
                if(allChips[a]->getId() == input) {
                    indexOfInput = a;
                }
                if(allChips[a]->getId() == chipId) {
                    indexOfOutput = a;
                }
            }
            if(allChips[indexOfOutput]->getInput1() == NULL) {
                allChips[indexOfOutput]->setInput1(allChips[indexOfInput]);
            }
            else {
                allChips[indexOfOutput]->setInput2(allChips[indexOfInput]);
            }
            allChips[indexOfInput]->setOutput(allChips[indexOfOutput]);
            cout << "Connected " << input << " to " << chipId << endl;
        }
        else if(command == "I") {
            cin >> chipId >> value;
            //find the chip with the id chipId
            for(int j=0; j < numChips; j++) {
                if(allChips[j]->getId() == chipId) {
                    //connect the input value to the chip
                    allChips[j]->setInput1(allChips[j]);
                    cout << "Connected " << value << " to " << chipId << endl;
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

    5.




*/