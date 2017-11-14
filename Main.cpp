/* 
 * File:   Main.cpp
 * Author: khanmo87
 *
 * Created on November 16, 2016, 10:13 PM
 */

#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip> 
#include "TreeDB.h"
using namespace std;
/*
 * 
 */
int main() 
{
    //line to hold user input
    string line;
    //Command holder
    string command;
    
    //Creates a new Tree
    TreeDB* myTree = new TreeDB;
    
    //Key to hold name
    string key;
    
    //integer to hold IP address
    int ipAddress;
    
    //To hold active or not
    bool active;
    string activeOrNot;
    cout<<"> ";
    
    //gets user input
    getline (cin, line);
    while ( !cin.eof () )
    {
        stringstream lineStream (line); //Creates a new string stream to put the user input string in 
        lineStream >> command;
        
        //Insert command
        if (command == "insert")
        {
            
            lineStream >> key;
            lineStream >> ipAddress;
            lineStream >> activeOrNot;
            
            //sets the boolean variable based on active or not
            if(activeOrNot == "active")
                active = true;
            else if(activeOrNot == "inactive")
                active = false;
            
            //Creates a new Entry dynamically
            DBentry* newEntry = new DBentry (key, ipAddress, active);
            
            //checks if it already exists or not
            //inserts if it does not
            if(myTree->insert(newEntry) == false)
            {
                //deletes the entry if it does
                delete newEntry;
                newEntry = NULL;
                cout<<"Error: entry already exists"<<endl;
            }
            else
                cout<<"Success"<<endl;
        }
        
        
        //Find command
        else if (command =="find")
        {
            lineStream >> key;
            //checks if node exists or not based on the key(name) provided
            //returns NULL pointer if it doesn't exist
            DBentry* entry = myTree->find(key);
            if (entry == NULL)
                cout<<"Error: entry does not exist"<<endl;
            else
            {
                //overloaded operator for printing DBentry
                cout << *entry;
            }
        }
        
        //remove command
        else if (command == "remove")
        {
            lineStream >> key;
            //removes node
            //returns false if node doesn't exist
            if(myTree->remove(key))
                cout<<"Success"<<endl;
            else
                cout<<"Error: entry does not exist"<<endl;
        }
        
        //printall command
        else if (command == "printall")
        {
            
            //Prints the entire tree based on the function provided
            myTree->printTree();
        }
        
        //Prints the number of probes
        else if (command == "printprobes")
        {
            lineStream >> key;
            //checks if entry exists or not
            DBentry* entry = myTree->find(key);
            if (entry == NULL)
                cout<<"Error: entry does not exist"<<endl;
            //prints the probecount if entry exists
            else
                myTree->printProbes();
        }
        
        //removes all the nodes
        else if (command == "removeall")
        {
            myTree->clear();
            cout<<"Success"<<endl;
        }
        
        //counts the number of active nodes
        else if (command == "countactive")
        {
            myTree->countActive();
        }
        
        //updates status to active or inactive
        else if (command == "updatestatus")
        {
            lineStream >> key;
            string activeOrNot;
            lineStream >> activeOrNot;
            //sets active variable based on the entry provided
            bool active;
            if(activeOrNot == "active")
                active = true;
            else if (activeOrNot == "inactive")
                active = false;
            myTree->changeActive(active, key);
        }
        //Prints out invalid command otherwise
        //Not required for this lab
        else
            cout<<"Invalid command"<<endl;
        cin.clear();
        cout<<"> ";
        //Asks for a new input by the end of executing command function
        getline (cin, line);
        
    }
    
    //deletes the entire tree
    delete myTree;
    return 0;
}

