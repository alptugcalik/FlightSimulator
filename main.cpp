#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>

#define CITYNUMBER 20
#define MAXQUEUESIZE 190 // MAX FLIGHT NUMBER
#define MONTHLY_CITY 5 //NUMBER OF MOUNTLY ADDED CITIES
#define LOW_OCCUPANCY 70

int MONTH=1; // global variable for month


using namespace std;

string cities[CITYNUMBER];

class CityGraph{
private:
    int numCity,numRoute; // number of edges and vertices
    int **routeFares; // fare/route matrix
    int *mark;// array for memorizing visits
public:
    CityGraph(); //constructor
    ~CityGraph(); //destructor
    void addGRoute(int v1,int v2); // add route from v1 to v2
    void addGRoute(string v1,string v2); // add route from v1 to v2 (using names)
    void removeGRoute(int v1, int v2); // remove route from v1 to v2
    void removeGRoute(string v1, string v2); // remove route from v1 to v2 (using names)
    int** getRouteFares() const; // get the fare matrix
    void setRouteFares(int v1,int v2, int fare);
    void printRouteMap() const;
    void setTicketPrices(int v1,int v2,int cash); // set the price
    int getTicketPrices(int v1,int v2) const; // get the price
    // set and get mark
    void setMark(int i);
    int getMark(int i) const;
    // get num city
    int getCityNumber() const;
    void clearAllMarks(); // method to clear marks

    // !!!!!!!!! IMPORTANT NOTES !!!!!!!!!

    // no need to implement addGCity method since all cities are stored at the cities array, first
    // this array is a global string array, and filled in main function
    // as the same reason for addGcity, no need to use removeGCity
    // only removing/adding routes are enough for the purpose of this program.

    // since the string array containing the citynames is a global array;
    // searchGCity method is not implemented. This array is used when a city name is needed.

    // searchGRoute method is not implemented. Instead, when a route is needed,
    // routeFares matrix is used/passed for each need in the corresponding place in other functions

};

//constructor
CityGraph::CityGraph(){
    numCity = CITYNUMBER; //assign city amount
    numRoute = 0; // no routes initally
    for(int i=0;i<CITYNUMBER;i++) cities[i] = cities[i]; // assign each name
    mark = new int [CITYNUMBER](); // allocation
    for(int i=0;i<CITYNUMBER;i++) mark[i] =0; // make UNVISITED all
    routeFares = new int*[CITYNUMBER]; // allocate memory for routes/fares
    for(int i=0;i<CITYNUMBER;i++)
        routeFares[i] = new int [CITYNUMBER];
    for(int i=0;i<CITYNUMBER;i++) // initialize routes/fares to zero
        for(int j=0;j<CITYNUMBER;j++)
            routeFares[i][j] = 0;
}

//deconstructor
CityGraph::~CityGraph(){
    delete [] mark;
    for(int i=0;i<CITYNUMBER;i++)
        delete[] routeFares[i];
    delete [] routeFares;
}

// set/get mark
void CityGraph::setMark(int i){
    mark[i] = 1; // make visited
}
int CityGraph::getMark(int i) const{
    return mark[i];
}

// clear marks
void CityGraph::clearAllMarks(){
    for(int j =0;j<numCity;j++)
        mark[j] =0;
}


// get city number
int CityGraph::getCityNumber() const{
    return numCity;
}
// newfares
void CityGraph::setRouteFares(int v1,int v2,int fare){
    routeFares[v1][v2]=fare;
}

// get the fare matrix
int** CityGraph::getRouteFares() const{
    return routeFares;
}

// add route by integer indices
void CityGraph::addGRoute(int v1,int v2){
    if(routeFares[v1][v2]==0){
    routeFares[v1][v2] = (rand()%100)+1; // assigns a random fare btw 1 and 100
    numRoute++;
    }
    else{
        cerr<<"Route exists!"<<endl;
    }
}

// add route by city names
void CityGraph::addGRoute(string v1,string v2){
    int i,j;
    for(i=0;i<CITYNUMBER;i++) // find the index of city 1
        if(v1.compare(cities[i])==0) break;
    for(j=0;j<CITYNUMBER;j++) // find the index of city 2
        if(v2.compare(cities[j])==0) break;
    if(routeFares[i][j]==0){
    routeFares[i][j] = (rand()%90) +10; // assigns a random fare btw 10 and 100
    numRoute++;
    }
    else{
        cerr<<"Route exists!"<<endl;
    }

}

 // remove route from v1 to v2
void CityGraph::removeGRoute(int v1, int v2){
    if(routeFares[v1][v2]!=0){
    routeFares[v1][v2] = 0; // assign route to 0
    numRoute--;
    }
    else return;
}

 // remove route by city names
