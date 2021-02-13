/*Lottery double linked list library by Kurtis Shane Wilhoite */

/*Explaination - A doubly linked list is a linked list which not only
points points forward, but also backward. This is however, not a circularly
linked list, as the tail of the list does not point back to the list. However,
we've been told circularly linked lists are allowed if necessary. */
#include <iostream> //Allows usage of cin/cout.
#include <vector> //Vector functionality
#include <ctime> //Rand functionality
#include <algorithm> //Sort functionality
using namespace std;

//Initalizing basic structure per node
struct node{
    int data;
    node *next;
    node *prev;
};

class list{
    private:
        node *head, *tail; //Each segment still needs a head and tail.
    public:
//Default constructor
        list(){
            head = NULL;
            tail = NULL;
        }
//Insertion
        //This functions the same way as with a normal linked list but with an additional segment at the end that directs the previous point
        void insertEnd(int val){
            //If its empty, creates a sigular node linked to itself
            if(head == NULL){
                node *temp = new node;
                temp->data = val;
                temp->next = temp->prev = temp;
                head = temp;
                return;
            }
            //Otherwise, Find last node
            tail = head->prev;

            //Set data to node
            node *temp = new node;
            temp->data = val;
            temp->next = head;

            //Set other node's data
            head->prev = temp;
            temp->prev = tail;
            tail->next = temp;
        }
        void insertBegin(int val){
            tail = head->prev;

            //Sets data to new node and sets its position at beginning
            node *temp = new node;
            temp->data = val;
            temp->next = head;
            temp->prev = tail;

            //Sets position of other nodes
            tail->next = head->prev = temp;

            //Temp is the new head
            head = temp;
        }
        void insertAfter(int afterval, int val){
            //Sets data to new node
            node *temp = new node;
            temp->data = afterval;

            //Creates temporary moving node that hits value
            node *aftertemp = head;
            while(aftertemp->data != val){
                aftertemp = aftertemp->next;
            }
            node *nextpos = aftertemp->next;

            //insert temp between the next node and previous
            aftertemp->next = temp;
            temp->prev = aftertemp;
            temp->next = nextpos;
            nextpos->prev = temp;
        }
//Search Node
        node *search(int val){ //Specified by the project, this part needs to search odd numbers backwards and even forwards
            if(val % 2 == 0){ //Traversal is backward if even. Sets a temporary tail that scrolls through backward and returns the temp
                node *temp = tail;
                while(temp->prev != tail){
                    if(temp->data == val){
                        return temp;
                    }
                    temp = temp->prev;
                }
                if(temp->data == val){
                    return temp;
                }
                return nullptr;
            } else { //Traversal is forward if odd. Sets a temporary head that scrolls through forward and returns the temp
                node *temp = head;
                while(temp->next != head){
                    if(temp->data == val){
                        return temp;
                    }
                    temp = temp->next;
                }
                if(temp->data == val){
                    return temp;
                }
                return nullptr; //Returns a nullptr if it can't be found within the list.
            }
        }
//Deletion
        void deleteNode(int val){
            node *temp = search(val); //Performs the previous search function.
            if(temp == nullptr){ //This essentially shouldn't happen, it's only if it's attempting to delete a node that doesn't exist.
                cout<<"\nError encountered.\n";
                return;
            } else{
                node *top = head; //Temporary head
                node *bottom = head->prev; //Temporary tail
                if(top == temp){ //If the head is the temp (being deleted), this changes the pointers to the next and previous, then ends.
                    bottom->next = top->next;
                    top->prev->next->prev = bottom;
                    head = bottom->prev;
                    delete top;
                    return;
                } else if(bottom == temp){ //If the tail is the temp (being deleted), this changes the pointers to the next and previous, then ends.
                    node *curr = bottom;
                    top = bottom->prev;
                    top->next = curr->next;
                    bottom = top;
                    delete curr;
                    return;
                } else{
                    while(top->next != head){ //While head's next is not head, essentially looping through the list
                        if(top == temp){ //Once temp head is equal to the temp (to be deleted), it then replaces it's pointers with the ones required. Otherwise it moves to the next point.
                            top->prev->next = top->next;
                            top->prev->next->prev = top->prev;
                            return;
                        }
                        top = top->next;
                    }
                }
            }
        }
//Print
        void print(){ //Looping through and printing the whole list
            node *temp = head;

            cout << "\nNumbers in forward order: \n";
            while(temp->next != head){
                cout << " "<<temp->data;
                temp = temp->next;
            }
            cout << " "<< temp->data<<endl;
        }
        void revPrint(){ //Looping through and printing the whole list in reverse
            node *last = head->prev;
            node *temp = head;
            temp = last;

            cout << "\nNumbers in reverse order: \n";
            while(temp->prev != last){
                cout << " "<<temp->data;
                temp = temp->prev;
            }
            cout << " "<<temp->data<<endl;
        }
};


//This contains the lottery data and uses the node list above
class lotto{
    private:
        int limit = 40; //Upper limit of the lottery
        int difNum = 6; //Limit of the numbers in the lottery
        list lottery; //Initalizing lottery list
    public:
        vector<int> lotteryList;
        lotto(){
            for(int i = 1; i <= limit; i++){ //Builds a 1-40 list of nodes
                lottery.insertEnd(i);
            }
        }
        void deleteNode(int val){ //Shortcut to deleteNode of the list
            lottery.deleteNode(val);
        }
        void createListing(){ //Creates the lottery numbers
            srand((unsigned)time(NULL)); //Random seed
            for(int i = 0; i < difNum; i++){ //For loop to create 6 numbers
                bool loop = true;

                while(loop == true){
                    loop = false;
                    int a = rand()% limit + 1;

                    for(int j = 0; j < limit; j++){
                        if(lottery.search(a) == nullptr){ //If the list search reaches a nullptr, that means it found a duplicate and should retry.
                            loop = true;
                            break;
                        }
                    }
                    if(loop == true){ //I is lowered if loop is marked as true.
                        i--;
                        break;
                    }
                    lottery.deleteNode(a); //Deleting the given number from the node list for duplication checking
                    lotteryList.push_back(a); //Adding it to the vector list for checking and usage
                }
            }
            sort(lotteryList.begin(), lotteryList.end()); //Sorting the lottery array
        }
        void printLotteryListing(){ //Printing the lottery array
            cout << "\nLottery numbers are: ";
            for(int i = 0; i < lotteryList.size(); i++){
                cout << lotteryList[i]<<" ";
            }
        }
        void print(){ //printing the available nodes that weren't deleted
            lottery.print();
        }
        void revPrint(){ //Same as above but in reverse.
            lottery.revPrint();
        }
};