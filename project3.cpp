#include <iostream>
using namespace std;

class CPUJob {
public:
    int job_id; // Unique identifier for the jobs
    int priority; // Priority level of the job (1-10)
    int job_type; // Job type (1-10)
    int cpu_time_consumed; // Total CPU time consumed by the job
    int memory_consumed; // Total memory consumed thus far
    CPUJob(int job_id, int priority, int job_type, int cpu_time_consumed, int memory_consumed); // Constructor
    void display(); // Display the job details
    ~CPUJob() {} // Destructor
};

CPUJob::CPUJob(int job_id, int priority, int job_type, int cpu_time_consumed, int memory_consumed)
    : job_id(job_id), priority(priority), job_type(job_type), cpu_time_consumed(cpu_time_consumed), memory_consumed(memory_consumed) {}

void CPUJob::display() {
    cout << "Job ID: " << job_id << ", Priority: " << priority << ", Job Type: "
         << job_type << ", CPU Time Consumed: " << cpu_time_consumed << ", Memory Consumed: "
         << memory_consumed << endl;
}

template <class DT>
class Queue {
public:
    DT JobPointer; // Pointer to a job (e.g., CPUJob*)
    Queue<DT>* next; // Pointer to the next node in the queue
    Queue(); // Constructor
    Queue(DT JobPointer); // Constructor
    Queue<DT>* getNext();
    DT find(int job_id);
};

template <class DT>
Queue<DT>::Queue() {
    JobPointer = nullptr;
    next = nullptr;
}

template <class DT>
Queue<DT>::Queue(DT JobPointer) {
    this->JobPointer = JobPointer;
    next = nullptr;
}

template <class DT>
Queue<DT>* Queue<DT>::getNext() {
    return next;
}

template <class DT>
DT Queue<DT>::find(int job_id) {
    Queue<DT>* current = this;
    while (current) {
        if (current->JobPointer->job_id == job_id) {
            return current->JobPointer;
        }
        current = current->next;
    }
    return nullptr;
}

template <class DT>
class NovelQueue {
public:
    ~NovelQueue(); // Destructor
    NovelQueue(); // Default Constructor
    Queue<DT>* front; // Pointer to the front of the queue
    int size; // Number of elements in the queue
    void enqueue(DT JobPointer); // Add a new job to the queue
    DT dequeue(); // Remove a job from the queue
    void modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed); // Modify a job
    void change(int job_id, int field_index, int new_value); // Change a job value
    void promote(int job_id, int positions); // Promote a job
    NovelQueue<DT>* reorder(int index); // Reorder the queue
    void display(); // Display the queue
    int count(); // Count the number of elements in the queue
    void listJobs(); // List all jobs in the queue
};

template <class DT>
NovelQueue<DT>::NovelQueue() {
    front = nullptr;
    size = 0;
}

template <class DT>
NovelQueue<DT>::~NovelQueue() {
    Queue<DT>* current = front;
    while (current) {
        Queue<DT>* next = current->next;
        delete current;
        current = next;
    }
}

template <class DT>
void NovelQueue<DT>::enqueue(DT JobPointer) {
    Queue<DT>* newNode = new Queue<DT>(JobPointer);
    if (size == 0) {
        front = newNode;
    } else {
        Queue<DT>* current = front;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode; 
    }
    size++;
}

template <class DT>
DT NovelQueue<DT>::dequeue() {
    if (size == 0) {
        return nullptr;
    }
    Queue<DT>* removedNode = front;
    front = front->next;
    size--;
    return removedNode->JobPointer;
}

template <class DT>
void NovelQueue<DT>::modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed) {
    Queue<DT>* current = front;
    while (current) {
        if (current->JobPointer->job_id == job_id) {
            current->JobPointer->priority = new_priority;
            current->JobPointer->job_type = new_job_type;
            current->JobPointer->cpu_time_consumed = new_cpu_time_consumed;
            current->JobPointer->memory_consumed = new_memory_consumed;
            return;
        }
        current = current->next;
    }
    cout << "Job not found!" << endl;
}

