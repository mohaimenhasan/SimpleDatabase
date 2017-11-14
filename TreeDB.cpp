#include "TreeDB.h"
#include <iostream>
#include <iomanip>
using namespace std; 

TreeDB::TreeDB() //initiallizes the tree
{
    root = NULL;
    probesCount = 0;
}

TreeDB::~TreeDB()
{
    clear(); //calls clear to remove everything
}
int TreeDB::activeCount(TreeNode* head) const
{
    int active = 0;
    if(head==NULL)
        return 0;
    if(head->getEntry()->getActive() == true)
        active = 1;
    return activeCount(head->getLeft()) + activeCount(head->getRight()) + active;
}

bool TreeDB::insert(DBentry* newEntry)
{
    if(newEntry == NULL) //returns false if nothing has been entered  
        return false;
    if(root==NULL) //returns true if root is empty by creating a new node
    {
        root = new TreeNode(newEntry);
        return true;
    }
    return insertTree(root, newEntry); //calls the helper function for recursion
} 

DBentry* TreeDB::find(string name)
{
    probesCount = 0; //sets probes count to zero
    TreeNode* head = root; //returns NULL if nothing's there
    if (head == NULL or head->getEntry() == NULL) return NULL;
    return findEntry(head, name);
}

void TreeDB::changeActive(bool active, string name)
{
    DBentry *changeEntry = find(name); //finds the entry
    if (changeEntry){
        changeEntry->setActive(active); //changes active
        cout<<"Success"<<endl;
        return;
    }
    cout<<"Error: entry does not exist"<<endl;
}

//Helper function for finding entry through recursion 
DBentry* TreeDB::findEntry(TreeNode* p, string name)
{
    probesCount = probesCount + 1; // increases the probes count by 1
    if(p->getEntry()->getName() == name) // returns a DBebtry pointer if it finds it
        return p->getEntry();
    if(p->getEntry()->getName()>name)
    {
        if(p->getLeft() == NULL or p->getLeft()->getEntry() == NULL) // returns NULL if it reaches the end
            return NULL;
        else
            return findEntry(p->getLeft(), name); //goes to the left otherwise
    }
    if(p->getEntry()->getName()<name)
    {
        if(p->getRight() == NULL or p->getRight()->getEntry() == NULL) 
            return NULL;
        else
            return findEntry(p->getRight(), name); // goes to the right
    }
}

