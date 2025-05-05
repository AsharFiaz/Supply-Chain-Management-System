#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <string>
#include <queue>

using namespace std;
const int INT_MAX = 1e9;

struct Node
{  
    int id;
    string Location;
    float main_distance;
    int stock_level;
    int product_output;
    int usage_rate;
    int fuel_cost;
    int capacity;
    Node *next;
    Node *prev;
};

struct Node *head = NULL;
struct Node *tail = NULL;

const int TABLE_SIZE = 10;
Node* hashTable [TABLE_SIZE]= { NULL };
const int MAX_NODES = 100; 
int graph[MAX_NODES][MAX_NODES] = {0}; 


class que{
public:
int size;
Node** arr;
int front;
int rear;
que(){
    size =30;
    arr= new Node*[size];
    front = -1;
    rear=-1;
}
void enque(Node* a){
    if(isFull()){
        cout<<"Cannot enqueue"<<endl;
    }
    else {
        if(isEmpty()){
            front ++;
            rear++;
            arr[rear]=a;
            
        }
        else if(a->stock_level>=arr[rear]->stock_level){
            rear=rear+1;
            arr[rear]=a;
           
        }
        else{
            int temp = rear;
            while(a->stock_level<arr[temp]->stock_level){
                arr[temp+1]=arr[temp];
                temp--;
                if(temp==-1){
                     arr[0]=a;
                    rear=rear+1;
                    break;
                }
            }
           if (temp!=-1){
            arr[temp+1]=a;
            rear= rear+1;
        }}
        
    }
}
void deque(){
    if(isEmpty()){
        cout<< "nothing to dequeue"<< endl; 
    }
    else {
        if(rear==front){
         rear =-1;
         front = -1;
        }
        else{
            front = front +1;
        }
    }
}

bool isEmpty(){
    if (front ==-1){
    return true;
    }
    else {
        return false;
    }
 
}
bool isFull(){
    if ((rear+1) %size ==front){
      return true;
    }
    else {
        return false;
    }

} 
Node* getFront(){
    return arr[front];
    
}  
};