void CityGraph::removeGRoute(string v1,string v2){
    int i,j;
    for(i=0;i<CITYNUMBER;i++) // find the index of city 1
        if(v1.compare(cities[i])==0) break;
    for(j=0;j<CITYNUMBER;j++) // find the index of city 2
        if(v2.compare(cities[j])==0) break;
    if(routeFares[i][j]!=0){
        routeFares[i][j] = 0; // assign route to 0
        numRoute--;
    }
     else return;
}

 // print the routes
void CityGraph::printRouteMap() const{
    cout<<endl;
    cout<<"Current Routes:"<<endl;
    for(int i=0;i<CITYNUMBER;i++){
        for(int j=0;j<CITYNUMBER;j++)
            {
                //check for the existing routes
                if(routeFares[i][j]!=0) cout<<"("<<cities[i]<<"--->"<<cities[j]<<","<<routeFares[i][j]<<")"<<endl;
            }
    }
}

 // set ticket price
 void CityGraph::setTicketPrices(int v1,int v2,int cash){
     routeFares[v1][v2] = cash;
 }

 // get ticket price
 int CityGraph::getTicketPrices(int v1,int v2) const{
     return routeFares[v1][v2];
 }

 // initializer for route map
CityGraph InitRouteMap(){
    CityGraph cityGraph; // construct the graph
    // add routes according to the specified map in pdf
    cityGraph.addGRoute("Probia","Las Datas");
    cityGraph.addGRoute("Signale","Probia");
    cityGraph.addGRoute("Probia","Gulf of Archi");
    cityGraph.addGRoute("Probia","Logicheim");
    cityGraph.addGRoute("Logicheim","Probia");
    cityGraph.addGRoute("Gulf of Archi","Logicheim");

    return cityGraph;
}

// class for a flight node
class FlightNode{
private:
    FlightNode* left;
    FlightNode* right;
    int occupancy; // occ of current month
    int occupancy2; // occ of past month
public:
    FlightNode(int depCity=-1,int arvCity=-1,FlightNode* leftNode = nullptr, FlightNode* rightNode = nullptr,int occ = rand()%99); // constructor with occ
    int departureCity; // in order to keep departure city of a flight
    int arrivalCity; // in order to keep arrival city of a flight
    int key;
    void setOccupancyRate(int occ); // set occupancy rates
    int getOccupancyRate() const; // get occupancy rates
     void setOccupancyRate2(int occ); // set occupancy rates
    int getOccupancyRate2() const; // get occupancy rates
    FlightNode* getLeft() const;
    FlightNode* getRight() const;
    void setKey(int newKey);
    void setLeft(FlightNode* newLeft);
    void setRight(FlightNode* newRight);
};

// another constructor
FlightNode::FlightNode(int depCity,int arvCity,FlightNode* leftNode, FlightNode* rightNode, int occ ){
    departureCity = depCity;
    arrivalCity = arvCity;
    key = 100*depCity + arvCity;
    left = leftNode;
    right = rightNode;
    occupancy = occ;
    occupancy2 = 100;
}
// set key
void FlightNode::setKey(int newKey){
    key = newKey;
}
// set occupancy
void FlightNode::setOccupancyRate(int occ){
        occupancy = occ; // random number btw 0 and 99
}

// get occupancy
int FlightNode::getOccupancyRate() const{
        return occupancy;
}

// set occupancy2
void FlightNode::setOccupancyRate2(int occ){
        occupancy2 = occ; // random number btw 0 and 99
}

// get occupancy2
int FlightNode::getOccupancyRate2() const{
        return occupancy2;
}

FlightNode* FlightNode::getLeft() const{
    return left;
}

FlightNode* FlightNode::getRight() const{
    return right;
}

void FlightNode::setLeft(FlightNode* newLeft) {
    left = newLeft;
}

void FlightNode::setRight(FlightNode* newRight) {
    right = newRight;
}

// queue class
template <class T>
class Queue{
private:
    int front,rear,count;
    T Qlist[MAXQUEUESIZE];
public:
    Queue(); // initialize the data members
    T getFront() const; // get the front of the queue
    void push(T newMember); // push a new member
    T pop(); // pop a member
    bool isEmpty() const;
};

// constructor
template <class T>
Queue<T>::Queue(){
     front = 0;
     count = 0;
     rear = 0;
}

// get front
template <class T>
T Queue<T>::getFront() const{
    return Qlist[front];
}

// push new member
template <class T>
void Queue<T>::push(T newMember){
    if(count == MAXQUEUESIZE) {
            cerr<< "queue overflow!!!";
            return;
    }
    count++;
    Qlist[rear] =newMember;
    rear = (rear + 1) % MAXQUEUESIZE;
}

// pop a member
template <class T>
T Queue<T>::pop(){
    T temp;
    if(count == 0) {
            cerr<< "deleting from an empty queue!!!";
            return NULL;
    }
    temp = Qlist[front];
    count--;
    front = (front + 1) % MAXQUEUESIZE;
    return temp;
}