bool TreeDB::remove(string name)
{
    
    //Recursion has not been used because of the corner cases
    
    //Checks if there's anything 
    TreeNode* head=root;
    if(root == NULL)
        return false;
    while(head->getLeft()!=NULL or head->getRight()!=NULL)
    {
        if(head->getEntry()->getName()==name)
            break;
        if(head->getLeft() != NULL and head->getEntry()->getName()>name)
            head=head->getLeft();
        if(head->getRight() != NULL and head->getEntry()->getName()<name)
            head=head->getRight();        
    }
    //returns false if node doesn't exist
    if(head->getEntry()->getName()!=name)
        return false;
    
    //remove head
    if(head == root)
    {
        
        //checks if head just goes on to the left
        if(head->getLeft() == NULL)
        {
            //Replaces head by it's next node
            root = head->getRight();
            head->setLeft(NULL);
            head->setRight(NULL);            
            delete head;
            head = NULL;
            return true;
        }
        
        //checks if head just goes on to the right 
        else if(head->getRight() == NULL)
        {
            //replaces by the node on the right
            root = head->getLeft();
            head->setLeft(NULL);
            head->setRight(NULL);            
            delete head;
            head = NULL;
            return true;
        }
        
        //if head is not unidirectional
        else if (head->getRight()!=NULL and head->getLeft()!= NULL)
        {
            int n = 0;
            TreeNode* changeHead = head;
            TreeNode* track;
            
            //gets to the max node on the left side of head
            while(changeHead->getRight()!=NULL)
            {
                n=n+1;
                //it only goes to the left side of head for the first time in the while loop
                if(n==1)
                {
                    changeHead = changeHead->getLeft();
                }
                
                //Corner case if there is only one node on head's left
                if(changeHead->getRight() == NULL)
                {
                    track = changeHead;
                    break;
                }
                
                if (changeHead->getRight()->getRight() == NULL)
                {
                    track = changeHead->getRight();
                    break;
                }
                changeHead = changeHead->getRight();
            }
            
            //sets up the new head
            if(track != head->getLeft())
                track->setLeft(head->getLeft());
            track->setRight(head->getRight());
            if(changeHead!=track)
                changeHead->setRight(NULL);
            //makes track(the max node on left) as the new root
            root = track;
            
            //sets the head's left and right to zero
            head->setLeft(NULL);
            head->setRight(NULL);            
            delete head; //deletes the head
            head = NULL;
            return true;
        }
    }
    //Not a head
    //track to the node previous to the node to be deleted
    TreeNode* trackPrevious=root;
    while(trackPrevious->getLeft()!=NULL or trackPrevious->getRight()!=NULL)
    {
        //breaks out if any one of the conditions match
        if(trackPrevious->getLeft() !=NULL and trackPrevious->getLeft() == head)  
            break;
        if(trackPrevious->getRight() !=NULL and trackPrevious->getRight() == head)
            break;
        
        //moves left or right depending on the comparison
        if(trackPrevious->getLeft() !=NULL and trackPrevious->getEntry()->getName()>name)
            trackPrevious=trackPrevious->getLeft();
        else if(trackPrevious->getRight() !=NULL and trackPrevious->getEntry()->getName()<name)
            trackPrevious=trackPrevious->getRight();  
    }
    
    //if the node to be deleted is on the left side of the parent pointer
    if (trackPrevious->getLeft()==head)
    {
        //if the node is unidirectional and only goes on to the right
        if(head->getLeft()==NULL)
        {
            TreeNode* temp;
            //if it's a leaf node
            //checks if there's anything on the right side of the "to be deleted node"
            if (head->getRight() ==NULL)
                temp = NULL;
            else
                temp = head->getRight();
            //sets the parents next to the temporary pointer
            trackPrevious->setLeft(temp);
            //sets the to be deleted pointers next to NULL
            head->setLeft(NULL);
            head->setRight(NULL);            
            //deletes the node
            delete head;
            head = NULL;
            return true;
        }
        //if the node is unidirectional and only goes on to the left
        else if(head->getRight()==NULL)
        {
            TreeNode* temp;
            //checks if the node is the leaf of the tree
            if (head->getLeft() == NULL)
                temp = NULL;
            else
                temp = head->getLeft();
            trackPrevious->setLeft(temp);
            head->setLeft(NULL);
            head->setRight(NULL);            
            delete head;
            head = NULL;
            return true;
        }
    }
     //if the node to be deleted is on the right side of the parent pointer
    else if(trackPrevious->getRight() == head)
    {        
        if(head->getLeft()==NULL)
        {
            //checks if it's a leaf node
            TreeNode* temp;
            if (head->getRight() ==NULL)
                temp = NULL;
            else
                temp = head->getRight();
            trackPrevious->setRight(temp);
            head->setLeft(NULL);
            head->setRight(NULL);            
            delete head;
            head = NULL;
            return true;
        }
        else if(head->getRight()==NULL)
        {
            TreeNode* temp;
            //checks if it's a leaf node
            if (head->getLeft() == NULL)
                temp = NULL;
            else
                temp = head->getLeft();
            trackPrevious->setRight(temp);
            head->setLeft(NULL);
            head->setRight(NULL);            
            delete head;
            head = NULL;
            return true;
        }
    }
    //if "to be deleted" node is not unidirectional
    if (head->getLeft()!=NULL and head ->getRight()!=NULL)
    {
        //BS tree
        //Look into head->left
        //Then keep on looking on it's right
        //Find the largest key
        //Move it up to the top and replace head
        //trackPtr is supposed to point to the biggest node on the left side
        TreeNode *trackptr;
        TreeNode *findptr = head;
        int n = 0;
        //finding pointer to the biggest node on the left side of the "to be deleted pointer" using a while loop
        while(findptr->getRight() != NULL)
        {
            n=n+1;
            //goes to the left only on the first case
            if(n==1)
            {
                if(findptr->getLeft()!=NULL)
                    findptr=findptr->getLeft();
            }
            
            //corner case where it breaks out if there's only one node on the left side
            if(findptr->getRight() == NULL)
            {
                trackptr = findptr;
                break;
            }
            
            //goes on till the end
            if(findptr->getRight()->getRight() == NULL)
            {
                trackptr = findptr->getRight();
                break;
            }
            findptr=findptr->getRight();
        }
        
        //if the "to be deleted node" is on the left side of the parent pointer pointing to it
        if(trackPrevious->getLeft()==head)
        {
            //sets the left of the parent pointer to the tracking pointer  
            trackPrevious->setLeft(trackptr);
            if(trackptr != head->getLeft())
                trackptr->setLeft(head->getLeft());
            //sets the right to deleted nodes right
            trackptr->setRight(head->getRight());
            if(trackptr != findptr)
                //sets the left of the pointer pointing to the maxpointer to the left of the maxpointer(trackptr)
                findptr->setRight(trackptr->getLeft());

            head->setLeft(NULL);
            head->setRight(NULL);            
            delete head;
            head = NULL;
            return true;
        }
        //if the "to be deleted node" is on the right side of the parent pointer pointing to it
        else if(trackPrevious->getRight()==head)
        {
            //sets the right of the parent pointer to the tracking pointer  
            trackPrevious->setRight(trackptr);
            if (trackptr != head->getLeft())
                trackptr->setLeft(head->getLeft());
            //sets the right to deleted nodes right
            trackptr->setRight(head->getRight());
            if(trackptr != findptr)
                //sets the left of the pointer pointing to the maxpointer to the left of the maxpointer(trackptr)
                findptr->setRight(trackptr->getLeft());
            head->setLeft(NULL);
            head->setRight(NULL); 
            delete head;
            head = NULL;
            return true;
        }
        
    }
}

