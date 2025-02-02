#include "DoubleEndedQueue.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Helper function for assertions
void test(bool condition, const string& message) {
    if (!condition) {
        throw runtime_error("Test failed: " + message);
    }
}

void testInsertOperations() {
    cout << "=== Testing Insert Operations ===\n";
    DoubleEndedQueue<int> q;
    
    q.insertFront(10);
    test(q.getFront() == 10, "Front should be 10");
    test(q.getRear() == 10, "Rear should be 10");
    test(q.getSize() == 1, "Size should be 1");

    q.insertRear(20);
    test(q.getFront() == 10, "Front should remain 10");
    test(q.getRear() == 20, "Rear should be 20");
    test(q.getSize() == 2, "Size should be 2");

    q.insertFront(5);
    test(q.getFront() == 5, "Front should be 5");
    test(q.getRear() == 20, "Rear should remain 20");
    test(q.getSize() == 3, "Size should be 3");

    cout << "Insert operations tests passed!\n\n";
}

void testRemoveOperations() {
    cout << "=== Testing Remove Operations ===\n";
    DoubleEndedQueue<int> q;
    q.insertFront(10);
    q.insertRear(20);
    q.insertFront(5);

    q.removeFront();
    test(q.getFront() == 10, "New front should be 10");
    test(q.getRear() == 20, "Rear should remain 20");
    test(q.getSize() == 2, "Size should be 2");

    q.removeRear();
    test(q.getFront() == 10, "Front should remain 10");
    test(q.getRear() == 10, "Rear should now be 10");
    test(q.getSize() == 1, "Size should be 1");

    q.removeRear();
    test(q.isEmpty(), "Queue should be empty");
    test(q.getSize() == 0, "Size should be 0");

    cout << "Remove operations tests passed!\n\n";
}

void testErrorHandling() {
    cout << "=== Testing Error Handling ===\n";
    DoubleEndedQueue<int> q;

    try {
        q.getFront();
        test(false, "Should throw exception for empty queue");
    } catch (const logic_error& e) {
        test(true, "Properly threw exception for empty front");
    }

    try {
        q.removeRear();
        test(false, "Should throw exception for empty queue");
    } catch (const logic_error& e) {
        test(true, "Properly threw exception for empty remove");
    }

    cout << "Error handling tests passed!\n\n";
}

void testCopyOperations() {
    cout << "=== Testing Copy Operations ===\n";
    DoubleEndedQueue<int> original;
    original.insertFront(1);
    original.insertRear(2);
    original.insertRear(3);

    // Test copy constructor
    DoubleEndedQueue<int> copy1(original);
    test(copy1.getFront() == 1, "Copy front should match");
    test(copy1.getRear() == 3, "Copy rear should match");
    test(copy1.getSize() == 3, "Copy size should match");

    // Test assignment operator
    DoubleEndedQueue<int> copy2;
    copy2 = original;
    test(copy2.getFront() == 1, "Assignment front should match");
    test(copy2.getRear() == 3, "Assignment rear should match");
    test(copy2.getSize() == 3, "Assignment size should match");

    // Test independence
    original.removeFront();
    test(copy1.getFront() == 1, "Copy should remain unchanged");
    test(copy2.getFront() == 1, "Assignment copy should remain unchanged");

    cout << "Copy operations tests passed!\n\n";
}

void testPrintFunctions() {
    cout << "=== Testing Print Functions ===\n";
    DoubleEndedQueue<int> q;
    q.insertRear(10);
    q.insertRear(20);
    q.insertRear(30);

    cout << "Front to Rear: ";
    q.print();  // Should show [10 20 30]

    cout << "Rear to Front: ";
    q.printRear();  // Should show [30 20 10]

    cout << "Empty queue print test:\n";
    DoubleEndedQueue<int> empty;
    try {
        empty.print();
    } catch (const logic_error& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }

    cout << "Print tests completed!\n\n";
}

int main() {
    try {
        testInsertOperations();
        testRemoveOperations();
        testErrorHandling();
        testCopyOperations();
        testPrintFunctions();
        
        cout << "All tests passed successfully!\n";
        return 0;
    } catch (const exception& e) {
        cerr << "\nError: " << e.what() << endl;
        return 1;
    }
}