// is empty
template <class T>
bool Queue<T>::isEmpty() const{
    return (count==0);
}


// a binary tree class for flights
class FlightTree{
private:
    FlightNode* root;
public:
    FlightTree(FlightNode* newRoot=nullptr); //constructor
    FlightNode* addTFlight(int v1,int v2); // add a flight and return the root of the tree
    FlightNode* addTFlight(string v1,string v2); // add a flight and return the root of the tree by city names
    FlightNode* addTFlight(int v1,int v2,int occ); // add a flight and return the root of the tree with occ
    FlightNode* removeTFlight(int key); // remove a flight and return the root of the tree
    void printFlights() const;
    FlightNode* getRoot() const;
    void setRoot(FlightNode* Root);
    void printFlightNumber(int depCity,int arvCity) const; // search and print the related flight
};


//constructor
FlightTree::FlightTree(FlightNode* newRoot){
    root = newRoot;
}

//get root
FlightNode* FlightTree::getRoot() const{
    return root;
}

//set root
void FlightTree::setRoot(FlightNode* Root){
    root=Root;
}

// add a flight
FlightNode* FlightTree::addTFlight(int depCity,int arvCity){
    int key=depCity*100+arvCity;
    bool control=false;
    FlightNode *temp=root, *temp2=temp;
    if(root== nullptr){
        root=new FlightNode(depCity,arvCity);
    }
    else{
        while (temp!= nullptr){
            if (key<temp->key) {
                temp2=temp;
                temp = temp->getLeft();
                control=false;
            }
            else if(key>temp->key) {
                temp2=temp;
                temp = temp->getRight();
                control=true;
            }
            else{
                cout<<"Flight exists!!"<<endl;
                return nullptr;
            }
        }
        if(control){
                temp2->setRight(new FlightNode(depCity, arvCity));
        }
        else{
                temp2->setLeft(new FlightNode(depCity, arvCity));

        }
    }
    return root;
}

// add a flight with city names
FlightNode* FlightTree::addTFlight(string v1,string v2){
    int depCity,arvCity;
    for(int i=0;i<CITYNUMBER;i++){
        if(v1.compare(cities[i])==0){
            depCity = i;
            break;
        }
    }
    for(int i=0;i<CITYNUMBER;i++){
        if(v2.compare(cities[i])==0){
            arvCity = i;
            break;
        }
    }
    int key=depCity*100+arvCity;
    bool control=false;
    FlightNode *temp=root, *temp2=temp;
    if(root== nullptr){
        root=new FlightNode(depCity,arvCity);
    }
    else{
        while (temp!= nullptr){
            if (key<temp->key) {
                temp2=temp;
                temp = temp->getLeft();
                control=false;
            }
            else if(key>temp->key) {
                temp2=temp;
                temp = temp->getRight();
                control=true;
            }
            else{
                cout<<"Flight exists!!"<<endl;
                return nullptr;
            }
        }
        if(control){
                temp2->setRight(new FlightNode(depCity, arvCity));
        }
        else{
                temp2->setLeft(new FlightNode(depCity, arvCity));

        }
    }
    return root;
}

// add a flight with occupancy
FlightNode* FlightTree::addTFlight(int depCity,int arvCity,int occ){
    int key=depCity*100+arvCity;
    bool control=false;
    FlightNode *temp=root, *temp2=temp;
    if(root== nullptr){
        root=new FlightNode(depCity,arvCity,nullptr,nullptr,occ);
    }
    else{
        while (temp!= nullptr){
            if (key<temp->key) {
                temp2=temp;
                temp = temp->getLeft();
                control=false;
            }
            else if(key>temp->key) {
                temp2=temp;
                temp = temp->getRight();
                control=true;
            }
            else{
                cout<<"Flight exists!!"<<endl;
                return nullptr;
            }
        }
        if(control){
                temp2->setRight(new FlightNode(depCity, arvCity, nullptr, nullptr,occ));
        }
        else{
                temp2->setLeft(new FlightNode(depCity, arvCity, nullptr, nullptr,occ));

        }
    }
    return root;
}
// helper for 1 flight print
void helperPrintOne(FlightNode* Root, int depCity,int arvCity){
    int depart,arvv;
    if(Root==nullptr) return;
    else{
        helperPrintOne(Root->getLeft(),depCity,arvCity);
        depart = Root->departureCity;
        arvv = Root->arrivalCity;
        if(depart == depCity && arvv == arvCity){
            if(depart>8 && arvv>8){
                cout<<"EE"<<depart+1<<arvv+1;
            }
            else if(depart<=8 && arvv>8){
                cout<<"EE0"<<depart+1<<arvv+1;
            }
            else if(depart>8 && arvv<=8){
                cout<<"EE"<<depart+1<<"0"<<arvv+1;
            }
            else if(depart<=8 && arvv<=8){
                cout<<"EE0"<<depart+1<<"0"<<arvv+1;
            }

            return;
        }
        helperPrintOne(Root->getRight(),depCity,arvCity);
    }
}
// print 1 flight
void FlightTree::printFlightNumber(int depCity,int arvCity) const{
    helperPrintOne(root,depCity,arvCity); // pass the root an parameters
}

