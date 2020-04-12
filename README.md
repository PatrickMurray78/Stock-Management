# Stock Management
Stock Management is an Advanced Procedural Programming Assignment for second year.

## About
Stock Control International Ltd currently manually store company stock records but have 
requested you to develop a new stock management application for them. 
 
The application will create a database which will store the details of all the stock items held 
by the company.  In addition to storing all the stock data the application should allow overall 
stock statistics to be generated. 
 
The Database will be implemented as a linked list and will have the ability to
save, restore, retrieve, add, delete and update stock details.

## Requirements
1. "login.txt" must have at least one username and password to allow
user to login.

## Usage(Summary)
1. User is prompted to enter a username, followed by a password.
2. Once login credentials has been validated, the menu is displayed along with a header.
3. The user has 8 options to choose from or can choose -1 to exit and save the current database.

## Usage
- When the program starts `initLogin()` is called from `Main.c` and initiates the login process by opening the "login.txt" file and adding each username and password to the `Login` struct linked list.
- `login()` is called by `initLogin()`, the purpose of this function is to ask the user for a username and password. The function iterates through the `Login` linked list and checks to find a matching username. If found, the password is then validated by comparing it against the node with the matching username. If the password doesnt match, the user is notified and is asked to enter a username and password until the correct credentials are entered. User is then brought back to `Main.c`.
- `init()` is then called by `Main.c`, this function simply checks "database.txt" to check if there is any saved stock items, if there is this function simply adds the first stock item to the database.
- The next function called is `fillDatabase()`, this is also called from `Main.c` and iterates through the rest of the file, disregarding the first stock item and adding each stock item thereafter to the database at the end.
- After the database has been filled with existing data, the main menu loop commences. The main loop has 8 options to choose from.
 1. Add Stock Item
 2. Display all Stock Items
 3. Display Stock Item
 4. Update Stock Item
 5. Delete Stock Item
 6. Generate Statistics
 7. Create Report
 8. List Stock Items in order of Monetary Value
 
- There is input validation on every input entered, the options in the menu work as follows

## Add Stock Item
If the database is empty, we call `addItemAtStart`. If the database is not empty we call `addItemAtEnd`.
For both of these functions, the user is prompted to enter the new stock details which has input validation for each input. The only difference between these functions is how the `newNode` is added to the database.

## Display All Stock Items
This function simply displays all contents of the database to the user. It does so by iterating through the database and for each node, it displays the corresponding formatted details to screen.

## Display Stock Item
The user is prompted with a menu asking the user if they would like to search by Stock Item Number or Stock Item Name.
The user is then prompted to enter the number or name they wish to search for.
If found, the details of the stock item are displayed to screen and function exits.

## Update Stock Item
The user is prompted with a menu asking the user if they would like to search by Stock Item Number or Stock Item Name.
The user is then prompted to enter the number or name they wish to search for.
If found, the user is then prompted to update the Stock Item Supplier Name, Stock Item Supplier Contact Number and the Re-order threshold limit.

## Delete Stock Item
The user is prompted to enter a stock item number to delete.
If found, the stock item is deleted from the start, the end or somewhere in between depending on which conditions were met.

## Generate Statistics
The user is prompted with a menu with three options.
 1. A. % of stock items below the re-order threshold limit.
 2. B. % of stock items below twice the re-order threshold limit.
 3. C. % of stock items above twice the re-order threshold limit.
 
Once the user has selected an option they are then prompted to enter the department they wish to generate the statistics for.

## Create Report
When this function is selected by the user, "report.txt" is opened.
Every stock item in the database is formatted and output to the report file.
Finally the three statistic options are generated for each department at the botto of the file.
This file is then closed and saved.

## List Stock Items in order of Monetary Value
The `stockInOrder()` function iterates through the database once for each stock item in the database.
The highest value is the first one found, this is then output to screen.
Through each subsequent iteration, the next highest is found and output to screen using numerous if/else's and certain conditions.
This continues until the full database has been sorted.

## Exit
Once the user enters -1 in the menu, `saveDatabase()` is then called. 
This function saves all contents of the database to a save file called "database.txt".
A goodbye message is then displayed, before the program exits.

## Design Decisions
Throughout my development of this project, there were numerous design decisions I made.
- I chose to use two header files, `login.h` and `database.h`.
- I used three `.c` files, `login.c`, `database.c` and `main.c`.
- I found that by splitting my code into three main areas, it really helped keep a nice structure throughout.
- The user's experience was something I took into account through every aspect of the program. I made the program as user friendly as I could with appropriate headers and a well structured output.
- I was unable to merge `addItemToStart()` and `addItemToEnd()` due to temp always being null when adding item to the end after adding an item to the start.
- When adding to the end, `isUnique()` is called to ensure the stock item number is unique. I chose to create a function for this as it made my code neater and it was easier to see what was going on inside `addItemAtEnd()` when all this code was elsewhere.
- I created another function called `createStrings()` which takes in multiple char arrays as parameters along with temp. I chose to use numbers for some of the variables inside the `Database` linked list, this made it easier to work with the numbers. So, when I was outputting to the user these numbers I used needed to be converted to strings using ultiple if/else statements. This made the output much easier to read and understand. This function is called by three other functions so it made a lot more sense to create a seperate function, rather than using duplicated code in these three functions.
- I believe if you have never used this program before, you would have no issue in using this program for the first time due to how user friendly this program is.