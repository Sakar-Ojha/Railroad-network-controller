#include "railroad.h"

// Name: Railroad  
// Description: Initializes a new Railroad object with zero stations and no head or tail.  
// Preconditions: None.  
// Postconditions: A Railroad object is created with m_numStations set to 0, m_head and m_tail set to nullptr.  
Railroad::Railroad(){
    m_numStations = 0;// number of stations in the network
    m_head = nullptr;
    m_tail = nullptr;
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: ~Railroad  
// Description: Destructor that clears the railroad network by deleting all stations.  
// Preconditions: A Railroad object has been created.  
// Postconditions: All memory used by the railroad network is deallocated, and the network is cleared.  

Railroad::~Railroad(){
    clearNetwork();
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: clearNetwork  
// Description: Deallocates all stations in the railroad network and resets the network's state.  
// Preconditions: The Railroad object has been initialized with stations.  
// Postconditions: All stations are deleted, and the railroad network is reset to its initial state with 0 stations.  

void Railroad::clearNetwork(){
     //Iterating through the linked list and deallocating each node
    Station* currentNode = m_head;
    while(currentNode){ //evaluates to false if its a nullptr
        Station* nextNode = currentNode->m_next;
        delete currentNode; // delete the current node to make sure no memory leaks
        currentNode = nextNode;
    }

    //Reinitializing variables back to default
    m_numStations = 0;// number of stations in the network
    m_head = nullptr;
    m_tail = nullptr;
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: extendAtHead  
// Description: Adds a new station at the head of the railroad network.  
// Preconditions: A valid passenger count and station code are provided.  
// Postconditions: The new station is added at the head of the network if it doesn't already exist.  

bool Railroad::extendAtHead(int newCode, int passengers){
    if (passengers < 0){ // if the passengers value is invalid range
        return false;
    }
    if (newCode <= 0){
        return false;
    }

    Station* travelNode = m_head; // initialize a node to go through the list
    
    while(travelNode != nullptr){
        if (travelNode->m_code == newCode){
            return false;
        }
        travelNode = travelNode->m_next; //traverse to next node
    }
    
    //Creating a new station object and setting the attributes
    Station* newStation = new Station; //create an empty station object and return its address
    newStation->m_code = newCode;
    newStation->m_passengers = passengers;

    if(m_head == nullptr){
        m_head = newStation;
    }
    else{
        newStation->m_next = m_head;
        m_head->m_previous = newStation; //doubly linked here
        m_head = newStation; // set it to m_head
        m_numStations ++; // added a new station
    }

    //if m_tail is also a null
    if(!m_tail){m_tail = m_head;}

    return true;
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: extendAtTail  
// Description: Adds a new station at the tail of the railroad network.  
// Preconditions: A valid passenger count and station code are provided.  
// Postconditions: The new station is added at the tail of the network if it doesn't already exist.  

bool Railroad::extendAtTail(int newCode, int passengers){
    if (passengers < 0){ // if the passengers value is invalid range
        return false;
    }
    if (newCode <= 0){
        return false;
    }
    
    Station* travelNode = m_head; // initialize a node to go through the list

    while(travelNode != nullptr){
        if (travelNode->m_code == newCode){
            return false; // if that station already exists
        }
        travelNode = travelNode->m_next; //traverse to next node
    }

    //Creating a new station object and setting the attributes
    Station* newStation = new Station;
    newStation->m_code = newCode;
    newStation->m_passengers = passengers;

    if(m_tail == nullptr){
        m_tail = newStation;
    }
    else{
        newStation->m_previous = m_tail; //previous in this case
        m_tail->m_next = newStation; //doubly linked here
        m_tail = newStation; // set it to m_tail
        m_numStations ++;
    }

    //if m_head is also a null
    if(!m_head){m_head = m_tail;}

    return true;
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
void Railroad::dump(){
    if (m_head != nullptr){
        int northCode, southCode, eastCode, westCode;
        Station *temp = m_head;
        while(temp != nullptr){
            if (temp->m_north != nullptr) northCode = temp->m_north->m_code;
            else northCode = -1;
            if (temp->m_south != nullptr) southCode = temp->m_south->m_code;
            else southCode = -1;
            if (temp->m_east != nullptr) eastCode = temp->m_east->m_code;
            else eastCode = -1;
            if (temp->m_west != nullptr) westCode = temp->m_west->m_code;
            else westCode = -1;
            cout << temp->m_code << 
                    " (" << 
                    "P: " << temp->m_passengers << 
                    ", N: " << northCode <<
                    ", S: " << southCode <<
                    ", E: " << eastCode <<
                    ", W: " << westCode <<
                    ")" << endl;
            temp = temp->m_next;
        }
    }
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: makeRoute  
// Description: Creates a route between stations based on the provided directions.  
// Preconditions: A valid route list is provided, and all stations in the route exist.  
// Postconditions: The route is created between the specified stations in the network, and connections are established.  

bool Railroad::makeRoute(list<pair<int,DIRECTION>> route){
    Station* currentNode = m_head;
    Station* travelNode = m_head; //This is a helper to find where the station is at

    //empty list
    if(route.empty()){ return false; }

    bool stationExists{false};

    //if NONE is not at the end
    if((route.back()).second != NONE){return false;}

    // Checking if the node exists in the List
    while(travelNode != nullptr){
        // Check if there is a station defined in the route's 1st station
        if(route.front().first == travelNode->m_code){
            currentNode = travelNode; //set the node as the current one
            stationExists = true;
        }

        travelNode = travelNode->m_next;
    }

    if(!stationExists){ return false; } // station doesnt exist

    travelNode = m_head; // reset back to head

    bool noneEncountered = false; // used to see if NONE is anywhere but at the end of the list
    for(std::list<pair<int,DIRECTION>>::iterator it = route.begin(); it != route.end(); ++it){
        // we check if none was encountered on the next loop so we know it wasnt at the end
        if(noneEncountered){return false;}

        if(it->second == NONE){
            noneEncountered = true; //set to true
        }
    }

    //If station has route to itself we return false 
    //NOTE: We check this after knowing NONE is at the end of the list
    for(std::list<pair<int,DIRECTION>>::iterator it = route.begin(); it != route.end(); ++it){
        //this store the previous element code
        int prevCode = 0;

        while((it->second) != NONE){
            //route to itself
            prevCode = it->first;
            it++;
            if(it->first == prevCode){
                return false;
            }
            prevCode = it->first;
        }
    }
    //if there is station that need to be extended to the tail
    for (std::list<pair<int,DIRECTION>>::iterator it = route.begin(); it != route.end(); ++it) {
        //default station Exists value to false
        //NOTE: this stationExists varibale is used to check if we have to extend to tail
        stationExists = false;

        while(travelNode!=nullptr){
            //check if the code matches
            if(it->first == travelNode -> m_code){
                stationExists = true; //set to true
            }
            travelNode=travelNode->m_next;
        }

        //we extend it to the tail if the provided station in the list doesnt exist in our linked list
        if(!stationExists){
            extendAtTail(it->first,DEFNUMPASS);
        }
        travelNode = m_head; // reset back to head
    }

    //this is to check for duplicates within the list itself
    // uses similar logic as checking for route to itself
    list<pair<int,DIRECTION>> checkDuplicates;
    checkDuplicates = route; //using copy constructor to create a copy
    checkDuplicates.sort();
    int prevCode = 0;
    DIRECTION prevDirection = NONE;
    for (std::list<pair<int,DIRECTION>>::iterator it = checkDuplicates.begin(); it != checkDuplicates.end(); ++it) {
        
        //route to itself
        prevCode = it->first;
        prevDirection = it->second;
        
        if(((it++->first) == prevCode) && ((it++->second) == prevDirection)){
            return false;
        }
    }

    // If the route is trying to alter an existing path and itself alters its own path
    for (std::list<pair<int,DIRECTION>>::iterator it = route.begin(); it != route.end(); ++it) {
        while((travelNode->m_next)!=nullptr){
            if(travelNode->m_code == it->first){

                if(it->second == NORTH){
                    if(travelNode->m_north){
                        return false;
                    }
                }
                else if(it->second == SOUTH){
                    if(travelNode->m_south){
                        return false;
                    }
                }
                else if(it->second == EAST){
                    if(travelNode->m_east){
                        return false;
                    }  
                }
                else if(it->second == WEST){
                    if(travelNode->m_west){
                        return false;
                    }
                }
            }
        }
        travelNode=m_head; //reset
    }

    // Using an iterator implementing make Route functionality
    for (std::list<pair<int,DIRECTION>>::iterator it = route.begin(); it != route.end(); ++it) {
        while(it->second != NONE){
            if(it->second == NORTH){
                // we are checking if there isnt already a value existing on the currentNode's direction to be changed
                //prevents cases where an existing route is being altered
                //this if statement is not necessary as we already did this check on top
                if(currentNode->m_north){
                    return false;
                }
                it++; //now we are on the next element/station on the given list
                while(travelNode != nullptr){
                    if(travelNode->m_code == it->first){
                        currentNode->m_north = travelNode;
                        currentNode = travelNode; // sets current Node to the next one on list
                    }

                    travelNode = travelNode->m_next; // next travel node
                }
            }

            // if next station is at South
            else if(it->second == SOUTH){
                if(currentNode->m_south){
                    return false;
                }
                it++; //now we are on the next element/station on the given list
                while(travelNode != nullptr){
                    if(travelNode->m_code == it->first){
                        currentNode->m_south = travelNode;
                        currentNode = travelNode; // sets current Node to the next one on list
                    }

                    travelNode = travelNode->m_next; //next travel node
                }         
            }

            // if next station is at East
            else if(it->second == EAST){
                if(currentNode->m_east){
                    return false;
                }
                it++; //now we are on the next element/station on the given list
                while(travelNode != nullptr){
                    if(travelNode->m_code == it->first){
                        currentNode->m_east = travelNode;
                        currentNode = travelNode; // sets current Node to the next one on list
                    }

                    travelNode = travelNode->m_next; //next travel node
                }         
            }

            //if next station is at West
            else if(it->second == WEST){
                if(currentNode->m_west){
                    return false;
                }
                it++; //now we are on the next element/station on the given list
                while(travelNode != nullptr){
                    if(travelNode->m_code == it->first){
                        currentNode->m_west = travelNode;
                        currentNode = travelNode; // sets current Node to the next one on list
                    }

                    travelNode = travelNode->m_next; //next travel node
                }         
            }

            travelNode = m_head; // reset the travel Node
        }
    }
    return true;
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: travel  
// Description: Simulates traveling through a series of stations according to the provided route.  
// Preconditions: A valid route list is provided, and all stations in the route exist.  
// Postconditions: The total number of passengers at the specified stations is returned.  

int Railroad::travel(list< pair<int,DIRECTION> > route){
    Station* travelNode = m_head;
    Station* currentNode = m_head;

    //lets us determine if all stations exist from the list
    bool stationExists;

    if(route.empty()){return -1;} // empty list of route

    // if the list contain some station not already on the linked list
    for (std::list<pair<int,DIRECTION>>::iterator it = route.begin(); it != route.end(); ++it) {
        //default station Exists value to false
        stationExists = false;

        while(travelNode!=nullptr){
            //check if the code matches
            if(it->first == travelNode -> m_code){
                stationExists = true; //set to true
            }
            travelNode=travelNode->m_next;
        }

        //we extend it to the tail if the provided station in the list doesnt exist in our linked list
        if(!stationExists){
           return -1; //-1 means false
        }

        travelNode = m_head; // reset back to head
    }

    //Now checking if the given list is valid
    //if NONE is anywhere but the end etc
    bool noneEncountered = false; // used to see if NONE is anywhere but at the end of the list
    for(std::list<pair<int,DIRECTION>>::iterator it = route.begin(); it != route.end(); ++it){
        // we check if none was encountered on the next loop so we know it wasnt at the end
        if(noneEncountered){return -1;}

        if(it->second == NONE){
            noneEncountered = true; //set to true
        }
    }

    //Set our currentNode to the first Station on the list
    while(travelNode!=nullptr){
        if(travelNode->m_code == route.front().first){
            currentNode = travelNode;
        }
        travelNode = travelNode->m_next;
    }

    travelNode = m_head; //reset travelNode

    // Checking if the links of the route is valid
    for(std::list<pair<int,DIRECTION>>::iterator it = route.begin(); it != route.end(); ++it){
        while(it->second != NONE){
            //checks if the link is valid
            bool linkValid = false;

            //checking if there is a link on that direction, if not returns false (-1)
            if(it->second ==NORTH){
                if(!currentNode->m_north){
                    return -1;
                }
                it++;
                //checking if the next stations m_code is the one given in the list of routes
                if(it->first == currentNode->m_north->m_code){
                    linkValid = true;
                    currentNode = currentNode->m_north; // currentNode is now the next station of the route
                }
            }

            //checking if there is a link on that direction, if not returns false (-1)
            if(it->second ==SOUTH){
                if(!currentNode->m_south){
                    return -1;
                }
                it++;
                if(it->first == currentNode->m_south->m_code){
                    linkValid = true;
                    currentNode = currentNode->m_south; // currentNode is now the next station of the route
                }
            }

            //checking if there is a link on that direction, if not returns false (-1)
            if(it->second ==EAST){
                if(!currentNode->m_east){
                    return -1;
                }
                it++;
                if(it->first == currentNode->m_east->m_code){
                    linkValid = true;
                    currentNode = currentNode->m_east; // currentNode is now the next station of the route
                }
            }

            //checking if there is a link on that direction, if not returns false (-1)
            if(it->second ==WEST){
                if(!currentNode->m_west){
                    return -1;
                }
                it++;
                if(it->first == currentNode->m_west->m_code){
                    linkValid = true;
                    currentNode = currentNode->m_west; // currentNode is now the next station of the route
                }
            }

            //testing if the link is valid at the end of the process
            if(!linkValid){return -1;}
        }
    }

    //Now after everything is checked we do the travel and return the total number of passengers
    currentNode = m_head;
    int totalNumPassengers = 0; //Set to 0 to avolid undeffined int values

    for(std::list<pair<int,DIRECTION>>::iterator it = route.begin(); it != route.end(); ++it){
        while(travelNode!=nullptr){
            if(travelNode->m_code == it->first){
                currentNode = travelNode;
            }
            travelNode = travelNode->m_next;
        }
        //Added to the total sum
        totalNumPassengers += currentNode->m_passengers;
        travelNode = m_head; //reset the travel node afterwards
    }  
    // return the total passengers from all stations
    return totalNumPassengers;
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: setNumPassengers  
// Description: Sets the number of passengers for a specific station.  
// Preconditions: A valid station code and passenger count are provided.  
// Postconditions: The number of passengers for the specified station is updated, or false is returned if the station is not found.  

bool Railroad::setNumPassengers(int code, int passengers){
    if (passengers < 0){ // if the passengers value is invalid range
        return false;
    }

    Station * travelNode = m_head;
    while (travelNode != nullptr){
    if(travelNode->m_code == code){
        travelNode->m_passengers = passengers;
        return true; //setting the number of passenngers on the station is succesful
    }
    else{travelNode = travelNode->m_next;}
    }
    return false; //if the code doesnt exist in the linked list.
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: removeStation  
// Description: Removes a station from the railroad network and updates all connections.  
// Preconditions: The station code exists in the network.  
// Postconditions: The specified station is removed, and all references to it from other stations are cleared.  

bool Railroad::removeStation(int aCode){    
    Station * travelNode = m_head;
    Station * removeNode = nullptr; //stores the address for the node being removed

    while (travelNode != nullptr){
        //cheking if there exists that station for us to delete
        if(travelNode->m_code == aCode){
            //we set the remove node equal to the one being deleted
            removeNode = travelNode;
        }
        travelNode = travelNode->m_next;
    }
    // if the node to remove doesnt exist
    if(!removeNode){return false;}

    //reset travelNode
    travelNode = m_head;

    while (travelNode != nullptr){
        //if there exists a link of that station on that node getting traversed
        if(travelNode->m_east == removeNode){
            travelNode->m_east = nullptr;  
        } 
        if(travelNode->m_west == removeNode){
            travelNode->m_west = nullptr;
        }
        if(travelNode->m_north == removeNode){
            travelNode->m_north = nullptr;
        }
        if(travelNode->m_south == removeNode){
            travelNode->m_south = nullptr;
        }
        travelNode = travelNode -> m_next;
    }

    //Implementing removing logic
    //set the nodes next to it point to each other
    // taking account for nullptr cases as well
    if(removeNode == m_tail){
        if(m_numStations == 1){
            m_head = nullptr;
            m_tail = nullptr;
            delete removeNode;
            m_numStations--; 
            return true;
        }
        else{
        removeNode->m_previous->m_next = nullptr;
        m_tail = removeNode->m_previous;
        delete removeNode;
        m_numStations--;
        return true;}
    }
    if(removeNode == m_head){
        removeNode->m_next->m_previous = nullptr;
        m_head = removeNode->m_next;
        delete removeNode;
        m_numStations--;
        return true;
    }

    removeNode->m_next->m_previous = removeNode->m_previous;
    removeNode->m_previous->m_next = removeNode->m_next;

    delete removeNode;
    m_numStations--;

    return true;
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: clearAllRoutes  
// Description: Clears all direction pointers (routes) from the railroad network.  
// Preconditions: The Railroad object contains stations with existing routes.  
// Postconditions: All direction pointers (north, south, east, west) are set to nullptr.  

//Goes through the linked list and sets every direction pointers to null
//therefore clearing all routes
void Railroad::clearAllRoutes(){
    Station* travelNode = m_head;

    while (travelNode!= nullptr){
        if(travelNode->m_north){
            travelNode->m_north = nullptr;
        }
        if(travelNode->m_south){
            travelNode->m_south = nullptr;
        }
        if(travelNode->m_east){
            travelNode->m_east = nullptr;
        }
        if(travelNode->m_west){
            travelNode->m_west = nullptr;
        }

        travelNode = travelNode->m_next;
    }
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// Name: operator=  
// Description: Assignment operator for copying a railroad network from one object to another.  
// Preconditions: A valid Railroad object exists for assignment.  
// Postconditions: The current object is assigned the state of the provided rhs object.  

// Assignment Operator
const Railroad& Railroad::operator=(const Railroad& rhs) {
    if (this == &rhs) { // self-assignment check
        return *this;
    }

    // Clear the current list before copying
    clearNetwork();

    // Copy stations one by one
    Station* rhsNode = rhs.m_head;
    Station* prevNewNode = nullptr;

    while (rhsNode != nullptr) {
        // Create a new station
        Station* newNode = new Station;
        newNode->m_code = rhsNode->m_code;
        newNode->m_passengers = rhsNode->m_passengers;

        // Link into the new list
        if (!m_head) {
            m_head = newNode;
        } else {
            prevNewNode->m_next = newNode;
            newNode->m_previous = prevNewNode;
        }

        prevNewNode = newNode;
        rhsNode = rhsNode->m_next;
        m_tail = newNode;
        m_numStations++;
    }

    // Now fix the route (north/south/east/west) connections
    Station* thisNode = m_head;
    rhsNode = rhs.m_head;
    while (rhsNode != nullptr) {
        if (rhsNode->m_north) {
            // Find the corresponding station in *this*
            int targetCode = rhsNode->m_north->m_code;
            Station* findNode = m_head;
            while (findNode && findNode->m_code != targetCode) {
                findNode = findNode->m_next;
            }
            thisNode->m_north = findNode;
        }
        if (rhsNode->m_south) {
            int targetCode = rhsNode->m_south->m_code;
            Station* findNode = m_head;
            while (findNode && findNode->m_code != targetCode) {
                findNode = findNode->m_next;
            }
            thisNode->m_south = findNode;
        }
        if (rhsNode->m_east) {
            int targetCode = rhsNode->m_east->m_code;
            Station* findNode = m_head;
            while (findNode && findNode->m_code != targetCode) {
                findNode = findNode->m_next;
            }
            thisNode->m_east = findNode;
        }
        if (rhsNode->m_west) {
            int targetCode = rhsNode->m_west->m_code;
            Station* findNode = m_head;
            while (findNode && findNode->m_code != targetCode) {
                findNode = findNode->m_next;
            }
            thisNode->m_west = findNode;
        }

        rhsNode = rhsNode->m_next;
        thisNode = thisNode->m_next;
    }

    return *this;
}
//_______________________________________________________________________________________
// Name: Railroad(const Railroad &rhs)  
// Description: Copy constructor for creating a new Railroad object as a copy of an existing one.  
// Preconditions: A valid Railroad object exists to copy.  
// Postconditions: A new Railroad object is created as a copy of the provided rhs object.  

// Copy Constructor
Railroad::Railroad(const Railroad& rhs) {
    m_head = nullptr;
    m_tail = nullptr;
    m_numStations = 0;

    // Use operator= logic to do the deep copy
    *this = rhs;
}