// print helper
void helperPrint(FlightNode* Root){
    int depart,arvv;
    if(Root==nullptr) return;
    else{
        helperPrint(Root->getLeft());
        depart = Root->departureCity;
        arvv = Root->arrivalCity;
        if(depart>8 && arvv>8){
            cout<<"EE"<<depart+1<<arvv+1<<": ";
        }
        else if(depart<=8 && arvv>8){
            cout<<"EE0"<<depart+1<<arvv+1<<": ";
        }
        else if(depart>8 && arvv<=8){
            cout<<"EE"<<depart+1<<"0"<<arvv+1<<": ";
        }
        else if(depart<=8 && arvv<=8){
            cout<<"EE0"<<depart+1<<"0"<<arvv+1<<": ";
        }
        cout<<cities[depart]<<"->"<<cities[arvv]<<endl;
        helperPrint(Root->getRight());
    }
}

//print flights
void FlightTree::printFlights() const{
    if(root == nullptr) {
            cerr<<"Cannot print an empty flight plan!!";
            return;
    }
    else {
            cout<<endl;
            cout<<"Current Flights:"<<endl;
            helperPrint(root);
    }
}



// helper functions for node deletion
// find min valued node in a sub tree
FlightNode* findMinKey(FlightNode* curr)
{
    while (curr->getLeft() != nullptr) {
        curr = curr->getLeft();
    }
    return curr;
}

// helper function for find the key and its parent
void findKey(FlightNode* &root, int key, FlightNode* &parent)
{
    FlightNode* temp = root, *temp2 = root;
    if(root == nullptr) {
            cerr<<"Root is empty! Cannot find a key!";
            return;
    }
    while (temp!= nullptr){
            if (key<temp->key) {
                temp2=temp;
                temp = temp->getLeft();
            }
            else if(key>temp->key) {
                temp2=temp;
                temp = temp->getRight();
            }
            else if(key == temp->key) break;
        }
    root = temp;
    parent = temp2;
}

// Function to delete flight node
void deleteFlight(FlightNode*& root, int& key)
{

    FlightNode* parent = nullptr;
    FlightNode* curr = root;

    findKey(curr, key, parent);

    // return if key is not found in the tree
    if (curr == nullptr)
        return;

    // a leaf node
    if (curr->getLeft() == nullptr && curr->getRight() == nullptr)
    {
        // if  not root
        if (curr != root)
        {
            if (parent->getLeft() == curr)   parent->setLeft(nullptr);
            else                             parent->setRight(nullptr);
        }
        // if only root exists
        else                                   root = nullptr;

        free(curr);
        return;
    }

    // has 2 child node
    else if (curr->getLeft() && curr->getRight())
    {
        FlightNode* successor  = findMinKey(curr->getRight());
        int val = successor->key;
        int occ = successor->getOccupancyRate();
        int arv = successor->arrivalCity;
        int dep = successor->departureCity;

        deleteFlight(root, successor->key);
        curr->setKey(val);
        curr->setOccupancyRate(occ);
        curr->arrivalCity = arv ;
        curr->departureCity = dep;
    }

    // one child
    else
    {
        FlightNode* child = (curr->getLeft())? curr->getLeft(): curr->getRight();
        if (curr != root)
        {
            if (curr == parent->getLeft())         parent->setLeft(child);
            else                                   parent->setRight(child);
        }
        else                                         root = child;
        free(curr);
        return;
    }

}

// remove a flight
FlightNode* FlightTree::removeTFlight(int key){
    deleteFlight(root,key); // delete the flight
    // print the cancellation info
    return root;
}

//initializer for flight tree
FlightTree InitFlightPlan(const CityGraph& cityGraph){
    FlightTree flightTree;
    int** fares = cityGraph.getRouteFares();
    for(int i=0;i<CITYNUMBER;i++){
        for(int j=0;j<CITYNUMBER;j++)
            {
                //check for the existing routes
                if(fares[i][j]!=0) flightTree.addTFlight(i,j);
            }
    }

    return flightTree;
}

 // add monthly new flights