class st
{
    private:
    int size,top;
    public:
    Node** arr;
    st()
    {
        size=111;
        top=-1;
        arr= new Node*[size];
    }
    st(int a )
    {
        size=a;
        top=-1;
        arr= new Node*[size];
    }
    void push(Node* a )
    {
    if(isFull())
    {
        cout<<"Array is Full"<<endl;
    }
    else
    {
        arr[++top]=a;
    }
    }
    void pop()
    {
     if(isEmpty())
     {
        cout<<"Nothing to pop"<<endl;
     }   
     else
     {
        top--;
     }
    }
    bool isEmpty()
    {
        if(top==-1)
        {
            return true;
        }
        else
        {
            return false;
        }
   }
    bool isFull()
    {
        if(top==size-1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Node* atTop()
    {
      if(isEmpty())
      {
        return '\0';
      }
      else
      {
        return arr[top];
      }
          }
      int topValue()
      {
        return top;
    }    
};



void addNode(int id,string Location, float main_distance,  int  stock_level , int product_output ,int usage_rate,int fuel_cost , int capacity)
{
    
    Node *new_node = new Node;
    new_node->id =id;
    new_node->Location =Location;
    new_node-> main_distance= main_distance;
    new_node->stock_level=stock_level;
    new_node->product_output = product_output;
    new_node->usage_rate = usage_rate;
    new_node->fuel_cost = fuel_cost;
    new_node->capacity = capacity;
    new_node->next = NULL;
    
    if(head == NULL)
    {
        head = new_node;
        tail = new_node;
        new_node->next = NULL;
        return;
    }
    
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
}

void print()
{
    Node *ptr = head;
    cout << " ID    Location           main_distance           stock_level    product_output ,     usage_rate,    fuel_cost ,     capacity"<< endl;
    if (head!=NULL)
    {
       while (ptr)
       {
           cout<<ptr->id<<" , "<<ptr->Location<<" , "<<ptr-> main_distance<<" , "<<ptr-> stock_level<<" , "<<ptr->product_output<< ", "<<ptr->usage_rate<< ", "<<ptr->fuel_cost<<","<<ptr->capacity<< endl;
           ptr=ptr->next;
       }
    }
   else
    {
       cout << "List is empty"<<endl;
    }
}


void print(string Location )
{
    Node *ptr = head;
    cout << " ID    Location           main_distance           stock_level    product_output ,     usage_rate,    fuel_cost ,     capacity, " << endl;
    if (head!=NULL)
    {
        for (char& c : Location) {
            c = tolower(c);
        }
         for (char& c : ptr->Location) {
            c = tolower(c);
        }
        while (ptr!=NULL && ptr->Location!=Location)
        {  
            ptr=ptr->next;
             for (char& c : ptr->Location) {
            c = tolower(c);
        }
        }
        if(ptr!=NULL){
             cout<<ptr->id<<" , "<<ptr->Location<<" , "<<ptr-> main_distance<<" , "<<ptr-> stock_level<<" , "<<ptr->product_output<< ", "<<ptr->usage_rate<< ", "<<ptr->fuel_cost<<","<<ptr->capacity<<  endl;
        }
        else{
            cout << "Location you entered is invalid"<<endl;
        }
    }
    else
    {
       cout << "List is empty"<<endl;
    }
}


void calculateProductOutputOfChain()
{
    Node *ptr = head;
    int total=0;
    if (head!=NULL)
    {
       while (ptr)
       {
           total = total + ptr->product_output;
           ptr = ptr->next;
       }

       cout<<"Total Product ouput(kg/day) of supply chain is "<< total <<endl;
    }
   else
    {
       cout << "List is empty"<<endl;
    }
}

void transportationCostGreaterThan1000()
{
    Node *ptr = head;
    cout << " ID    Location           main_distance           stock_level    product_output ,     usage_rate,    fuel_cost ,     capacity"<< endl;
    if (head!=NULL)
    {
       while (ptr)
       {
        if(ptr->fuel_cost>=1000)
        {
           cout<<ptr->id<<" , "<<ptr->Location<<" , "<<ptr-> main_distance<<" , "<<ptr-> stock_level<<" , "<<ptr->product_output<< ", "<<ptr->usage_rate<< ", "<<ptr->fuel_cost<<","<<ptr->capacity<< endl;
        }
           ptr=ptr->next;
       }
    }
   else
    {
       cout << "List is empty"<<endl;
    }
}

void highestUtilizationRate()
{
    st s1;
    st s2;
    Node *ptr = head;
   
    cout << " ID    Location           main_distance           stock_level    product_output ,     usage_rate,    fuel_cost ,     capacity"<< endl;
    if (head!=NULL)
    {
       while (ptr)
       {
           if(s1.isEmpty())
           {
            s2.push(ptr);
           }
           else if(s2.atTop()->usage_rate<=ptr->usage_rate)
           {
            s2.push(ptr);
           }
            s1.push(ptr);
           ptr=ptr->next;
       }
       Node* temp=s2.atTop();
       cout<<temp->id<<" , "<<temp->Location<<" , "<<temp-> main_distance<<" , "<<temp-> stock_level<<" , "<<temp->product_output<< ", "<<temp->usage_rate<< ", "<<temp->fuel_cost<<","<<temp->capacity<< endl;
    }
   else
    {
       cout << "List is empty"<<endl;
    }
}


void searchByProductOutput(int output )
{
    Node *ptr = head;
    cout << " ID    Location           main_distance           stock_level    product_output ,     usage_rate,    fuel_cost ,     capacity, " << endl;
    if (head!=NULL)
    {
        
        while (ptr!=NULL && ptr->product_output!=output)
        {  
            ptr=ptr->next;
            
        }
        if(ptr!=NULL){
             cout<<ptr->id<<" , "<<ptr->Location<<" , "<<ptr-> main_distance<<" , "<<ptr-> stock_level<<" , "<<ptr->product_output<< ", "<<ptr->usage_rate<< ", "<<ptr->fuel_cost<<","<<ptr->capacity<<  endl;
        }
        else{
            cout << "Product output " << output << "  is invalid"<<endl;
        }
    }
    else
    {
       cout << "List is empty"<<endl;
    }
}


void searchByStorageCapacity(int capacity )
{
    Node *ptr = head;
    cout << " ID    Location           main_distance           stock_level    product_output ,     usage_rate,    fuel_cost ,     capacity, " << endl;
    if (head!=NULL)
    {
        
        while (ptr!=NULL && ptr->capacity!=capacity)
        {  
            ptr=ptr->next;
            
        }
        if(ptr!=NULL){
             cout<<ptr->id<<" , "<<ptr->Location<<" , "<<ptr-> main_distance<<" , "<<ptr-> stock_level<<" , "<<ptr->product_output<< ", "<<ptr->usage_rate<< ", "<<ptr->fuel_cost<<","<<ptr->capacity<<  endl;
        }
        else{
            cout << "Storage capacity " << capacity << "  is invalid"<<endl;
        }
    }
    else
    {
       cout << "List is empty"<<endl;
    }
}




int getHashIndex(int stock_level)
{
    return stock_level / TABLE_SIZE;
}

void displayGroups(int index) {
    Node* node= hashTable[index];
    que q1;
    while (node != NULL) {
        q1.enque(node);   
        node= node->next;
    }
    while(!q1.isEmpty()){
    Node* temp = q1.getFront(); 
    cout << "Location: " << temp->Location << ", Stock Level: " << temp->stock_level << endl;
    q1.deque();
    }
}

void inserthashNode(Node* node)
{
    Node* new_node = new Node;
    new_node->id = node->id;
    new_node->Location = node->Location;
    new_node->main_distance = node->main_distance;
    new_node->stock_level = node->stock_level;
    new_node->product_output = node->product_output;
    new_node->usage_rate = node->usage_rate;
    new_node->fuel_cost = node->fuel_cost;
    new_node->capacity = node->capacity;
    new_node->next = NULL;
    
    int index = getHashIndex(new_node->stock_level);

    if (new_node->stock_level == 100) {
        index = 9;
    }

    if (hashTable[index] == NULL)
    {
        hashTable[index] = new_node;
    
    }
    else
    {
        Node* temp = hashTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    
    }
}

void displayHashTable()
 {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Group " << i << ": "<<endl;
        if (hashTable[i] == NULL) {
            cout << "Empty" << endl;
        }
        else {
            displayGroups(i);
        }
    }
}

int retrieveNodesAtIndex(int index)
{
    if (index < 0 || index >= TABLE_SIZE)
    {
        cout << "Invalid index!" << endl;
        return -1;
    }

    Node* temp = hashTable[index];
    int count=0;
    int i = 0;
    while (temp != NULL)
    {
        cout << i<<") Location: " << temp->Location << "\tStock Level: " << temp->stock_level << endl;
        count ++;
        i++;
        temp = temp->next;
    }
    
    return count;
}

void printPath(int parent[], int target, string locations[])
{
    if (parent[target] == -1)
    {
        cout << "[" <<locations[target] <<"]" << "-> ";
        return;
    }

    printPath(parent, parent[target], locations);
    cout << "[" << locations[target] <<"]" << " ->";
    
}

void populateMatrix(int index) {
    Node* temp = hashTable[index];

    int i = 0;
    while (temp != NULL) {
        Node* temp2 = temp->next;
        int j = i+1;

        while (temp2 != NULL) {
           
                cout << endl;
                cout << "Enter the distance between " << temp->Location << " and " << temp2->Location << ": ";
                int a ;
                cin>>a;
                graph[i][j]=a;
                graph[j][i]=a;
            

            temp2 = temp2->next;
            j++;
        }

        temp = temp->next;
        i++;
    }
}

void shortestPath(int index, int source, int V){


	cout<<"---------------------------------------------------------"<<endl;
	cout<<"Enter the edge weights, enter 0 if no edge exists "<<endl;
	cout<<"---------------------------------------------------------"<<endl;

	populateMatrix(index);


    int distances[V];    
    bool visited[V]; 
    int parent[V]; 

    for (int i = 0; i < V; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }

    distances[source] = 0; 
    parent[source] = -1; 

    for (int count = 0; count < V-1 ; count++) {

        int minDist = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && distances[v] < minDist) {
                minDist = distances[v];
                minIndex = v;
            }
        }
        