template <class DT>
void NovelQueue<DT>::change(int job_id, int field_index, int new_value) {
    Queue<DT>* current = front;
    while (current) {
        if (current->JobPointer->job_id == job_id) {
            switch (field_index) {
            case 1:
                current->JobPointer->priority = new_value;
                break;
            case 2:
                current->JobPointer->job_type = new_value;
                break;
            case 3:
                current->JobPointer->cpu_time_consumed = new_value;
                break;
            case 4:
                current->JobPointer->memory_consumed = new_value;
                break;
            default:
                cout << "Invalid field index!" << endl;
                return;
            }
            return;
        }
        current = current->next;
    }
    cout << "Job not found!" << endl;
}

template <class DT>
void NovelQueue<DT>::promote(int job_id, int positions) {
    if (positions <= 0 || !front) return;

    Queue<DT>* current = front;
    Queue<DT>* previous = nullptr;
    while (current && current->JobPointer->job_id != job_id) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        current->JobPointer->display();
        return;
    }

    if (previous) {
        previous->next = current->next;  // Remove current from its position
        current->next = front;           // Move it to the front
        front = current;
    }
}

template <class DT>
NovelQueue<DT>* NovelQueue<DT>::reorder(int index) {
    NovelQueue<DT>* reorderedQueue = new NovelQueue<DT>();
    Queue<DT>* current = front;
    switch (index) {
        case 1: // Job ID
            while (current) {
                reorderedQueue->enqueue(current->JobPointer);
                current = current->next;
            }
            break;
        case 2: // Priority
            while (current) {
                Queue<DT>* next = current->next;
                if (reorderedQueue->size == 0 || current->JobPointer->priority > reorderedQueue->front->JobPointer->priority) {
                    current->next = reorderedQueue->front;
                    reorderedQueue->front = current;
                } else {
                    Queue<DT>* current2 = reorderedQueue->front;
                    while (current2->next && current2->next->JobPointer->priority > current->JobPointer->priority) {
                        current2 = current2->next;
                    }
                    current->next = current2->next;
                    current2->next = current;
                }
                current = next;
            }
            break;
        case 3: // Job Type
            while (current) {
                Queue<DT>* next = current->next;
                if (reorderedQueue->size == 0 || current->JobPointer->job_type > reorderedQueue->front->JobPointer->job_type) {
                    current->next = reorderedQueue->front;
                    reorderedQueue->front = current;
                } else {
                    Queue<DT>* current2 = reorderedQueue->front;
                    while (current2->next && current2->next->JobPointer->job_type > current->JobPointer->job_type) {
                        current2 = current2->next;
                    }
                    current->next = current2->next;
                    current2->next = current;
                }
                current = next;
            }
            break;
        case 4: // CPU Time Consumed
            while (current) {
                Queue<DT>* next = current->next;
                if (reorderedQueue->size == 0 || current->JobPointer->cpu_time_consumed > reorderedQueue->front->JobPointer->cpu_time_consumed) {
                    current->next = reorderedQueue->front;
                    reorderedQueue->front = current;
                } else {
                    Queue<DT>* current2 = reorderedQueue->front;
                    while (current2->next && current2->next->JobPointer->cpu_time_consumed > current->JobPointer->cpu_time_consumed) {
                        current2 = current2->next;
                    }
                    current->next = current2->next;
                    current2->next = current;
                }
                current = next;
            }
            break;
        case 5: // Memory Consumed
            while (current) {
                Queue<DT>* next = current->next;
                if (reorderedQueue->size == 0 || current->JobPointer->memory_consumed > reorderedQueue->front->JobPointer->memory_consumed) {
                    current->next = reorderedQueue->front;
                    reorderedQueue->front = current;
                } else {
                    Queue<DT>* current2 = reorderedQueue->front;
                    while (current2->next && current2->next->JobPointer->memory_consumed > current->JobPointer->memory_consumed) {
                        current2 = current2->next;
                    }
                    current->next = current2->next;
                    current2->next = current;
                }
                current = next;
            }
            break;
    }    
    return reorderedQueue;

}

template <class DT>
void NovelQueue<DT>::display() {
    Queue<DT>* current = front;
    while (current) {
        current->JobPointer->display();
        current = current->next;
    }
}