void AddMonthlyNewFlights(FlightTree& flightTree, int newFlights[20][20]){
    //UPDATE message and print the new flights
    int depCity,arvCity;
    cout<<endl;
    cout<<"Monthly New Flight Offers"<<endl;
    for(int i=0;i<CITYNUMBER;i++){
        for(int j=0;j<CITYNUMBER;j++){
            if(newFlights[i][j]==99){
                    flightTree.addTFlight(i,j,100); // add a new flight with occ 100
                    depCity=i;
                    arvCity=j;
                    cout<<"Flight ";
                    if(depCity>8 && arvCity>8){
                    cout<<"EE"<<depCity+1<<arvCity+1;
                    }
                    else if(depCity<=8 && arvCity>8){
                    cout<<"EE0"<<depCity+1<<arvCity+1;
                    }
                    else if(depCity>8 && arvCity<=8){
                    cout<<"EE"<<depCity+1<<"0"<<arvCity+1;
                    }
                    else if(depCity<=8 && arvCity<=8){
                    cout<<"EE0"<<depCity+1<<"0"<<arvCity+1;
                    }
                    cout<<" Added"<<endl;
            }
        }
    }
}

 // add monthly new routes
void AddMonthlyNewRoutes(int N,CityGraph& cityGraph,FlightTree& flightTree){
    int count =0; // count for added routes
    int i,j;
    int newFlights[20][20] ;
    for(int i=0;i<CITYNUMBER;i++)
        for(int j=0;j<CITYNUMBER;j++)
            newFlights[i][j]=0;
    int** fares = cityGraph.getRouteFares();
    MONTH++;
    cout<<"--------------------------MONTH "<<MONTH<<"--------------------------"<<endl;
    cout<<"Monthly New Route Offers"<<endl;
    while(true){
        i = rand()%20; // random number btw 0 and 19
        j = rand()%20; // random number btw 0 and 19
        if(fares[i][j]==0 && i!=j) { // check for existing routes and routes from/to the same city
            cityGraph.addGRoute(i,j);
            // in order to add the flights in the same order, flights are added here
            newFlights[i][j] = 99; // mark new flights
            count++;
            cout<<"("<<cities[i]<<"--->"<<cities[j]<<","<<fares[i][j]<<")";
            cout<<" Route Added"<<endl;
        }
        if(count==N) break;
    }
    cout<<endl;
    // call for update flights
    AddMonthlyNewFlights(flightTree,newFlights);
}

//DISCARD UNPOPULAR ROUTES AND UPDATE PRICES
void discardAndUpdateRoutes(CityGraph& cityGraph,int unpop[20][20]){
    int price;
    cout<<endl;
    cout<<"Discarded Routes & Routes on Discount"<<endl;
    for(int i=0;i<CITYNUMBER;i++){
        for(int j=0;j<CITYNUMBER;j++){
            if(unpop[i][j] == 50){
                price = cityGraph.getTicketPrices(i,j);
                // if the fare is 1 dont half the price
                if(price == 1) price = price*2;
                cityGraph.setTicketPrices(i,j,price/2);
                cout<<"("<<cities[i]<<"--->"<<cities[j]<<","<<cityGraph.getTicketPrices(i,j)<<") is 50% off"<<endl;
            }
            else if(unpop[i][j]==100){
                cityGraph.removeGRoute(i,j);
                cout<<"("<<cities[i]<<"--->"<<cities[j]<<") Route Discarded"<<endl; // discard
            }
            else if(unpop[i][j]==20){
                price = cityGraph.getTicketPrices(i,j);
                cityGraph.setTicketPrices(i,j,price*2); // double the price again

            }
        }
    }
}


//CANCEL UNPOPULAR FLIGHTS
void cancelUnpopularFlights(FlightTree& flightTree,CityGraph& cityGraph){
    Queue<FlightNode*> Q;
    FlightNode* p;
    Q.push(flightTree.getRoot());
    // search tree and find flights with low occupancies
    int depart,arvv,key;
    int newOcc,occ,occ2;
    int unpopular [20][20];
    // initialize
    for(int i=0;i<CITYNUMBER;i++)
        for(int j=0;j<CITYNUMBER;j++)
            unpopular[i][j] = 0;
    cout<<endl;
    cout<<"Cancelled Flights"<<endl;
    while(!Q.isEmpty()){
        p = Q.pop();
        depart = p->departureCity;
        arvv = p->arrivalCity;
        occ = p->getOccupancyRate();
        occ2 = p->getOccupancyRate2();
        // get new occupancy
        newOcc = rand()%100;
        // 2 months low occupancy
        // discard
        if(occ2 < LOW_OCCUPANCY && occ < LOW_OCCUPANCY) {
            unpopular[depart][arvv] = 100;
        }
        // last month low occupancy
        // half the ticket price
        else if(occ < LOW_OCCUPANCY && occ2 > LOW_OCCUPANCY){
            unpopular[depart][arvv] = 50;
        }
        // double the price if occupancy is high (previous occ is low)
        else if(occ > LOW_OCCUPANCY && occ2 < LOW_OCCUPANCY){
            unpopular[depart][arvv] = 20;
        }
        p->setOccupancyRate2(occ);
        p->setOccupancyRate(newOcc);
        if(p->getLeft()!= nullptr) Q.push(p->getLeft());
        if(p->getRight()!= nullptr) Q.push(p->getRight());

    }
    for(int i=0;i<CITYNUMBER;i++)
        for(int j=0;j<CITYNUMBER;j++)
            if(unpopular[i][j] == 100){
                    key = 100*i+j;
                    depart = i;
                    arvv = j;
                    flightTree.removeTFlight(key);
                    cout<<"Flight ";
                    if(depart>8 && arvv>8){
                        cout<<"EE"<<depart+1<<arvv+1;
                    }
                    else if(depart<=8 && arvv>8){
                        cout<<"EE0"<<depart+1<<arvv+1;
                    }
                    else if(depart>8 && arvv<=8){
                        cout<<"EE"<<depart+1<<"0"<<arvv+1;
                    }
                    else if(depart<=8 && arvv<=8){
                        cout<<"EE0"<<depart+1<<"0"<<arvv+1;
                    }
                    cout<<" Cancelled"<<endl;
            }
    discardAndUpdateRoutes(cityGraph,unpopular);
}

