#include <iostream>


int x = 1;
struct S{
    /*
     * ++X is the prefix increment operator,
     * this means that the value of x is first incremented and then used in the program
     */
    int n = ++x;
    S(){}               //uses default member initializer.
    S(int arg): n(arg) {} //use member initializer.

};
/*
 * If a member has default member initializer and also appears in the member initialization list in a constructor,
 * the default member initializer is ignored for that constructor.
 */
int main() {
    std::cout<<x<<'\n';
    S s1;
    std::cout<<"s1.n: "<<s1.n<<'\n';
    std::cout<<"x: "<<x<<'\n';
    S s2(7);

    std::cout<<x<<'\n';


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
