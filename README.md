# SimpleDatabase
1. Objectives
The objectives of this assignment are to provide you with more practice on the use of the
various C++ concepts/constructs introduced in the lectures so far, including classes, dynamic
memory allocation, pointers, I/O, and dynamic data structures. This will be done in the context
of implementing a binary search tree class.
2. Problem Statement
In this assignment, you will implement a simple database to store and retrieve data. You are
creating a simple “domain name server” – a database that can rapidly look up string names,
such as www.google.com, and return a 32-bit integer that is the Internet Protocol (IP)
address corresponding to that “domain name”. This is the function performed by the domain
name servers that allow you to type in easy to remember website names and have your web
browser automatically go to the correct IP address (computer) to retrieve the web data.
You will implement three classes: DBentry, TreeNode and TreeDB. The DBentry
class will be used to create objects that hold an entry of the database. Each entry has a key (a
string, corresponding to the name of the internet domain) and some data (a 32-bit integer that
gives the IP address and a boolean flag that indicates whether the computer at that IP address is
active or not). The TreeDB and TreeNode classes will be used to create a binary search tree
database of DBentry objects. TreeDB represents the entire binary tree, while each
TreeNode represents a single node in the tree.
In a real domain names server, we would have to rapidly search billions of domain names
(strings) as we looked for the IP address corresponding to a name. The fact that a binary search
tree can find entries in large datasets very efficiently, and can also add new entries efficiently,
makes it a very appropriate data structure for this application.
2. Command and Output Specification
Your database will be exercised by a simple parser. Whenever the parser expects the user to
enter a command, it should prompt the user for input by outputting a greater than sign followed
by a space:
> user input would appear here
The parser reads commands from cin, calls the appropriate TreeDB and DBentry functions,
and sends the appropriate output to cout. Each command consists of an operation, followed by
zero or more arguments. The command and the arguments are separated by white spaces, and
will always appear on the same line. You parser should process commands until the end-of-file
(eof) is encountered. You may assume that all the input is syntactically correct – your
program will not be tested with invalid commands, the wrong number of arguments, or misspelt
ECE 244 – Fall 2016 Page 2 of 12
arguments. The only error messages you need to generate are those listed below. The
commands and their parameters are:
insert name IPaddress status. This command creates a new entry with name
(a string) as the key and IPaddress (a non-negative integer) and status (active or
inactive) as specified. You may assume that the name, IPaddress, and active
arguments are separated by spaces and that there are no spaces within an argument. The
new entry is then inserted into the database. If there already exists an entry with the
same key, the error message “Error: entry already exists” is printed to
cout. Otherwise “Success” is printed.
find name. This command finds the entry with the key name in the database, and prints
its contents to cout as name : IPaddress : status. Name and IPaddress are
printed as a string and an unsigned integer, respectively, while status is either active
or inactive. Between values a space, colon and space should be printed.
If no such entry exists, the error message “Error: entry does not exist” is
printed to cout.
remove name. This command deletes the entry with the key name from the database. If
no such entry exists, the error message “Error: entry does not exist” is
printed to cout. Otherwise “Success” is printed.
printall. This command prints all the entries in the database, sorted in ascending order
of keys, one entry per line.
printprobes name. This command finds the entry with the key name in the database.
If no such entry exists, the error message “Error: entry does not exist” is
printed to cout. Otherwise, the number of probes (DBentries examined during the tree
search) is printed to cout.
removeall. This command deletes all the entries in the database, returning it to the
empty state. When done, “Success” is printed.
countactive. This command counts the number of entries in the database that are active
and prints this count to cout.
updatestatus name status. This command updates the status of the entry with
the given name; status must be either active or inactive. If no entry with name
exists, the error message “Error: entry does not exist” is printed to cout.
Otherwise “Success” is printed.
The following is an example of commands and their outputs. The example assumes an empty
database at the beginning.
> insert www.google.com 283983 active
Success
> insert www.yahoo.com 191333 active
Success
> insert www.eecg.utoronto.ca 179333 inactive
Success
> insert www.altera.com 283299 active
Success
> find www.google.com
ECE 244 – Fall 2016 Page 3 of 12
www.google.com : 283983 : active
> updatestatus www.google.com inactive
Success
> printall
www.altera.com : 283299 : active
www.eecg.utoronto.ca : 179333 : inactive
www.google.com : 283983 : inactive
www.yahoo.com : 191333 : active
> printprobes www.altera.com
3
> remove www.eecg.utoronto.ca
Success
> printprobes www.altera.com
2
> countactive
2
> printall
www.altera.com : 283299 : active
www.google.com : 283983 : inactive
www.yahoo.com : 191333 : active
> removeall
Success
> find www.google.com
Error: entry does not exist
> printall
> (Ctrl+D)