// add return flights
void addReturnFlights(FlightTree& flightTree,int noFlight[20][20]){
    int depart,arvv;
    cout<<endl;
    cout<<"Missing Return Flights"<<endl;
    for(int i=0;i<CITYNUMBER;i++)
        for(int j=0;j<CITYNUMBER;j++){
            if(noFlight[i][j]==1){
                flightTree.addTFlight(i,j,100); // occupancy is 100 in order not to delete at first month
                depart =i;
                arvv =j;
                cout<<"Flight ";
                if(depart>8 && arvv>8){
                    cout<<"EE"<<depart+1<<arvv+1;
                }
                else if(depart<=8 && arvv>8){
                    cout<<"EE0"<<depart+1<<arvv+1;
                }
                else if(depart>8 && arvv<=8){
                    cout<<"EE"<<depart+1<<"0"<<arvv+1;
                }
                else if(depart<=8 && arvv<=8){
                    cout<<"EE0"<<depart+1<<"0"<<arvv+1;
                }
                cout<<" Added"<<endl;
            }
        }


}

// check for return routes
void checkNAddReturnRoutes(CityGraph& cityGraph,FlightTree& flightTree){
    int** currentFares = cityGraph.getRouteFares();
    int noRoute [20][20];
    // initialize
    for(int i=0;i<CITYNUMBER;i++)
        for(int j=0;j<CITYNUMBER;j++)
            noRoute[i][j] = 0;
    cout<<endl;
    cout<<"-------------- CHECK FOR RETURN ROUTES ------------------"<<endl;
    cout<<"Missing Return Routes"<<endl;
    for(int i=0;i<CITYNUMBER;i++)
        for(int j=0;j<CITYNUMBER;j++){
            if(i == j) continue; // pass for i=j
            if(currentFares[i][j] != 0 && currentFares[j][i] == 0 ){
                    cityGraph.addGRoute(j,i);
                    noRoute[j][i] = 1;
                    cout<<"("<<cities[j]<<"--->"<<cities[i]<<","<<cityGraph.getRouteFares()[j][i]<<") Return Route Added"<<endl;
            }
            else if(currentFares[i][j] == 0 && currentFares[j][i] != 0 ){
                    cityGraph.addGRoute(i,j);
                    noRoute[i][j] = 1;
                    cout<<"("<<cities[i]<<"--->"<<cities[j]<<","<<cityGraph.getRouteFares()[i][j]<<") Return Route Added"<<endl;
            }
            // return routes are added
            // if added, noRoutes[i][j]=1
        }
    addReturnFlights(flightTree,noRoute);
}