void TreeDB::clear()
{   
    //deletes the root
    //calls the destructor for tree nodes to take care of it
    delete root;
    root = NULL;
}


void TreeDB::printProbes() const
{
    //prints the number of probes when counted
    cout<<probesCount<<endl;
}


void TreeDB::countActive () const
{
    //counts the active number of nodes
    cout<< activeCount(root)<<endl;
}

ostream& operator<< (ostream& out, const TreeDB& rhs)
{

}

void TreeDB::printTree()
{
    //prints the tree using the help of a helper recursive function
    printall(root);
}

void TreeDB::printall(TreeNode* head)
{
    if(head == NULL)
        return;
    printall(head->getLeft());
    cout<<*(head->getEntry());
    printall(head->getRight());
    
}



bool TreeDB::insertTree(TreeNode* p, DBentry* r)
{
    if(p->getEntry()->getName() == r->getName()) return false; //Node already exists
    if(p->getEntry()->getName()>r->getName()) //Checks on the left side of the node through recursion
    {
        if(p->getLeft() == NULL) //base case when it reaches the leaf
        {
            p->setLeft(new TreeNode(r)); //creates a new Treenode
            return true;
        }
        else return insertTree(p->getLeft(), r); //goes on the left side 
    }
    if(p->getEntry()->getName()<r->getName()) //checks on the right side 
    {
        if(p->getRight()==NULL) //creates a node at the leaf
        {
            p->setRight(new TreeNode(r));
            return true;
        }
        else return insertTree(p->getRight(), r); //goes to the right
    }
}

