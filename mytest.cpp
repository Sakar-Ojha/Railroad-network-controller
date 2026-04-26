#include "railroad.h"
using namespace std;

class Tester {
public:
    /*
    Pre: Railroad is empty. 
    Post: After inserting 300 valid stations at head, 
          extendAtHead should return true each time 
          and m_numStations == 300.
    */
    void testExtendAtHeadNormal() {
        Railroad net;
        bool allInserted = true;

        // Insert 300 stations at the head of the list
        for (int i = 1; i <= 300; i++) {
            if (!net.extendAtHead(i, i)) {
                allInserted = false; // If any insert fails, test fails
            }
        }

        // Verify insertion count and success
        if (allInserted && net.m_numStations == 300) {
            cout << "testExtendAtHeadNormal passed!\n";
        } else {
            cout << "testExtendAtHeadNormal FAILED!\n";
        }
    }

    /*
    Pre: Railroad is empty. 
    Post: Calling extendAtHead with invalid code (<1) 
          should return false and not change station count.
    */
    void testExtendAtHeadError() {
        Railroad net;
        bool result = net.extendAtHead(0, 50); // invalid station code

        if (result == false && net.m_numStations == 0) {
            cout << "testExtendAtHeadError passed!\n";
        } else {
            cout << "testExtendAtHeadError FAILED!\n";
        }
    }

    /*
    Pre: Railroad is empty. 
    Post: After inserting 100 valid stations at tail, 
          extendAtTail should return true each time 
          and m_numStations == 100.
    */
    void testExtendAtTailNormal() {
        Railroad net;
        bool allInserted = true;

        // Insert 100 stations at the tail of the list
        for (int i = 1; i <= 100; i++) {
            if (!net.extendAtTail(i, i)) {
                allInserted = false;
            }
        }

        if (allInserted && net.m_numStations == 100) {
            cout << "testExtendAtTailNormal passed!\n";
        } else {
            cout << "testExtendAtTailNormal FAILED!\n";
        }
    }

    /*
    Pre: Railroad is empty. 
    Post: Calling extendAtTail with invalid code (<1) 
          should return false and not change station count.
    */
    void testExtendAtTailError() {
        Railroad net;
        bool result = net.extendAtTail(-5, 100);

        if (result == false && net.m_numStations == 0) {
            cout << "testExtendAtTailError passed!\n";
        } else {
            cout << "testExtendAtTailError FAILED!\n";
        }
    }

    /*
    Pre: Railroad has 10 stations.
    Post: Removing all 10 stations by valid codes 
          should succeed and result in empty list.
    */
    void testRemoveStationNormal() {
        Railroad net;
        // Add 10 stations
        for (int i = 1; i <= 10; i++) {
            net.extendAtTail(i, i * 2);
        }

        bool allRemoved = true; // to check that at every removal the function returns true
        // Remove them one by one
        for (int i = 1; i <= 10; i++) {
            if (!net.removeStation(i)) {
                allRemoved = false;
            }
        }

        if (allRemoved && net.m_numStations == 0) {
            cout << "testRemoveStationNormal passed!\n";
        } else {
            cout << "testRemoveStationNormal FAILED!\n";
        }
    }

    /*
    Pre: Railroad has 1 station.
    Post: Trying to remove a non-existing station code 
          should return false and leave count unchanged.
    */
    void testRemoveStationError() {
        Railroad net;
        net.extendAtTail(1, 20); // Add one station

        bool result = net.removeStation(99); // Invalid removal
        if (result == false && net.m_numStations == 1) {
            cout << "testRemoveStationError passed!\n";
        } else {
            cout << "testRemoveStationError FAILED!\n";
        }
    }

    /*
    Pre: Railroad has 3 stations with a route linking them. 
    Post: After removing a middle station, any links 
          pointing to it should be cleaned up (travel fails).
    */
    void testRemoveStationLinkCleanup() {
        Railroad net;
        net.extendAtTail(1, 10);
        net.extendAtTail(2, 20);
        net.extendAtTail(3, 30);

        // Create route 1 -> 2
        list<pair<int,DIRECTION>> route;
        route.push_back({1, EAST});
        route.push_back({2, NONE});
        net.makeRoute(route);

        // Remove station 2 (middle)
        net.removeStation(2);
        int travellers = net.travel(route);

        // After cleanup, traversal should fail since we just deleted station 2 from the route
        if (travellers < 0) {
            cout << "testRemoveStationLinkCleanup passed!\n";
        } else {
            cout << "testRemoveStationLinkCleanup FAILED!\n";
        }
    }

