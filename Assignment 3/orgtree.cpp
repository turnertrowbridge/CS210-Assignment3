#include <algorithm>
#include "orgtree.h"

/**
 * SINGLE EXAMINEE AFFIDAVIT
*“I, the undersigned, promise that this exam submission is my own work. I recognize that should this not
*be the case; I will be subject to plagiarism penalties as outlined in the course syllabus.”
*Student Name: Turner Trowbridge
*RED ID: 827959204
Date: 11/2/2022
*/


/**
 * Check if an employee is present in an organization chart. 
 * 
 * @param  head the head / root Employee of the organization chart
 * @param  e_id the employee id being searched
 * @return      true or false
 * @see         
 */
bool Orgtree::isEmployeePresentInOrg(Employee *head, int e_id) {
    // Write your recursive implementation here

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

    // base case 1: empty organization chart
    if (head == nullptr) {
        return false;
    }
        // base case 2: if the employee is found, return true
    else if (head->getEmployeeID() == e_id) {
        return true;
    }

    // search employee from each child of the head
    // return true if the employee is found in one of the child subtree
    // if not found, return false

    // loop through child nodes
    for (Employee *e: head->getDirectReports()) {
        // recursively search child nodes for id
        if (isEmployeePresentInOrg(e, e_id)) {
            return true;
        }
    }
    // return false if no more child nodes
    return false;
}

/**
 * Find the level of an employee in an organization chart / tree. 
 * 
 * <p>
 * The head / root of the org chart has a level of 0, children of the head have
 * a level of head plus 1, and so on and so forth... 
 * 
 * <p>
 * Assumption: e_id is unique among all employee IDs
 *
 * @param  head      the head / root Employee of the organization chart
 * @param  e_id      the employee id being searched
 * @param  headLevel the level of the head employee of the organization 
 * @return    level of the employee in the org chart
 *      returns Employee::NOT_FOUND if e_id is not present
 * @see         
 */
int Orgtree::findEmployeeLevel(Employee *head, int e_id, int headLevel) {
    // Write your recursive implementation here.

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

    // base case 1: empty organization chart
    if (head == nullptr) {
        return Employee::EMPTY_EMPLOYEEID;
    }
        // base case 2: if the employee is found, return headLevel
    else if (head->getEmployeeID() == e_id) {
        return headLevel;
    }

    // search employee from each child of the head
    // loop through child nodes
    for (Employee *e: head->getDirectReports()) {
        // recursively search child nodes for id
        const int result = findEmployeeLevel(e, e_id, headLevel + 1);
        if (result >= 0) {
            return result;
        }
    }
    // return -1 if no more child nodes found
    return Employee::EMPTY_EMPLOYEEID;
}

/**
 * Find the closest shared manager of two employees e1 and e2. 
 * 
 * <p>
 * There are two possible organizational relationships between two employees in the org chart:
 * case 1: e1 or e2 is a manager of the other employee;
 * case 2: e1 or e2 is not a manager of the other employee, they have at least one shared manager
 *
 * Employee 1 is a manager of employee 2 if employee 1 is an ancestor of employee 2 in the organization chart 
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   closest shared manager in the org chart between employee e1 and employee e2
   *           if head is nullptr, returns nullptr
   *           if neither e1 or e2 is present, returns empty employee           
   *           if e1 is present and e2 is not, returns e1
   *           if e2 is present and e1 is not, returns e2
   *           if e1 and e2 both are present, returns their shared manager
   *              if e1 is a manager (ancestor) of e2, returns e1
   *              else if e2 is a manager (ancestor) of e1, returns e2
   *              else returns the shared manager of e1 and e2
 * @see         
 */
