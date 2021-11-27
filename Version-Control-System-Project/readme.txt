MiniGit Project Functionality 
Didi Trifonova
April 27, 2021 

At the beginning of the program the user will be prompted to decide if they would like to initialize a git repository
(1) Yes - Creates ".miniGit" subdirectory to keep track of file version
(2) No - exits program

Next they will be promted to choose from 5 menu options
(1) Add
    (a) User will be prompted for a filename that they would like to add 
    (b) First check if the file exists in the directory, if not then returns to menu choices
    (c) Next it will traverse the most recent SLL to check if the filename is added
    (d) If added it will return to menu, if not, a new SLL node will be added to the most recent DLL node
(2) Remove
    (a) Prompts user for filename
    (b) Checks to make sure filename exists in most recent SLL
    (c) If found, SLL node is deleted
(3) Commit
    (a) Checks whether fileVersion exists in ".miniGit" 
    (b) If it doesnt then it gets copied into the repository
    (c) If it does exist then it checks for changes between repository and current directory
    (d) If changes exist then the fileVersion is incremented and copied to repository
    (e) If a change to the .MiniGit repository was made then a new DLL node is added with incremented commit number
    (f) Finally a deep copy of the SLL list is added to the new DLL node
(4) Checkout
    (a) Prompts user for commit number they wish to checkout 
    (b) While traversing SLL, current files are overwritten using selected commit num
(5) Print commit info
    (a) Prompts user for a commit number
    (b) Prints the SLL associated with that commit 
(6) Quit
    (a) Exits program