// display route options (by int values)
bool displayRootOptions(FlightTree& flightTree, CityGraph& cityGraph, int depCity, int arvCity){
    int count =0;
    cout<<endl;
    cout<<"One-way Trip Options for "<<cities[depCity]<<" ---> "<<cities[arvCity]<<" :"<<endl;


    // direct option
    if(cityGraph.getRouteFares()[depCity][arvCity]!=0) {
        cout<< "Direct Option: "<<cities[depCity]<<" ---> ";
        flightTree.printFlightNumber(depCity,arvCity);
        cout<<" ---> " <<cities[arvCity]<<" for "<<cityGraph.getRouteFares()[depCity][arvCity]<<endl;
        count++;
    }
    // 1-stop option
    for(int i=0;i<cityGraph.getCityNumber();i++){
        if(i == arvCity) continue; // pass the direct option
        if(cityGraph.getRouteFares()[depCity][i]!=0){
            if(cityGraph.getRouteFares()[i][arvCity]!=0){
                int price1,price2;
                price1 = cityGraph.getRouteFares()[depCity][i];
                price2 = cityGraph.getRouteFares()[i][arvCity];
                cout<< "1-Stop Option: "<<cities[depCity]<<" ---> ";
                flightTree.printFlightNumber(depCity,i);
                cout<<" ---> " <<cities[i]<<" ---> ";
                flightTree.printFlightNumber(i,arvCity);
                cout<<" ---> " <<cities[arvCity]<<" for "<<price1<<"+"<<price2<<endl;
                count++;
            }
        }
    }
    // 2-stop option
    for(int i=0;i<cityGraph.getCityNumber();i++){
        if(i == arvCity) continue; // pass the direct option
        if(cityGraph.getRouteFares()[depCity][i]!=0){
            for(int j=0;j<cityGraph.getCityNumber();j++){
                if(j == arvCity) continue; // pass the 1-stop option
                if(cityGraph.getRouteFares()[i][j]!=0){
                    if(cityGraph.getRouteFares()[j][arvCity]!=0){
                        int price1,price2,price3;
                        price1 = cityGraph.getRouteFares()[depCity][i];
                        price2 = cityGraph.getRouteFares()[i][j];
                        price3 = cityGraph.getRouteFares()[j][arvCity];
                        cout<< "2-Stop Option: "<<cities[depCity]<<" ---> ";
                        flightTree.printFlightNumber(depCity,i);
                        cout<<" ---> " <<cities[i]<<" ---> ";
                        flightTree.printFlightNumber(i,j);
                        cout<<" ---> " <<cities[j]<<" ---> ";
                        flightTree.printFlightNumber(j,arvCity);
                        cout<<" ---> " <<cities[arvCity]<<" for "<<price1<<"+"<<price2<<"+"<<price3<<endl;
                        count++;
                    }
                }
            }
        }
    }

    // clear the marks
    cityGraph.clearAllMarks();

    // check if there is no trip option by count
    if(count==0){
        cout<<"No Trip Options"<<endl;
        return false;
    }

    return true;
}


// display route options (by string values)
bool displayRootOptions(FlightTree& flightTree, CityGraph& cityGraph, string depCityS, string arvCityS){
    int depCity,arvCity,count =0;
    // find city numbers
    for(int i=0;i<cityGraph.getCityNumber();i++){
        if(depCityS.compare(cities[i])==0){
            depCity = i;
            break;
        }
    }
    for(int i=0;i<cityGraph.getCityNumber();i++){
        if(arvCityS.compare(cities[i])==0){
            arvCity = i;
            break;
        }
    }

    cout<<endl;
    cout<<"One-way Trip Options for "<<cities[depCity]<<" ---> "<<cities[arvCity]<<" :"<<endl;


    // direct option
    if(cityGraph.getRouteFares()[depCity][arvCity]!=0) {
        cout<< "Direct Option: "<<cities[depCity]<<" ---> ";
        flightTree.printFlightNumber(depCity,arvCity);
        cout<<" ---> " <<cities[arvCity]<<" for "<<cityGraph.getRouteFares()[depCity][arvCity]<<endl;
        count++;
    }
    // 1-stop option
    for(int i=0;i<cityGraph.getCityNumber();i++){
        if(i == arvCity) continue; // pass the direct option
        if(i == depCity) continue; // pass the current city
        if(cityGraph.getRouteFares()[depCity][i]!=0){
            if(cityGraph.getRouteFares()[i][arvCity]!=0){
                int price1,price2;
                price1 = cityGraph.getRouteFares()[depCity][i];
                price2 = cityGraph.getRouteFares()[i][arvCity];
                cout<< "1-Stop Option: "<<cities[depCity]<<" ---> ";
                flightTree.printFlightNumber(depCity,i);
                cout<<" ---> " <<cities[i]<<" ---> ";
                flightTree.printFlightNumber(i,arvCity);
                cout<<" ---> " <<cities[arvCity]<<" for "<<price1<<"+"<<price2<<endl;
                count++;
            }
        }
    }
    // 2-stop option
    for(int i=0;i<cityGraph.getCityNumber();i++){
        if(i == arvCity) continue; // pass the direct option
        if(i == depCity) continue; // pass the current city
        if(cityGraph.getRouteFares()[depCity][i]!=0){
            for(int j=0;j<cityGraph.getCityNumber();j++){
                if(j == arvCity) continue; // pass the 1-stop option
                if(j == depCity) continue; // pass the current city
                if(cityGraph.getRouteFares()[i][j]!=0){
                    if(cityGraph.getRouteFares()[j][arvCity]!=0){
                        int price1,price2,price3;
                        price1 = cityGraph.getRouteFares()[depCity][i];
                        price2 = cityGraph.getRouteFares()[i][j];
                        price3 = cityGraph.getRouteFares()[j][arvCity];
                        cout<< "2-Stop Option: "<<cities[depCity]<<" ---> ";
                        flightTree.printFlightNumber(depCity,i);
                        cout<<" ---> " <<cities[i]<<" ---> ";
                        flightTree.printFlightNumber(i,j);
                        cout<<" ---> " <<cities[j]<<" ---> ";
                        flightTree.printFlightNumber(j,arvCity);
                        cout<<" ---> " <<cities[arvCity]<<" for "<<price1<<"+"<<price2<<"+"<<price3<<endl;
                        count++;
                    }
                }
            }
        }
    }

    // check if there is no trip option by count
    if(count==0){
        cout<<"No Trip Options"<<endl;
        return false;
    }

    return true;
}

