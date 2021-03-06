#include <iostream>
#include <stdexcept>

using namespace std;

// Write a try - catch block.
// Throws a bulit-in exception in the try block
// Catch it in the catch block and write it out.
// Don't forget includes

int main()
{
    try {

        int a = 4;
        int b = 1;

        if (!b)
            throw runtime_error ("You can not divide by zero.");
        else if (a == b)
            throw 'e';
        else if (b == 1)
            throw 1;
    } catch (...) {
        cout << "There was an error." << endl;
    }

	return 0;
}