template <class DT>
int NovelQueue<DT>::count() {
    return size;
}

template <class DT>
void NovelQueue<DT>::listJobs() {
    Queue<DT>* current = front;
    while (current) {
        cout << "Job ID: " << current->JobPointer->job_id << endl;
        current = current->next;
    }
}

int main() {
    int n; // Number of commands
    cin >> n; // Read the number of commands

    // Instantiate a NovelQueue for CPUJob pointers
    NovelQueue<CPUJob*>* myNovelQueue = new NovelQueue<CPUJob*>();

    char command; // Variable to store the command type

    // Variables for job attributes
    int job_id, priority, job_type, cpu_time_consumed, memory_consumed;

    // Variables for modifying a job
    int new_priority, new_job_type, new_cpu_time_consumed;
    int new_memory_consumed;
    int field_index, new_value;

    // Variable for the number of positions in the 'Promote' command
    int positions;
    int attribute_index; // Variable for the 'Reorder' command

    /************** Read each command Process ***************/
    for (int i = 0; i < n; ++i) {
        cin >> command; // Read the command type

        switch (command) {
        
            case 'A': { // Add (Enqueue)
                cin >> job_id >> priority >> job_type;
                cin >> cpu_time_consumed >> memory_consumed;
                CPUJob* newJob = new CPUJob(job_id, priority, job_type,
                        cpu_time_consumed, memory_consumed);
                (*myNovelQueue).enqueue(newJob);
                cout << "Enqueued Job: ";
                (*newJob).display();

                cout << "Jobs after enqueue:" << endl;
                (*myNovelQueue).display();

                break;
            }   
            case 'R': { // Remove (Dequeue)
                CPUJob* removedJob = (*myNovelQueue).dequeue();
                if (removedJob) {
                    cout << "Dequeued Job: " << endl;
                    (*removedJob).display();
                    delete removedJob; // Clean up memory after use

                    cout << "Jobs after dequeue:" << endl;
                    (*myNovelQueue).display();
                }
                break;
            }
            case 'M': { // Modify
                cin >> job_id >> new_priority >> new_job_type;
                cin >> new_cpu_time_consumed >> new_memory_consumed;
                (*myNovelQueue).modify(job_id, new_priority, new_job_type,
                new_cpu_time_consumed, new_memory_consumed);
                cout << "Modified Job ID " << job_id << ":" << endl;
                myNovelQueue->front->find(job_id)->display();
                cout << "Jobs after modification:" << endl;
                (*myNovelQueue).display();
                break;
            }
            case 'C': { // Change Job Values
                cin >> job_id >> field_index >> new_value;
                (*myNovelQueue).change(job_id, field_index, new_value);
                cout << "Changed Job ID " << job_id << " field " << field_index << " to " << new_value << ":" << endl;
                myNovelQueue->front->find(job_id)->display();
                cout << "Jobs after changing field:" << endl;
                (*myNovelQueue).display();

                break;
            }
            case 'P': { // Promote
                cin >> job_id >> positions;
                (*myNovelQueue).promote(job_id, positions);
                cout << "Promoted Job ID " << job_id << " by " << positions << " Position(s):" << endl;
                myNovelQueue->front->find(job_id)->display();
                cout << "Jobs after promotion:" << endl;
                (*myNovelQueue).display();
                break;
            }
            case 'O': { // Reorder
                cin >> attribute_index;
                NovelQueue<CPUJob*>* reorderedQueue =
                (*myNovelQueue).reorder(attribute_index);
                cout << "Reordered Jobs by attribute " << attribute_index << ":" << endl;
                (*reorderedQueue).display();
                break;
            }
            case 'D': { // Display
                (*myNovelQueue).display();
                break;
            }
            case 'N': { // Count
                cout << "Number of elements in the queue: " <<
                (*myNovelQueue).count() << endl;
                    break;
            }
            case 'L': { // List Jobs
                (*myNovelQueue).listJobs();
                break;
            }
            default:
                cout << "Invalid command!" << endl;
        }
    }

    delete myNovelQueue; // Clean up the NovelQueue after all operations
    return 0;
}
