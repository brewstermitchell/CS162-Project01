// CS162 Project 1
// Brewster Mitchell
// 10/3/2016
// Project 1: Simple Shopping Cart
// 	A simple shopping cart for tracking total cost of items versus a budget.
//	Current functionality does not include the option to remove items from cart.
//	Currently does not print the items in the cart.
// Sources: none

// includes
# include <iostream>
# include <iomanip>

using namespace std;

// declare constants
const int N_OF_ELEMS = 1000; // accounts for huge shopping trips
const int MAX_CHAR = 64; // max length of char arrays

// define structs
struct shoppingCart 
{ // contains arrays of cart items and their costs
	int numberOfItemsInCart = 0; // counter to track length of list
	double cartTotal = 0.0;
	char itemsInCart[N_OF_ELEMS][MAX_CHAR]; // array of items in the cart, to be used at a later date to print items at checkout.
	double pricesInCart[N_OF_ELEMS]; // array of prices of items in the cart
}; // end init

// function prototyping
double cleanInputToDouble(); // get money input from user and check for garbage. Return double.
int cleanInputToInteger(); // get integer input from user and check for garbage. Return integer.
void clearInputStream(); // clean input stream to prep for next input. Defined function since it is used many times throughout.

// main function
int main() 
{
	// format output stream for currency (USD)
	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::showpoint);
	cout.precision(2);

	// variable declarations
	double budgetTotal = 0.0;
	char nameToAdd[MAX_CHAR];
	double priceToAdd = 0.0;
	int numberOfItem = 0;
	char userYesNo; 
	
	// init struct for shopping cart
	shoppingCart newCart;

	// Print welcome message at start of program
	cout << "--------------------" << endl << "Simple Shopping Cart" << endl << "--------------------" << endl;
	
	// get budget and echo to user
	cout << endl << "Enter your shopping budget for today: $";
	budgetTotal = cleanInputToDouble();
	cout << endl << "Great! Your total budget is $" << budgetTotal << "." << endl;

	// start adding items
	cout << endl << "Let's get started." << endl;
	
	while (true)
	{  // loop until exit condition is met (user inputs 'Q' or 'q' for item name.
		// print total number of items in cart and remaining budget.
		cout << "You have " << newCart.numberOfItemsInCart << " items in your cart and a total remaining budget of $" << budgetTotal - newCart.cartTotal << "." << endl;

		// get item information from user
		cout << "Please enter the name of your next item (or Q to check out and quit): ";
		cin.get(nameToAdd, MAX_CHAR, '\n');

		if (nameToAdd[1] == '\0' && (nameToAdd[0] == 'Q' || nameToAdd[0] == 'q')) // check if input is only 'Q' or 'q', and if true, break loop
		{
			break;
		}

		else
		{
			cout << endl << nameToAdd << " is an interesing choice..." << endl;
		}

		// clear input stream
		clearInputStream();

		// get cost of item entered (no quitting now!)
		cout << "Please enter the price of each " << nameToAdd << " (no $ sign): ";
		priceToAdd = cleanInputToDouble();
		cout << endl;

		// get number of that item user is purchasing
		cout << "Enter quantity: ";
		numberOfItem = cleanInputToInteger();
		
		// display total cost of items, remaining budget after purchase, and determine if add to cart based on user response
		cout << endl << "The total cost of " << numberOfItem << " of " <<  nameToAdd << " is $" << priceToAdd * numberOfItem << "." << endl;
		cout << "This would leave you with $" << budgetTotal - newCart.cartTotal - (priceToAdd * numberOfItem) << " remaining." << endl;
		cout << "Add item(s) to cart? (Y/N): ";
		cin >> userYesNo;
		clearInputStream();

		if (userYesNo == 'Y' || userYesNo == 'y')
		{	
			// add items to cart, updating total number of items and cart total
			cout << endl << "Adding items to cart..." << endl;
			for  (int i = 0; i < numberOfItem; ++i)
			{ // add names of items for later enhancement to print cart contents by name
				for (int x = 0; x < sizeof(nameToAdd); x++)
				{ // add name of item to 2D array of names of items in cart.
					newCart.itemsInCart[newCart.numberOfItemsInCart][x] = nameToAdd[x];
				}
				newCart.pricesInCart[newCart.numberOfItemsInCart] = priceToAdd;
				newCart.cartTotal += priceToAdd;
				newCart.numberOfItemsInCart++;
			}

			
		}

		else if (userYesNo == 'N' || userYesNo == 'n')
		{
			continue; // return to beginning of loop to give user option to total and exit.
		}

		else
		{
			cout << "You didn't enter Y or N. Let's start over." << endl;
		}

	}

	// check out. Print individual prices and total
	cout << endl << "Checking out. Here's a list of the prices of each item you've entered:" << endl;
	for ( int i = 0; i < newCart.numberOfItemsInCart; ++i)
	{
		cout << "Item #" << i + 1 << ": $" << newCart.pricesInCart[i] << endl;
	}

	cout << "Your total cost today is $" << newCart.cartTotal << ". You saved $" << budgetTotal - newCart.cartTotal << "." << endl;
	cout << "Hope that's a positive number!" << endl << "Goodbye!" << endl;

	// end program
	return 0;
	
}

double cleanInputToDouble()
{
	double userInput = 0.0;
	cin >> userInput;

	while (!cin)
	{
		clearInputStream();
		cout << endl << "Couldn't read a dollar amount. Please enter a dollar amount without dollar sign." << endl;
		cout << "Please try again (no $ sign): ";
		cin >> userInput;
	}

	clearInputStream();
	
	return userInput;
}

int cleanInputToInteger()
{
	int userInput = 0;
	cin >> userInput;

	while (!cin)
	{
		clearInputStream();
		cout << endl << "Couldn't get a proper quantity. Please enter a valid number: " ;
		cin >> userInput;
	}

	clearInputStream();

	return userInput;
}

void clearInputStream()
{
	cin.clear();
	cin.ignore(100, '\n');
}
