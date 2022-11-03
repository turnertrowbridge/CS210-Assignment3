/**
 * Start of a driver file to test orgtree.cpp
 * CS 210 Fall 2022
 * @author Mitchell Shapiro <mshapiro6805@sdsu.edu>
 * @date Oct 2022
 */

#include "orgtree.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * THIS DRIVER FILE IS ONLY A START!
 * IT IS CRITICAL THAT YOU ADD YOUR
 * OWN TEST CASES. MOST CASES ARE
 * HIDDEN ON GRADESCOPE.
 */

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void assert(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
        // If you do comment this out, ignore the
        // "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    /*
     * Construct the following organization chart for testing
     *                1
     *           /    \    \
     *           2    3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     */

    Employee *head = new Employee(1, vector<int>{2, 3, 4});
    Employee *e2 = head->getDirectReports().at(0);
    Employee *e3 = head->getDirectReports().at(1);
    Employee *e4 = head->getDirectReports().at(2);

    e2->addDirectReports(vector<int>{5, 6});
    e3->addDirectReports(vector<int>{7, 8});
    e4->addDirectReport(9);

    Employee *e5 = e2->getDirectReports().at(0);
    Employee *e6 = e2->getDirectReports().at(1);
    Employee *e9 = e4->getDirectReports().at(0);

    e5->addDirectReport(10);
    e6->addDirectReport(11);
    e9->addDirectReport(12);

    // Begin Testing
    // A few sample testing code are provided below

    // TODO Test all Orgtree functions
    //      according to the specifications in the comment section ABOVE each function signature. 

    // IMPORTANT: You should also construct at least one different chart 
    // Also make sure to check edge cases, such as empty chart, or one employee chart.

    // Test isEmployeePresentInOrg function
    bool employeePresent = Orgtree::isEmployeePresentInOrg(head, 6);
    assert(employeePresent, "ID 6 Present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, -2);
    assert(employeePresent == false, "ID -2 Not present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 12);
    assert(employeePresent, "ID 12 present in tree");

    for (int i = 1; i < 13; i++) {
        employeePresent = Orgtree::isEmployeePresentInOrg(head, i);
        assert(employeePresent, "ID " + to_string(i) + " present in tree");
    }


    //TODO...

    // Test findEmployeeLevel function
    int employeeLevel = Orgtree::findEmployeeLevel(head, 6, 0);
    assert(employeeLevel == 2, "Level of ID 6 returns " + to_string(employeeLevel) + ", expected 2");

    employeeLevel = Orgtree::findEmployeeLevel(head, 12, 0);
    assert(employeeLevel == 3, "Level of ID 12 returns " + to_string(employeeLevel) + ", expected 3");

    employeeLevel = Orgtree::findEmployeeLevel(head, 8, 0);
    assert(employeeLevel == 2, "Level of ID 8 returns " + to_string(employeeLevel) + ", expected 2");

    employeeLevel = Orgtree::findEmployeeLevel(head, 789456, 0);
    assert(employeeLevel == -1, "Level of ID 789456 returns " + to_string(employeeLevel) + ", expected -1");

    //TODO...

    // Test findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // Assert / verify the returned Employee* has the expected Employee ID

    // null ptr test
    Employee *returned = Orgtree::findClosestSharedManager(nullptr, 14, 14);
    assert(returned == nullptr, "nullptr passed as head returns nullptr as expected");

    // e1 and e2 not present test
    returned = Orgtree::findClosestSharedManager(head, 14, 14);
    assert(returned == NULL, "Shared manager of 14 (not in tree) and 14 (not in tree) returns NULL as expected");

    // only e1 present test
    returned = Orgtree::findClosestSharedManager(head, 5, 13);
    assert(returned->getEmployeeID() == 5, "Shared manager of 5 and 13 (not in tree) returns " + to_string(returned->getEmployeeID()) + ", expected 5");

    // only e2 present test
    returned = Orgtree::findClosestSharedManager(head, 17, 7);
    assert(returned->getEmployeeID() == 7, "Shared manager of 17 (not in tree) and 7 returns " + to_string(returned->getEmployeeID()) + ", expected 7");

    // shared manager test #1
    returned = Orgtree::findClosestSharedManager(head, 10, 12);
    assert(returned->getEmployeeID() == 1, "Shared manager of 10 and 12 returns " + to_string(returned->getEmployeeID()) + ", expected 1");

    // shared manager test #2
    returned = Orgtree::findClosestSharedManager(head, 7, 8);
    assert(returned->getEmployeeID() == 3, "Shared manager of 7 and 8 returns " + to_string(returned->getEmployeeID()) + ", expected 3");

    // e1 is ancestor of e2 test
    returned = Orgtree::findClosestSharedManager(head, 2, 10);
    assert(returned->getEmployeeID() == 2, "Shared manager of 2 and 10 returns " + to_string(returned->getEmployeeID()) + ", expected 2");

    // e2 is ancestor of e1 test
    returned = Orgtree::findClosestSharedManager(head, 9, 4);
    assert(returned->getEmployeeID() == 4, "Shared manager of 9 and 4 returns " + to_string(returned->getEmployeeID()) + ", expected 4");

    //TODO...

    // Test findNumOfManagersBetween function
    int numManagers = Orgtree::findNumOfManagersBetween(head, 10, 11);
    assert(numManagers == 3, "Managers between 10 and 11 returns " + to_string(numManagers) + ", expected 3");

    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 77);
    assert(numManagers == -1, "Managers between 1 and 77(not present) returns " + to_string(numManagers) + ", expected -1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 89, 11);
    assert(numManagers == -1, "Managers between 89(not present) and 11 returns " + to_string(numManagers) + ", expected -1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 55, 78);
    assert(numManagers == -1, "Managers between 55(not present) and 78(not present) returns " + to_string(numManagers) + ", expected -1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 8);
    assert(numManagers == 1, "Managers between 1 and 8 returns " + to_string(numManagers) + ", expected 1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 10, 12);
    assert(numManagers == 5, "Managers between 10 and 12 returns " + to_string(numManagers) + ", expected 5");

    // TODO numManagers = ...

    // Test deleteOrgtree function
    // VERY IMPORTANT: Related to valgrind memory leaking detection testing,
    // You MUST call your deleteOrgtree function at the end of this driver testing code
    // to delete all the allocated memory for the tree. 

    Orgtree::deleteOrgtree(head);

    // Use the printed employee ID along the sequence of deletion to verify your implementation
    // This part will be autograded as well as manually inspected for grading


    /*
    * Construct the following organization chart for testing
    *                55
    *           /         \
    *           789       45
    *     / | | | | | \     /\
     *    1 7 2 5 8 3  20   75 11000
     *   /
     *   4
     *   |
     *   52
     *   |
     *   17
    */

    head = new Employee(55, vector<int>{789, 45});
    Employee *e789 = head->getDirectReports().at(0);
    Employee *e45 = head->getDirectReports().at(1);

    e789->addDirectReports(vector<int>{1, 7, 2, 5, 8, 3, 20});
    e45->addDirectReports(vector<int>{75, 11000});

    Employee* e1 = e789->getDirectReports().at(0);

    e1->addDirectReport(4);
    e4 = e1->getDirectReports().at(0);

    e4->addDirectReport(52);
    Employee *e52 = e4->getDirectReports().at(0);

    e52->addDirectReport(17);


    // Begin Testing
    // A few sample testing code are provided below

    // TODO Test all Orgtree functions
    //      according to the specifications in the comment section ABOVE each function signature.

    // IMPORTANT: You should also construct at least one different chart
    // Also make sure to check edge cases, such as empty chart, or one employee chart.

    // Test isEmployeePresentInOrg function
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 55);
    assert(employeePresent, "ID 55 Present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, -2);
    assert(employeePresent == false, "ID -2 Not present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 11000);
    assert(employeePresent, "ID 11000 present in tree");



    //TODO...

    // Test findEmployeeLevel function
    employeeLevel = Orgtree::findEmployeeLevel(head, 17, 0);
    assert(employeeLevel == 5, "Level of ID 17 returns " + to_string(employeeLevel) + ", expected 5");

    employeeLevel = Orgtree::findEmployeeLevel(head, 75, 0);
    assert(employeeLevel == 2, "Level of ID 75 returns " + to_string(employeeLevel) + ", expected 2");

    employeeLevel = Orgtree::findEmployeeLevel(head, -117, 0);
    assert(employeeLevel == -1, "Level of ID -117 returns " + to_string(employeeLevel) + ", expected -1");

    //TODO...

    // Test findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // Assert / verify the returned Employee* has the expected Employee ID

    // null ptr test
    returned = Orgtree::findClosestSharedManager(nullptr, 14, 14);
    assert(returned == nullptr, "nullptr passed as head returns nullptr as expected");

    // e1 and e2 not present test
    returned = Orgtree::findClosestSharedManager(head, 14, 14);
    assert(returned == NULL, "Shared manager of 14 (not in tree) and 14 (not in tree) returns NULL as expected");

    // only e1 present test
    returned = Orgtree::findClosestSharedManager(head, 5, 13);
    assert(returned->getEmployeeID() == 5, "Shared manager of 5 and 13 (not in tree) returns " + to_string(returned->getEmployeeID()) + ", expected 5");

    // only e2 present test
    returned = Orgtree::findClosestSharedManager(head, -29, 20);
    assert(returned->getEmployeeID() == 20, "Shared manager of -29 (not in tree) and 20 returns " + to_string(returned->getEmployeeID()) + ", expected 20");

    // shared manager test #1
    returned = Orgtree::findClosestSharedManager(head, 1, 20);
    assert(returned->getEmployeeID() == 789, "Shared manager of 1 and 20 returns " + to_string(returned->getEmployeeID()) + ", expected 789");

    // shared manager test #2
    returned = Orgtree::findClosestSharedManager(head, 52, 2);
    assert(returned->getEmployeeID() == 789, "Shared manager of 52 and 2 returns " + to_string(returned->getEmployeeID()) + ", expected 789");

    // shared manager test #3
    returned = Orgtree::findClosestSharedManager(head, 17, 11000);
    assert(returned->getEmployeeID() == 55, "Shared manager of 17 and 11000 " + to_string(returned->getEmployeeID()) + ", expected 55");

    // e1 is ancestor of e2 test
    returned = Orgtree::findClosestSharedManager(head, 45, 75);
    assert(returned->getEmployeeID() == 45, "Shared manager of 45 and 75 returns " + to_string(returned->getEmployeeID()) + ", expected 45");

    // e2 is ancestor of e1 test
    returned = Orgtree::findClosestSharedManager(head, 52, 1);
    assert(returned->getEmployeeID() == 1, "Shared manager of 52 and 1 returns " + to_string(returned->getEmployeeID()) + ", expected 1");

    // head node is ancestor test
    returned = Orgtree::findClosestSharedManager(head, 55, 17);
    assert(returned->getEmployeeID() == 55, "Shared manager of 55 and 17 returns " + to_string(returned->getEmployeeID()) + ", expected 55");

    //TODO...

    // Test findNumOfManagersBetween function
    numManagers = Orgtree::findNumOfManagersBetween(head, 55, 4);
    assert(numManagers == 2, "Managers between 55 and 4 returns " + to_string(numManagers) + ", expected 2");

    numManagers = Orgtree::findNumOfManagersBetween(head, 11000, -99);
    assert(numManagers == -1, "Managers between 110000 and -99(not present) returns " + to_string(numManagers) + ", expected -1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 89, 1);
    assert(numManagers == -1, "Managers between 89(not present) and 1 returns " + to_string(numManagers) + ", expected -1");

    numManagers = Orgtree::findNumOfManagersBetween(head, -4, -3);
    assert(numManagers == -1, "Managers between -4(not present) and -3(not present) returns " + to_string(numManagers) + ", expected -1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 8);
    assert(numManagers == 1, "Managers between 1 and 8 returns " + to_string(numManagers) + ", expected 1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 11000, 17);
    assert(numManagers == 6, "Managers between 11000 and 17 returns " + to_string(numManagers) + ", expected 6");

    // TODO numManagers = ...

    // Test deleteOrgtree function
    // VERY IMPORTANT: Related to valgrind memory leaking detection testing,
    // You MUST call your deleteOrgtree function at the end of this driver testing code
    // to delete all the allocated memory for the tree.

    Orgtree::deleteOrgtree(head);

    // Use the printed employee ID along the sequence of deletion to verify your implementation
    // This part will be autograded as well as manually inspected for grading

    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}