#include <iostream>
#include <algorithm>

#include <string>
#include <vector>

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

struct templateA{
    templateA() = default; //This way constructor format ok.
    explicit templateA(int v) : v(v) {} // also ok format.
    const int&  v=42; //default value.
};
//
struct Foo;
struct templateB
{
    //The static keyword is only used with declaration of a static member, inside the class definition,
    //but not with the definition of static member.
    static int a[];  //declaration, incomplete type.
    static Foo x;   //declaration, incomplete type.
    static templateB tempB;     //declaration, incomplete type. (inside it's own definition.)
};
int templateB::a[10]; //definition, complete type.
struct Foo {};
Foo templateB::x;   //definition, complete type.
templateB    templateB::tempB;     //definition, complete type.

//-------------------------------------------------------
// https://www.stroustrup.com/bs_faq2.html#in-class
class inClassConstant{
public:
    /*
     * Inside a class definition, the keyword static declares members that are not bound to class instances.
     * Also the members's value can be changed.
     */
    static const int c7 = 31;
    static  int c6;
};
//the class self property.
const int inClassConstant::c7;
int inClassConstant::c6 = 11;
int inClassConstantF() {
    //undefined reference to `inClassConstant::c6'
//    const int* p1 = &inClassConstant::c6; // error: c6 not an lvalue
    const int* p2 = &inClassConstant::c7;
    return  *p2;
}
//---------------DECLARE THE EXPLICIT CONSTRUCTOR -----------------------
//https://www.stroustrup.com/bs_faq2.html#explicit-ctor
struct Point{
    int x,y;
    explicit Point(int xx =0, int yy=0) :x(xx), y(yy) {}
};
void f(Point);
void g()
{
    Point orig;
    Point p1(2); //explicit call of constructor. yy is 0.
//    f(2); //error: could not convert '2' from 'int' to 'Point'
    Point p3 = Point(2);
    std::cout<<"explicit conversion. p3.x = "<<p3.x<<"  p3.y = "<<p3.y<<".\n";
}
//--------------------------THIS POINTER--------------------------------------------
class thisPointerClass{
public:    int x;
    void foo(){
        x = 6;
        this ->x = 5;
    }
    void foo() const {}

    void foo(int _x) {
        this->x = _x;
    }
    int y;

    explicit thisPointerClass(int x) : x(x), //uses parameter x to initialize member x
                y(this->x) {}   //use member x to initialize y

    thisPointerClass& operator= (const thisPointerClass& b)
    {
        x = b.x;
        return *this;
    }

};
//--------------------------THIS POINTER END---------------------------------------------
struct Printer{
    std::ostream& os;
    explicit Printer(std::ostream& os) :os(os) {}

    template<typename T>
    void operator() (const T& obj) {
        os<<obj<<' ';
    }
};
void member_templates()
{
    std::vector<int> v = {1,2,3};
    std::for_each(v.begin(), v.end(), Printer(std::cout));
    std::string s {"hello!"};
    std::ranges::for_each(s,Printer(std::cout));
}

struct class_Bit_field{
    /* Declares a class data member with explicit size, in bits.
     *
     */
    unsigned int b = 3;
};
void f_class_Bit_field()
{
    class_Bit_field c = { 6 };
    ++c.b; //7
    std::cout<<"Now unsigned int b =" <<c.b<<'\n';
    ++c.b;//8 does not fit, will return to 0.
    std::cout<<"unsigned int b = "<<c.b<<'\n';
}

int main() {
    member_templates();
    f_class_Bit_field();
    thisPointerClass t1(19);
    std::cout<<"t1.x= "<<t1.x<<'\n';

    inClassConstant i1;
    i1.c6 = 89;
    std::cout<<"i1.c6 value now "<<i1.c6<<'\n';
    std::cout<<"In class constant demo: "<<inClassConstantF()<<'\n';
    std::cout<<"Calling Point explicit construct> ";
    g();
    //
    templateA a2{};
    std::cout<<a2.v<<'\n';
    std::cout<<'\n';
//    std::cout<<a2.v;
    std::cout<<"original x value: "<<x<<'\n';
    S s1;
    std::cout<<"s1.n: "<<s1.n<<'\n';
    std::cout<<"x: "<<x<<'\n';
    /*
     * If a member has default member initializer and also appears in the member initialization list in a constructor,
    * the default member initializer is ignored for that constructor.
    */
    S s2(7);
    std::cout<<x<<'\n';


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
