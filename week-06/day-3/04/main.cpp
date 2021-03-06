// Create a class called ParentClass. It should have two public functions. Both return a string. One virtual, the other not.
// Each should return a unique string.
// Create a ChildClass which inherits from the ParentClass publicly.
// This should override both functions. The virtual and the nonvirtual one both.
// These should return unique string again.
//
// Create a main() function. In this function, create a ParentClass* pointer and instanciate a ChildClass member for that pointer.
// Hint: This should look something like this: ParentClass* a = new ChildClass();
// Print out the result of both functions on this a pointer.
// Print out the result of both functions if You first cast pointer a to be interpreted as of type ChildClass*
#include "parentclass.h"
#include "childclass.h"

int main()
{
    ParentClass *p = new ChildClass();

    cout << p->where_am_i();
    cout << p->who_am_i();

    cout << ((ChildClass*)p)->where_am_i();
    cout << ((ChildClass*)p)->who_am_i();

    return 0;
}
