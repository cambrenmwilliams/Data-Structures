#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class duplicateInsertion : public std::exception {
public:
    const char* what() const noexcept override {
        return "Duplicate insertion";
    }
};

class NotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Not found";
    }
};

template <typename DT>
class MTree {
   
    protected:
        int M; // Maximum number of children per node (M+1 way split)
        vector<DT> values; // Values stored in the node (M-1 values)
        vector<MTree*> children; // Pointers to child MTrees (M+1 children)
        MTree* root; // Pointer to the root of the MTree
   
    public:
        MTree(int M) : M(M), root(this) {}
        ~MTree();
        bool is_leaf() const; // Check if the current node is a leaf
        void insert(const DT& value); // Insert a value into the MTree
        void split_node(); // Split the node if it exceeds capacity (i.e >=M)
        MTree* find_child(const DT& value); // Find the correct child to follow
        bool search(const DT& value); // Search for a value in the MTree
        void remove(const DT& value); // Delete a value from the MTree
        void buildTree(vector<DT>& input_values); // Build the tree
        vector<DT> collect_values(); // Collect values from all leaf nodes
        bool find (const DT& value);
};

// Removed duplicate constructor definition

template <typename DT>
MTree<DT>::~MTree() {
    for (int i = 0; i < children.size(); i++) {
        delete children[i];
    }
}

template <typename DT>
bool MTree<DT>::is_leaf() const {
    return children.empty();
}

template <typename DT>
void MTree<DT>::insert(const DT& value) {
    if (search(value)) {
        throw duplicateInsertion();
    }
    if (is_leaf()) {
        values.push_back(value);
        std::sort(values.begin(), values.end());

        if (values.size() >= M) {
            split_node();
        }
    } else {
        MTree<DT>* child = find_child(value);
        child->insert(value);

        if(child->values.size() >= M) {
            child->split_node();
        }
    }
}

template <typename DT>
void MTree<DT>::split_node() {
    int splitIndex = (M + 1) / 2;
    MTree<DT>* new_node = new MTree<DT>(M);
    
    new_node->values = vector<DT>(values.begin() + (M + 1) / 2, values.end());
    values.resize(splitIndex);
    
    if (!is_leaf()) {
        new_node->children = vector<MTree<DT>*>(children.begin() + (M + 1) / 2, children.end());
        children.resize((M + 1) / 2);
    }

    if (this == root) {
        MTree<DT>* new_root = new MTree<DT>(M);
        new_root->values.push_back(values.back());
        new_root->children.push_back(this);
        new_root->children.push_back(new_node);
        root = new_root;
        new_root->root = new_root;
    } else {
        MTree<DT>* parent = dynamic_cast<MTree<DT>*>(children[0]);
        parent->values.push_back(values.back());
        parent->children.push_back(new_node);
        sort(parent->values.begin(), parent->values.end());
        
        if (parent->values.size() == M) {
            parent->split_node();
        }
    }
}


template <typename DT>
MTree<DT>* MTree<DT>::find_child(const DT& value) {
    for (int i = 0; i < values.size(); i++) {
        if (value < values[i]) {
            return children[i];
        }
    }
    return children[children.size() - 1];
}

template <typename DT>
bool MTree<DT>::search(const DT& value) {
    if (std::find(values.begin(), values.end(), value) != values.end()) {
        return true;
    }
    if (is_leaf()) {
        return false;
    }

    for (int i = 0; i < values.size(); i++) {
        if (value < values[i]) {
            return children[i]->search(value);
        }
    }
    return children.back()->search(value);
}