    /*
    Pre: Two distinct Railroad objects exist.
    Post: After assignment, they should have equal station counts 
          but deep copy (no shared head pointer).
    */
    void testAssignmentOperatorNormal() {
        Railroad net1;
        for (int i = 1; i <= 5; i++)
            net1.extendAtTail(i, i*10);

        Railroad net2;
        net2 = net1; // Assignment operator

        if (net1.m_numStations == net2.m_numStations &&
            net1.m_head != net2.m_head) {
            cout << "testAssignmentOperatorNormal passed!\n";
        } else {
            cout << "testAssignmentOperatorNormal FAILED!\n";
        }
    }

    /*
    Pre: Multiple small railroads created.
    Post: Assignment works with different sizes (1 and 2 stations).
    */
    void testAssignmentOperatorEdgeCases() {
        Railroad one, two;
        one.extendAtTail(1, 10);
        two = one;

        Railroad three, four;
        three.extendAtTail(1, 10);
        three.extendAtTail(2, 20);
        four = three;

        if (two.m_numStations == 1 && four.m_numStations == 2) {
            cout << "testAssignmentOperatorEdgeCases passed!\n";
        } else {
            cout << "testAssignmentOperatorEdgeCases FAILED!\n";
        }
    }

    /*
    Pre: Railroad with 5 stations.
    Post: Copy constructor produces a deep copy 
          with same count but different head pointer.
    */
    void testCopyConstructorNormal() {
        Railroad net1;
        for (int i = 1; i <= 5; i++)
            net1.extendAtTail(i, i*3);

        Railroad net2(net1); // Copy constructor

        if (net1.m_numStations == net2.m_numStations &&
            net1.m_head != net2.m_head) {
            cout << "testCopyConstructorNormal passed!\n";
        } else {
            cout << "testCopyConstructorNormal FAILED!\n";
        }
    }

    /*
    Pre: Railroad with small sizes.
    Post: Copy constructor correctly handles 1 and 2 stations.
    */
    void testCopyConstructorEdgeCases() {
        Railroad one;
        one.extendAtTail(1, 10);
        Railroad copyOne(one);

        Railroad two;
        two.extendAtTail(1, 10);
        two.extendAtTail(2, 20);
        Railroad copyTwo(two);

        if (copyOne.m_numStations == 1 && copyTwo.m_numStations == 2) {
            cout << "testCopyConstructorEdgeCases passed!\n";
        } else {
            cout << "testCopyConstructorEdgeCases FAILED!\n";
        }
    }

    /*
    Pre: Railroad has 1 station. Route starts from invalid code.
    Post: makeRoute should return false.
    */
    void testMakeRouteInvalidStart() {
        Railroad net;
        net.extendAtTail(1,10);

        list<pair<int,DIRECTION>> route;
        route.push_back({99, NONE}); // Invalid start station
        bool result = net.makeRoute(route);

        if (result == false) {
            cout << "testMakeRouteInvalidStart passed!\n";
        } else {
            cout << "testMakeRouteInvalidStart FAILED!\n";
        }
    }

    /*
    Pre: Railroad with 2 stations and a route between them.
    Post: Attempting to make a duplicate conflicting route 
          should return false.
    */
    void testMakeRouteOverwriteLink() {
        Railroad net;
        net.extendAtTail(1,10);
        net.extendAtTail(2,20);

        // First valid route 1 -> 2
        list<pair<int,DIRECTION>> route1;
        route1.push_back({1,EAST});
        route1.push_back({2,NONE});
        net.makeRoute(route1);

        // Overwriting same link should fail
        list<pair<int,DIRECTION>> route2;
        route2.push_back({1,EAST});
        route2.push_back({2,NONE});
        bool result = net.makeRoute(route2);

        if (result == false) {
            cout << "testMakeRouteOverwriteLink passed!\n";
        } else {
            cout << "testMakeRouteOverwriteLink FAILED!\n";
        }
    }