Employee *Orgtree::findClosestSharedManager(Employee *head, int e1_id, int e2_id) {
    // Write your recursive implementation here

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

    // base case 1: empty organization chart
    if (head == nullptr) {
        return nullptr;
    }

    // base case 2: either e1_id or e2_id is the same as the head / root
    if (head->getEmployeeID() == e1_id || head->getEmployeeID() == e2_id) {
        return head;
    }

    // Recursively traverse through direct reports of the head to find
    // where e1 and e2 are

    /*
       For each recursive call (starting from the root), you need to handle three possible scenarios:
       1) if e1 is found in one subtree, and e2 is found from another subtree;
          the head at that recursive step would be the closest shared manager of e1 and e2.

          you can use the returned pointer (being NOT NULL) from findClosestSharedManager
          to see if e1 or e2 is found from a subtree (one of the base cases).

       2) if either e1 or e2 is first found in one subtree (following one subtree),
          but the other employee is NOT found from any other subtree, then the found
          employee must either be the manager of the other employee, or the other employee
          is NOT in the org chart; in either case, the first found employee should be
          returned as the shared manager.

       3) if neither e1 or e2 is found in the org chart, return nullptr
    */

    // check if e1 or e2 is present inside tree
    bool e1Present = isEmployeePresentInOrg(head, e1_id);
    bool e2Present = isEmployeePresentInOrg(head, e2_id);

    for (Employee *e: head->getDirectReports()) {

        // Check if e1 and e2 are in the subtree
        bool e1InSubtree = isEmployeePresentInOrg(e, e1_id);
        bool e2InSubtree = isEmployeePresentInOrg(e, e2_id);

        // if employees are in same subtree
        // search deeper in subtree
        if (e1InSubtree && e2InSubtree) {
            return findClosestSharedManager(e, e1_id, e2_id);
        }

        // if both employees are present and only one employee is in the subtree
        // return parent
        else if (e1Present && e2Present && (e1InSubtree || e2InSubtree)) {
            return head;
        }

        // if ONLY one employee is present and employee is in the subtree
        // go deeper to find position of present employee
        else if ((e1Present || e2Present) && (e1InSubtree || e2InSubtree)) {
            return findClosestSharedManager(e, e1_id, e2_id);
        }
    }

    //neither e1 nor e2 is found
    return NULL;
}

/**
 * Calculate the number of managers between employee e1 and employee e2. 
 * 
 * <p>
 * The number of managers between employee e1 and employee e2 can be calculated by: 
 *  number of edges between employee 1 and closest shared manager + 
 *  number of edges between employee 2 and closest shared manager - 1
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   number of managers between employee e1 and employee e2
 *           returns Employee::NOT_FOUND if either e1 or e2 is not present in the chart
 * @see         
 */
int Orgtree::findNumOfManagersBetween(Employee *head, int e1_id, int e2_id) {

    // Write your implementation here. You do NOT need to use recursive approach here.
    // Use the above functions wherever you need to implement this function.

    bool e1Present = isEmployeePresentInOrg(head, e1_id);
    bool e2Present = isEmployeePresentInOrg(head, e2_id);

    if (!e1Present || !e2Present) {
        return Employee::NOT_FOUND;
    }

    Employee *sharedManager = findClosestSharedManager(head, e1_id, e2_id);
    int sharedManagerLevel = findEmployeeLevel(head, sharedManager->getEmployeeID(), 0);

    // find edges between employees and return

            // employee 1 level - manager level - 1
    return findEmployeeLevel(head, e1_id, 0)
           - sharedManagerLevel

           // add
           // employee 2 level - manager level
           + findEmployeeLevel(head, e2_id, 0)
           - sharedManagerLevel - 1;

    // Continue only if both employee nodes e1_id and e2_id are in the org chart tree
    // otherwise, return Employee::NOT_FOUND

    // The number of managers between employee e1 and employee e2 can be calculated by:
    // number of edges between e1_id and closest shared manager +
    // number of edges between e2_id and closest shared manager - 1

}

/** Recursively delete a tree 
 *  The proper implementation of this function is also needed for
 *  passing the valgrind memory leaking test. 
 * 
 * <p>
 * Traversing from the head / root node, recursively deallocate 
 * the memory of the descendants from the leaf node level. 
 *
 * DO NOT worry about removing them from the vector directReports
 * 
 * Use post order traversal:
 * Delete / deallocate the children recursively
 * Delete / deallocate the current node after deleting its children
 *     Before deleting the current node, print its employee ID and a new line
 *     This part will be autograded as well as manually inspected for grading
 * 
 * For example, with the following org chart, the post order traversal
 * order would be 5 6 2 7 8 3 1, and the nodes should be deleted in that order
 *             1
 *           /    \
 *           2    3
 *          / \  / \
 *          5 6  7 8
 *
 * @param  head  the head / root Employee of the organization chart
 * @return   None 
 * 
 * @see         
 */
void Orgtree::deleteOrgtree(Employee *head) {
    // Write your recursive implementation here

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

    // base case: empty tree or organization chart
    if (head == NULL)
    {
        return;
    }
    // delete children recursively
    for (Employee *e: head->getDirectReports()) {
        deleteOrgtree(e);
    }
    // print current node's employee ID and a new line
    cout << head->getEmployeeID() << endl;
    // delete the current node after deleting its children
    delete head;
}