template <typename DT>
void MTree<DT>::remove(const DT& value) {
    if (values.empty()) {
        return;
    }
    if (value < values[0]) {
        children[0]->remove(value);
        return;
    }
    for (int i = 0; i < values.size(); i++) {
        if (values[i] == value) {
            values.erase(values.begin() + i);
            if (is_leaf()) {
                return;
            }
            if (children[i]->values.size() >= (M + 1) / 2) {
                values.insert(values.begin() + i, children[i]->values.back());
                children[i]->values.pop_back();
                return;
            }
            if (children[i + 1]->values.size() >= (M + 1) / 2) {
                values.insert(values.begin() + i, children[i + 1]->values.front());
                children[i + 1]->values.erase(children[i + 1]->values.begin());
                return;
            }
            children[i]->values.push_back(values[i]);
            values.erase(values.begin() + i);
            values.insert(values.begin() + i, children[i + 1]->values.front());
            children[i + 1]->values.erase(children[i + 1]->values.begin());
            return;
        }
        if (values[i] < value && value < values[i + 1]) {
            children[i + 1]->remove(value);
            return;
        }
    }
    children.back()->remove(value);
}

template <typename DT>
void MTree<DT>::buildTree(vector<DT>& input_values) {
    if (input_values.size() <= M - 1) {
        values = input_values;
    } else {
        int D = input_values.size() / M;
        for(int i = 0; i < M; i++) {
            int start = i * D;
            //cout << "start: " << start << " - ";
            int end;
            if (i == M - 1) {
                end = input_values.size() - 1;
                //cout << "end: " << end << endl;
            } else {
                end = start + D - 1;
                //cout << "end: " << end << endl;
                values.push_back(input_values[end]);
            }
            vector<DT> child_values(input_values.begin() + start, input_values.begin() + end + 1);
            MTree<DT>* child = new MTree<DT>(M);
            child->buildTree(child_values);
            children.push_back(child);
        }
    }
    
}

template <typename DT>
vector<DT> MTree<DT>::collect_values() {
    vector<DT> result;
    if (is_leaf()) {
        result.insert(result.end(), values.begin(), values.end());
        return values;
    }
    for (int i = 0; i < children.size(); i++) {
        vector<DT> child_values = children[i]->collect_values();
        result.insert(result.end(), child_values.begin(), child_values.end());
    }
    return result;
}

template <typename DT>
bool MTree<DT>::find(const DT& value) {
    return search(value);
}

int main() {
    int n; // Number of elements in the initial sorted array
    int MValue;
    int numCommands;
    char command;
    int value;
    
    // Read the number of elements in the initial sorted array
    cin >> n; 
    vector<int> mySortedValues(n);

    // Read n numbers from input and add them to the vector mySortedValues
    for (int i = 0; i < n; i++) {
        cin >> mySortedValues[i];
    }
    
    // Get the M value
    cin >> MValue;
    MTree<int>* myTree = new MTree<int>(MValue);
    myTree->buildTree(mySortedValues);

    // Get the number of commands
    cin >> numCommands;
    for (int i = 0; i < numCommands; i++) {
        // Read the command for each iteration
        cin >> command;
        switch (command) {
            case 'I': { // Insert
                cin >> value;
                //cout << "Inserting value = " << value << endl;
                try {
                    myTree->insert(value);
                    cout << "The value = " << value << " has been inserted." << endl;
                } catch (duplicateInsertion& e) {
                    cout << "The value = " << value << " already in the tree." << endl;
                }
                break;
            }

            case 'R': { // Remove
                cin >> value;
                try {
                    myTree->remove(value);
                    cout << "The value = " << value << " has been removed." << endl;
                } catch (NotFoundException& e) {
                    cout << "The value = " << value << " not found." << endl;
                }
                break;
            }

            case 'F': { // Find
                cin >> value;
                if (myTree->find(value)) {
                    cout << "The element with value = " << value << " was found." << endl;
                } else {
                    cout << "The element with value = " << value << " not found." << endl;
                }
                break;
            }

            case 'B': { // Rebuild tree
                vector<int> myValues = myTree->collect_values();
                myTree->buildTree(myValues);
                cout << "The tree has been rebuilt." << endl;
                break;
            }

            default: {
                cout << "Invalid command!" << endl;
                break;
            }
        }
    }

    cout << "Final list: ";
    for(int i = 0; i < myTree->collect_values().size(); i++) {
        cout << myTree->collect_values()[i] << " ";
    }

    delete myTree;

    return 0;
}
