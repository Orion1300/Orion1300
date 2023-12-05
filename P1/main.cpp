#define MAX_SIZE 256
#include <iostream>
#include <string>


using namespace std;

struct queue {
    string data = "";
    struct queue* next;
};
struct queue* headQ = NULL;

struct stack {
    string data;
    struct stack* next;
};
struct stack* headS = NULL;



typedef struct NodeH {
    string key;         
    string value;       
    struct NodeH* next;  
} NodeH;

typedef struct HashTable {
    int size;      
    NodeH** table;  
} HashTable;


HashTable* createHashTable() {

    HashTable* hashTable = new HashTable; 

    hashTable->size = MAX_SIZE;   
    hashTable->table = (NodeH**)malloc(MAX_SIZE * sizeof(NodeH*)); 
    for (int i = 0; i < MAX_SIZE; i++) {
        hashTable->table[i] = NULL; 
    }
    return hashTable;
}
HashTable* hashTable = createHashTable();


int hashT(string key) {
    int k = 0;
    for (size_t i = 0; i < key.length(); i++)
    {
        k += (int)key[i] % MAX_SIZE;
    }
    return k % MAX_SIZE; 
}



string searchHash(HashTable* hashTable, string key) {
    int index = hashT(key); 
    NodeH* temp = hashTable->table[index]; 

    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value; 
        }
        temp = temp->next; 
    }
    return "";
}


void inserthesh(HashTable* hashTable, string key, string value) {
    int index = hashT(key); 
    NodeH* node = new NodeH; 
    if (searchHash(hashTable, key) == "") {
        node->key = key; 
        node->value = value; 
        node->next = hashTable->table[index]; 
        hashTable->table[index] = node;
    }
    else cout << "Ячейка занята\n";
}




void deleteHash(HashTable* hashTable, string key) {
    int index = hashT(key); 
    NodeH* current = hashTable->table[index];
    NodeH* prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                hashTable->table[index] = current->next; 
            }
            else {
                prev->next = current->next; 
            }
            free(current); 
            return;
        }
        prev = current;
        current = current->next;
    }
}


typedef struct NodeS {
    string key;                
    struct NodeS* next;  
} NodeS;

typedef struct Set {
    int size;      
    NodeS** table;  
} Set;


Set* createSet() {

    Set* set = new Set; 

    set->size = MAX_SIZE;   
    set->table = (NodeS**)malloc(MAX_SIZE * sizeof(NodeS*)); 
    for (int i = 0; i < MAX_SIZE; i++) {
        set->table[i] = NULL; 
    }
    return set;
}
Set* set = createSet();

bool searchSet(Set* set, string key) {
    int k = 0;
    for (size_t i = 0; i < key.length(); i++)
    {
        k += (int)key[i] % MAX_SIZE;
    }
    int index = k % MAX_SIZE; 
    NodeS* temp = set->table[index]; 

    while (temp != NULL) {
        if (temp->key == key) {
            return true; 
        }
        temp = temp->next; 
    }
    return false; 
}



int main() {
    setlocale(LC_ALL, "Russian");
    cout << "SADD\tSREM\tSISMEMBER\nSPUSH\tSPOP\tSPOP\nQPUSH\tQPOP\tQPOP\nHSET\tHDEL\tHGET\nBreak\n";
    while (true)
    {
        string command = "";
        cout << "Введите команду ";
        cin >> command;
        if (command == "SADD") {
            cout << "введите значение ";
            string key;
            cin >> key;
            int k = 0;
            for (size_t i = 0; i < key.length(); i++)
            {
                k += (int)key[i] % MAX_SIZE;
            }
            int index = k % MAX_SIZE; 
            NodeS* node = new NodeS; 
            if (searchSet(set, key) == false) {
                node->key = key; 
                node->next = set->table[index]; 
                set->table[index] = node; 
            }
            else cout << "занято\n";
        }
        
        else if (command == "SREM") {
            cout << "введите значение ";
            string key;
            cin >> key;
            int k = 0;
            for (size_t i = 0; i < key.length(); i++)
            {
                k += (int)key[i] % MAX_SIZE;
            }
            int index = k % MAX_SIZE; 

            NodeS* current = set->table[index];
            NodeS* prev = NULL;
            int k1 = 0;
            while (current != NULL) {
                if (current->key == key) {
                    if (prev == NULL) {
                        set->table[index] = current->next; 
                    }
                    else {
                        prev->next = current->next; 
                    }
                    free(current); 
                    k1 = 1;
                    break;
                }
                prev = current;
                current = current->next;
            }
            if (k1 == 0) cout << "element not found\n";
        }
       
        else if (command == "SISMEMBER") {
            cout << "введите значение ";
            string key;
            cin >> key;
            int k = 0;
            for (size_t i = 0; i < key.length(); i++)
            {
                k += (int)key[i] % MAX_SIZE;
            }
            int index = k % MAX_SIZE; 
            NodeS* temp = set->table[index]; 
            int k1 = 0;
            while (temp != NULL) {
                if (temp->key == key) {
                    k1 = 1; 
                    break;
                }
                temp = temp->next; 
            }
            if (k1 == 0) cout << "false\n";
            else cout << "true\n";
        }

        else if (command == "SPUSH") {
            cout << "введите значение ";
            string value;
            cin >> value;
            struct stack* newNode = new stack; 
            newNode->data = value;
            newNode->next = headS;
            headS = newNode;
        }

        else if (command == "SPOP") {
            string x;
            if (headS != NULL) {
                string value = headS->data;
                headS = headS->next;
                x = value;
            }
            else x = "";

            if (x == "") cout << "нет значений" << endl;
            else cout << x << endl;
        }
        
        else if (command == "QPUSH") {
            cout << "введите значение ";
            string value;
            cin >> value;
            struct queue* newNode = new queue; 

            newNode->data = value;
            newNode->next = NULL;

            if (headQ == NULL) { 
                headQ = newNode; 
            }
            else {
                struct queue* current = headQ;
                while (current->next != NULL) { 
                    current = current->next;
                }
                current->next = newNode; 
            }
        }
       
        else if (command == "QPOP") {
            string x = "";
            if (headQ != NULL) {
                string value = headQ->data;
                headQ = headQ->next;
                x = value;
            }
            if (x == "") cout << "нет значений" << endl;
            else cout << x << endl;
        }
        
        else if (command == "HSET") {
            cout << "введите значение ";
            string x;
            cin >> x;
            cout << "введите ключ ";
            string k;
            cin >> k;
            inserthesh(hashTable, k, x);
        }
        
        else if (command == "HDEL") {
            cout << "введите ключ ";
            string k;
            cin >> k;
            deleteHash(hashTable, k);
        }
        
        else if (command == "HGET") {
            cout << "введите ключ ";
            string k;
            cin >> k;
            cout << searchHash(hashTable, k) << endl;
        }
        
        else if (command == "Break") { break; }
        else {
            cout << "\n";
            command = "";
        }
    }
}