        visited[minIndex] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[minIndex][v]>0 && distances[minIndex] != INT_MAX &&
                distances[minIndex] + graph[minIndex][v] < distances[v]) {
                distances[v] = distances[minIndex] + graph[minIndex][v];
                parent[v] = minIndex; 
            }
        }
        
    }
    
    cout<<endl;
   	cout<<"---------------------------------------------------------"<<endl; 
    
    string locations[V]; 

    int place = 0;
    Node* t = hashTable[1];
    while (t != NULL) {
        locations[place] = t->Location;
        place++;
        t = t->next;
    }
	 
	string l="";
	Node* temp = hashTable[1];
    int i = 0;
    while (temp != NULL)
    {
    	if (i==source){
      		l= temp->Location;
      	}
        i++;
        temp = temp->next;
    }
    
    for (int i = 1; i < V; i++)
    {
    	cout<<endl;
    	cout<<"---------------------------------------------------------"<<endl; 
        cout << "Shortest distance from "<<" [(source)" << l << "] "<< " to " << locations[i] << " is :" <<endl;
           	cout<<"---------------------------------------------------------"<<endl; 
        cout<<endl;
		cout<< "DISTANCE = "<< distances[i]<<endl; 
        cout << "PATH =  ";
        printPath(parent, i, locations);
        cout <<endl;
    }
}  