    /*
    Pre: Railroad with 3 stations and a valid route linking them.
    Post: travel should return sum of travellers (60 here).
    */
    void testTravelNormal() {
        Railroad net;
        net.extendAtTail(1,10);
        net.extendAtTail(2,20);
        net.extendAtTail(3,30);

        // Route: 1 -> 2 -> 3
        list<pair<int,DIRECTION>> route;
        route.push_back({1,EAST});
        route.push_back({2,EAST});
        route.push_back({3,NONE});
        net.makeRoute(route);

        int travellers = net.travel(route);

        if (travellers == 60) {
            cout << "testTravelNormal passed!\n";
        } else {
            cout << "testTravelNormal FAILED!\n";
        }
    }

    /*
    Pre: Railroad with 2 stations only.
    Post: travel should fail when route includes invalid station.
    */
    void testTravelError() {
        Railroad net;
        net.extendAtTail(1,10);
        net.extendAtTail(2,20);

        // Route tries to go to non-existing station 3
        list<pair<int,DIRECTION>> route;
        route.push_back({1,EAST});
        route.push_back({3,NONE});

        int travellers = net.travel(route);

        if (travellers < 0) {
            cout << "testTravelError passed!\n";
        } else {
            cout << "testTravelError FAILED!\n";
        }
    }

    /*
    Pre: Railroad with 3 stations.
    Post: Route beginning with a non-NONE direction 
          before reaching intended start should fail.
    */
    void testNoneAtBeginingOfList(){
        Railroad net;
        net.extendAtTail(1, 10);
        net.extendAtTail(2, 20);
        net.extendAtTail(3, 30);

        list<pair<int,DIRECTION>> route;
        route.push_back({2, SOUTH});
        route.push_back({1, NONE});
        route.push_back({3, SOUTH});

        bool result = net.makeRoute(route);

        if(!result){
            cout << "testNoneAtBeginningOfList passed!\n";
        }
        else {
            cout << "testNoneAtBeginningOfList FAILED!\n";
        }
    }

    /* 
    Pre: Railroad has 3 stations
    Post: all routes passengers is set to 0 
    and we set passengers to one of them using setNumPassengers 
    and travel along route containing all the stations to see if the result is what we set it to
    */
    void testSetPassengers(){
        Railroad net;

        //preset all passengers to 0
        net.extendAtTail(1, 0);
        net.extendAtTail(2, 0);
        net.extendAtTail(3, 0);

        //make a route with all the above stations
        list<pair<int,DIRECTION>> route;
        route.push_back({1,EAST});
        route.push_back({2,SOUTH});
        route.push_back({3,NONE});
        
        net.makeRoute(route);

        //sets passenger count to 50 here for second station
        // this will make the total passenger count 50 on all stations
        bool result = net.setNumPassengers(2,50);
        
        //it is a valid travel route and should be 50
        int passengerCount = net.travel(route);
        
        if(passengerCount == 50 && result){
            cout << "testSetPassengers passed!\n";
        }
        else{
            cout << "testSetPassengers FAILED!\n";
        }
    }

    /*
    Pre: we have 2 stations with routes linking one to another (valid)
    Post: We travel along and record the first result,
        then clear the routes then record the second travel result,
        shouldn't be the same as the routes have just been cleared
    */
    void testClearRoute(){
        Railroad net;
        net.extendAtTail(1, 10);
        net.extendAtTail(2, 20);
        // cout << net->getNumPassegers();
        //make a route with all the above stations
        list<pair<int,DIRECTION>> route;
        route.push_back({1,EAST});
        route.push_back({2,NONE});
        
        net.makeRoute(route);
        //this is to compare with the values after clearing
        int prevTotal = net.travel(route);

        net.clearAllRoutes(); // clear all the routes

        int totalAfter = net.travel(route); //there is no route anmore after clearing

        if(!(prevTotal == totalAfter)){
            cout << "testClearRoute passed!";
        }
        else{
            cout << "testClearRoute FAILED!";
        }
    }
};

int main() {
    Tester t;
    t.testExtendAtHeadNormal();
    t.testExtendAtHeadError();
    t.testExtendAtTailNormal();
    t.testExtendAtTailError();
    t.testRemoveStationNormal();
    t.testRemoveStationError();
    t.testRemoveStationLinkCleanup();
    t.testAssignmentOperatorNormal();
    t.testAssignmentOperatorEdgeCases();
    t.testCopyConstructorNormal();
    t.testCopyConstructorEdgeCases();
    t.testMakeRouteInvalidStart();
    t.testMakeRouteOverwriteLink();
    t.testTravelNormal();
    t.testTravelError();
    t.testNoneAtBeginingOfList();
    t.testSetPassengers();
    t.testClearRoute();
}
