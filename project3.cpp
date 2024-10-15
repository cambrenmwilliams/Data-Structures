#include <iostream>
using namespace std;

class CPUJob {
    public:
        int job_id; // Unique identifier for the job
        int priority; // Priority level of the job (1-10)
        int job_type; // Job type (1-10)
        int cpu_time_consumed; // Total CPU time consumed by the job
        int memory_consumed; // Total memory consumed thus far
        CPUJob(int job_id, int priority, int job_type, int cpu_time_consumed,
                int memory_consumed); // Constructor
        void display(); // Display the job details

        int getJobId() const;
        void setJobId(int job_id);

        int getPriority() const;
        void setPriority(int priority);

        int getJobType() const;
        void setJobType(int job_type);

        int getCpuTimeConsumed() const;
        void setCpuTimeConsumed(int cpu_time_consumed);

        int getMemoryConsumed() const;
        void setMemoryConsumed(int memory_consumed);
    };

CPUJob::CPUJob(int job_id, int priority, int job_type, int cpu_time_consumed,
        int memory_consumed) {
    this->job_id = job_id;
    this->priority = priority;
    this->job_type = job_type;
    this->cpu_time_consumed = cpu_time_consumed;
    this->memory_consumed = memory_consumed;
}

void CPUJob::display() {
    cout << "Job ID: " << job_id << ", Priority: " << priority << ", Job Type: "
    << job_type << ", CPU Time Consumed: " << cpu_time_consumed << ", Memory Consumed: "
    << memory_consumed << endl;
}

int CPUJob::getJobId() const { return job_id; }
void CPUJob::setJobId(int job_id) { CPUJob::job_id = job_id; }

int CPUJob::getPriority() const { return priority; }
void CPUJob::setPriority(int priority) { CPUJob::priority = priority; }

int CPUJob::getJobType() const { return job_type; }
void CPUJob::setJobType(int job_type) { CPUJob::job_type = job_type; }

int CPUJob::getCpuTimeConsumed() const { return cpu_time_consumed; }
void CPUJob::setCpuTimeConsumed(int cpu_time_consumed) { CPUJob::cpu_time_consumed = cpu_time_consumed; }

int CPUJob::getMemoryConsumed() const { return memory_consumed; }
void CPUJob::setMemoryConsumed(int memory_consumed) { CPUJob::memory_consumed = memory_consumed; }

template <class DT>
class Queue {
    public:
        DT* JobPointer; // Pointer to a job (e.g., CPUJob)
        Queue<DT>* next; // Pointer to the next node in the queue
        Queue(); // Constructor
        Queue(DT* JobPointer); // Constructor
        Queue<DT>* getNext();
};

template <class DT>
Queue<DT>::Queue() {
    JobPointer = nullptr;
    next = nullptr;
}

template <class DT>
Queue<DT>::Queue(DT* JobPointer) {
    this->JobPointer = JobPointer;
    next = nullptr;
}

template <class DT>
Queue<DT>* Queue<DT>::getNext() {
    return next;
}

template <class DT>
class NovelQueue {
    public:
        ~NovelQueue(); // Destructor
        NovelQueue(); // Default Constructor
        Queue<DT>* front; // Pointer to the front of the queue
        Queue<DT>** NodePtrs; // Array of pointers to Queue nodes
        int size; // Number of elements in the queue)
        void enqueue(DT JobPointer); // Add a new job to the queue
        DT dequeue(); // Remove a job from the queue
        void modify(int job_id, int new_priority, int new_job_type,
        int new_cpu_time_consumed, int new_memory_consumed); // Modify a job
        void change(int job_id, int field_index, int new_value); // Change a job value
        void promote(int job_id, int positions); // Promote a job
        NovelQueue<DT>* reorder(int attribute_index); // Reorder the queue
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
    Queue<DT>* newNode = new Queue<DT>(&JobPointer);
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
        cout << "Queue is empty!" << endl;
        return nullptr;
    }
    Queue<DT>* removedNode = front;
    front = front->next;
    size--;
    return *removedNode->JobPointer;
}