int main()
{
    ifstream fin;
    fin.open("Waste_Management_data.csv");
    string line, word;
    vector<string> lineData;
    int lines = 0;
    while(!fin.eof()){
     
        getline(fin,line);
        stringstream s(line);
        while(getline(s,word,',')){
            lineData.push_back(word);
        }

        stringstream s0(lineData[0]);
        int id;
        s0>> id;
        stringstream s1(lineData[2]);
        float distance;
        s1>> distance;
        stringstream s2(lineData[3]);
        int  stock_level;
        s2>> stock_level;
        stringstream s3(lineData[4]);
        int product_output;
        s3>>product_output;
        stringstream s4(lineData[5]);
        int usage_rate;
        s4>>usage_rate;
        stringstream s5(lineData[6]);
        int fuel_cost;
        s5>>fuel_cost;
        stringstream s6(lineData[9]);
        int capacity;
        s6>>capacity;
       
        if(lines!=0)
        {
            addNode(id,lineData[1],distance, stock_level,product_output,usage_rate,fuel_cost,capacity);
        }
     
        lineData.clear();
        lines++;
    }
     
    Node* current = head;
    while (current != NULL) {
        inserthashNode(current);
        current = current->next;
    }
    
    int choice = 0;
    do
    {   
        cout<<""<<endl;
        cout<<"*******************************************************"<<endl;
        cout<<"1) Print information about all Store"<<endl;
        cout<<"2) Print information about 1 Store"<<endl;
        cout<<"3) Display the Stores on basis of Stock Level."<<endl;
        cout<<"4) Display all the Store grouped according to their Stock Level"<<endl;
        cout<<"5) Search a store by product output (kg/day) "<<endl;
        cout<<"6) Search a store by storage capacity (kg) "<<endl;
        cout<<"7) Calculate total Product output (kg/day) of the chain"<<endl;
        cout<<"8) Display all the stores with transportation cost greater than or equal to 1000"<<endl;
        cout<<"9) Get the store with the highest utilization rate in constant time"<<endl;
        cout<<"10) Visit the Store with Stock level < 20 to supply the products."<<endl;
        cout<<""<<endl;
        cout<<"*******************************************************"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1 :
            {
                print();
                break;
            }
            case 2 :
            {
                string station;
                cout<<"\n Enter station name:";
                cin>>station;
                print(station);
                break;
            }
            case 3 :
            {
                int level;
                cout<<"\n Enter Stock Level:"<<endl;
                cout<<"\n Example : Writing a stock level 35 will give you all stores that have stock level between 30-39"<<endl;
                cout<<endl;
                cin>>level;
            	if (level<0){
            		cout<<"Invalid Stock Level ."<<endl;
				}
				else if (level>= 0 && level<10){
					cout<<"No Store is having this Stock Level ."<<endl;
				}
				else if (level>=10 && level<20){
					int count = retrieveNodesAtIndex(1);
					cout<<endl;
					cout<<count<<" Store have this Stock Level"<<endl;
				}
				else if (level>=20 && level<30){
					int count = retrieveNodesAtIndex(2);
					cout<<endl;
					cout<<count<<" Store have this Stock Level"<<endl;
				}
				else if (level>=30 && level<40){
					int count = retrieveNodesAtIndex(3);
					cout<<count<<" Store have this Stock Level"<<endl;
				}
				else if (level>=40 && level<50){
					int count = retrieveNodesAtIndex(4);
					cout<<endl;
					cout<<count<<" Store have this Stock Level"<<endl;
				}
				else if (level>=50 && level<60){
					int count = retrieveNodesAtIndex(5);
					cout<<count<<" Store have this Stock Level"<<endl;
				}
				else if (level>=60 && level<70){
					int count = retrieveNodesAtIndex(6);
					cout<<endl;
					cout<<count<<" Store have this Stock Level"<<endl;
				}
				else if (level>=70 && level<80){
					int count = retrieveNodesAtIndex(7);
					cout<<endl;
					cout<<count<<" Store have this Stock Level"<<endl;
				}
				else if (level>=80 && level<90){
					int count = retrieveNodesAtIndex(8);
					cout<<endl;
					cout<<count<<" Store have this Stock Level"<<endl;
				}
				else if (level>=90 && level<=100){
					int count = retrieveNodesAtIndex(9);
					cout<<endl;
					cout<<count<<" Store have this Stock Level"<<endl;
				}
                break;
            }
            case 4 :
            {
                displayHashTable();
                break;
            }
            case 5 :
            {
                int output;
                cout<<"Enter product output (kg/day) of the store to search"<<endl;
                cin>>output;
                searchByProductOutput(output );
                break;
            }
            case 6 :
            {
                int capacity;
                cout<<"Enter storage capacity (kg) of the store to search"<<endl;
                cin>>capacity;
                searchByStorageCapacity(capacity);
                break;
            }
            case 7 :
            {
                calculateProductOutputOfChain();
                break;
            }
            case 8 :
            {
                transportationCostGreaterThan1000();
                break;
            }
            case 9 :
            {
                highestUtilizationRate();
                break;
            }
            case 10 :
            {
            	cout<<"---------------------------------------------------------"<<endl;	
				cout<<" STORES TO BE VISITED FOR ADDING  ARE : "<<endl;
				cout<<"---------------------------------------------------------"<<endl;
				int V= retrieveNodesAtIndex(1);
				cout<<"---------------------------------------------------------"<<endl;
				cout<<"Enter the source as numeric value , from where you want to start the Ride  (starting point):"<<endl;
				int source ;
				cin>>source;
                shortestPath(1,source,V );
                break;
            }
            default :
            {
                cout<<"Invalid choice!"<<endl;
            }
        }
    }
    while(choice!=0);
    return 0;
}