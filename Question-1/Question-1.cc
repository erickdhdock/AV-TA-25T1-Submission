/// Question 1: This question requests you to fix all compile errors in the main function and any classes. Address
/// the comments given inside the code.
/// Your code should run and compile without any warnings or errors.


#include <iostream>
#include <map>
#include <vector>
#include <initializer_list>
#include <memory>
#include <cmath>


using namespace std; //a dded 

const int values[] = { 1,2,3,4,5 };
const int val_size = sizeof(values) / sizeof(int); // fixed here



class Foo {
    vector<int> mElements;
public:
    Foo(std::initializer_list<int> list)
    : mElements(list) {}
};

struct Person { // fixed here
    int age;
    float weight;
};


void show_output(const int** pp)
{
    printf("%p : %p : %d", pp, *pp, **pp);
}



int main() {

    int x = -10;
    int y = 15;
    cout << " " << /* (x,y) - ? */ y << endl;

    // print integer ratios of y:x till x < y
    // invalid ratios should print 0
    while (x < y)
    {
        if (x != 0)
            cout << "ratio: " << (y/x) << endl;
        else
            cout << "ratio: 0" << endl;
        x++;
        y--;
    }


    int i = 1, j = 1; // don't change values
    if ((i = !3) & (j = 1))
    {
        cout << "j is 1 and i is not 3\n";
    }
    else {
        cout << "either j is NOT 1, or i is set to 3\n";

    }


    typedef map<int, double> valmap;
    valmap m;

    for (int i = 0; i < val_size; i++)
        m.insert(make_pair(values[i], pow(values[i], .5)));

    m.insert(make_pair(1, 2));


    int n = 1;
    int* p = &n;
    const int * pp = p; // int* -> int** 
    show_output(&pp);

    // Initialise a person on the heap with the use of smart pointers (unique_ptr) instead.
    unique_ptr<Person> ptr = make_unique<Person>();
    ptr->age = 10;
    ptr->weight = 55.5;


    // Initialise with 5 integers
    Foo foo = { 1,2,3,4,5 };

    return 0;
}