template <class DT>
void NovelQueue<DT>::modify(int job_id, int new_priority, int new_job_type,
        int new_cpu_time_consumed, int new_memory_consumed) {
    Queue<DT>* current = front;
    while (current) {
        if (current->JobPointer->getJobId() == job_id) {
            current->JobPointer->setPriority(new_priority);
            current->JobPointer->setJobType(new_job_type);
            current->JobPointer->setCpuTimeConsumed(new_cpu_time_consumed);
            current->JobPointer->setMemoryConsumed(new_memory_consumed);
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
        if (current->JobPointer->getJobId() == job_id) {
            switch (field_index) {
                case 1:
                    current->JobPointer->setPriority(new_value);
                    break;
                case 2:
                    current->JobPointer->setJobType(new_value);
                    break;
                case 3:
                    current->JobPointer->setCpuTimeConsumed(new_value);
                    break;
                case 4:
                    current->JobPointer->setMemoryConsumed(new_value);
                    break;
                default:
                    cout << "Invalid field index!" << endl;
            }
            return;
        }
        current = current->next;
    }
    cout << "Job not found!" << endl;
}

template <class DT>
void NovelQueue<DT>::promote(int job_id, int positions) {
    Queue<DT>* current = front;
    while (current) {
        if (current->JobPointer->getJobId() == job_id) {
            if (current == front) {
                cout << "Job is already at the front!" << endl;
                return;
            }
            Queue<DT>* previous = front;
            while (previous->next != current) {
                previous = previous->next;
            }
            previous->next = current->next;
            current->next = front;
            front = current;
            cout << "Job promoted!" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Job not found!" << endl;
}

template <class DT>
NovelQueue<DT>* NovelQueue<DT>::reorder(int attribute_index) {
    NovelQueue<DT>* reorderedQueue = new NovelQueue<DT>();
    Queue<DT>* current = front;
    while (current) {
        Queue<DT>* newNode = new Queue<DT>(current->JobPointer);
        if (reorderedQueue->size == 0) {
            reorderedQueue->front = newNode;
        } else {
            Queue<DT>* currentNew = reorderedQueue->front;
            while (currentNew->next) {
                currentNew = currentNew->next;
            }
            currentNew->next = newNode;
        }
        reorderedQueue->size++;
        current = current->next;
    }
    return reorderedQueue;
}

template <class DT>
void NovelQueue<DT>::display() {
    Queue<DT>* current = front;
    while (current) {
        (*current->JobPointer).display();
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
        cout << current->JobPointer->getJobId() << " ";
        current = current->next;
    }
    cout << endl;
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
                break;
            }   
            case 'R': { // Remove (Dequeue)
                CPUJob* removedJob = (*myNovelQueue).dequeue();
                if (removedJob) {
                cout << "Dequeued Job: ";
                (*removedJob).display();
                delete removedJob; // Clean up memory after use
                }
                break;
            }
            case 'M': { // Modify
                cin >> job_id >> new_priority >> new_job_type;
                cin >> new_cpu_time_consumed >> new_memory_consumed;
                (*myNovelQueue).modify(job_id, new_priority, new_job_type,
                new_cpu_time_consumed, new_memory_consumed);
                break;
            }
            case 'C': { // Change Job Values
                cin >> job_id >> field_index >> new_value;
                (*myNovelQueue).change(job_id, field_index, new_value);
                break;
            }
            case 'P': { // Promote
                cin >> job_id >> positions;
                (*myNovelQueue).promote(job_id, positions);
                break;
            }
            case 'O': { // Reorder
                cin >> attribute_index;
                NovelQueue<CPUJob*>* reorderedQueue =
                (*myNovelQueue).reorder(attribute_index);
                cout << "Reordered Queue:" << endl;
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