int main()
{
    string line;
    string city[20];
    ifstream myfile("citylist.txt");
    if (myfile.is_open())
    {
    int i=0;
    while ( getline (myfile,line) )
    {
    cities[i]=line;
    cout << cities[i] << '\n';
    i++;
    }
    myfile.close();
    }
    else cout << "Unable to open file";
    cout<<endl;
    cout<<endl;
    cout<<"FLIGHT RADAR IS STARTING..."<<endl;
    cout<<"--------------------------MONTH "<<MONTH<<"--------------------------"<<endl;

    CityGraph cityGraph = InitRouteMap();
    FlightTree flightTree = InitFlightPlan(cityGraph);
    // it is desired that by implementing cancel unpopular flights, at the beginning of each month,
    // the unpopular flights will be cancelled
   // month 1
   // only construct
    cityGraph.printRouteMap();
    flightTree.printFlights();
    // month 2
    // only add new ones
    AddMonthlyNewRoutes(MONTHLY_CITY,cityGraph,flightTree); // calls nestedly add monthly new flights
    cancelUnpopularFlights(flightTree,cityGraph); // calls nestedly discard unpopular routes*/
    cityGraph.printRouteMap();
    flightTree.printFlights();
    // month 3
    AddMonthlyNewRoutes(MONTHLY_CITY,cityGraph,flightTree); // calls nestedly add monthly new flights
    cancelUnpopularFlights(flightTree,cityGraph); // calls nestedly discard unpopular routes*/
    cityGraph.printRouteMap();
    flightTree.printFlights();
    // month 4
    AddMonthlyNewRoutes(MONTHLY_CITY,cityGraph,flightTree); // calls nestedly add monthly new flights
    cancelUnpopularFlights(flightTree,cityGraph); // calls nestedly discard unpopular routes*/
    cityGraph.printRouteMap();
    flightTree.printFlights();
    // month 5
    AddMonthlyNewRoutes(MONTHLY_CITY,cityGraph,flightTree); // calls nestedly add monthly new flights
    cancelUnpopularFlights(flightTree,cityGraph); // calls nestedly discard unpopular routes*/
    cityGraph.printRouteMap();
    flightTree.printFlights();
    // month 6
    AddMonthlyNewRoutes(MONTHLY_CITY,cityGraph,flightTree); // calls nestedly add monthly new flights
    cancelUnpopularFlights(flightTree,cityGraph); // calls nestedly discard unpopular routes*/
    cityGraph.printRouteMap();
    flightTree.printFlights();
    // check for return flights
    checkNAddReturnRoutes(cityGraph,flightTree); // calls nestedly add return flights
    cityGraph.printRouteMap();
    flightTree.printFlights();
    // check possible routes
    displayRootOptions(flightTree,cityGraph,0,1);
    displayRootOptions(flightTree,cityGraph,1,13);
    displayRootOptions(flightTree,cityGraph,10,4);
    displayRootOptions(flightTree,cityGraph,5,10);
    displayRootOptions(flightTree,cityGraph,15,12);
     displayRootOptions(flightTree,cityGraph,"Gulf of Archi","Prokontrolkka");
    displayRootOptions(flightTree,cityGraph,"North Kirchoff","East Circuitta");
    displayRootOptions(flightTree,cityGraph,"South Kirchoff","Telecommunicastan");
    displayRootOptions(flightTree,cityGraph,"Biomedberg","Biomedberg");
    displayRootOptions(flightTree,cityGraph,"Logicheim","Magneta");

    cout<<endl;
    cout<<"---------------------- SYSTEM CHECK ---------------------------"<<endl;
    // the system can be checked by adding both new flights and cities (both of them should be added)
    flightTree.addTFlight(8,10);
    cityGraph.addGRoute(8,10);
    flightTree.addTFlight("East Circuitta","Island of Semicon");
    cityGraph.addGRoute("East Circuitta","Island of Semicon");
    flightTree.printFlights();
    cityGraph.printRouteMap();
    displayRootOptions(flightTree,cityGraph,"Logicheim","Magneta");



    return 0;
}
