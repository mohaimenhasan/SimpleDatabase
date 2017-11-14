#include "DBentry.h"
#include <iostream>
#include <iomanip>
using namespace std; 


//sets default entry with default constructor
DBentry::DBentry()
{
    IPaddress = 0;
    active = false;
    
}


//modified constructor for setting DB entry based on the information provided
DBentry::DBentry (string _name, unsigned int _IPaddress, bool _active)
{
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}


//Default destructor for destructors
DBentry::~DBentry()
{
    
}


//sets the name of the entry
void DBentry::setName(string _name)
{
    name = _name;
}


//sets IP address
void DBentry::setIPaddress(unsigned int _IPaddress)
{
    IPaddress = _IPaddress;
}


//sets active or not
void DBentry::setActive (bool _active)
{
    active = _active;
}


//returns name
string DBentry::getName() const
{
    return name;
}

//returns IP address
unsigned int DBentry::getIPaddress() const
{
    return IPaddress;
}


//returns if entry is active or not
bool DBentry::getActive() const
{
    return active;
}

//Modified ostream operator to print DB entry
ostream& operator<< (ostream& out, const DBentry& rhs)
{
    string a;
    if(rhs.active) a  = "active";
    if(rhs.active == false) a = "inactive";
    out<<rhs.name<<" : "<<rhs.IPaddress<<" : "<<  a <<endl;
    return out;
}