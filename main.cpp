#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
/*
 * struct inheritance format

    struct A { };
    struct B : A { };
    struct C : B { };
 */

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
//    VirtualFunction(2); //error: could not convert '2' from 'int' to 'Point'
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
    //todo it failed.
    std::cout<<"unsigned int b = "<<c.b<<'\n';
}


//-----------------------USING DECLARATION-----------------------------------------------------------------
/*
 * IF the derived class name already have a member with same name, parameter list, and qualifications,
 * the derived class member hides or overrides(doesn't conflict with) the member that
 * is introduced from the base class.
 */

struct struct_using_declaration{
    virtual void VirtualFunction(int) {std::cout << "struct::VirtualFunction Called now.\n";}
    void g(char) {std::cout<<"struct::g\n";}
    void Non_Virual_Function(int) {std::cout << "struct::Non_Virual_Function Called\n";}

protected:
    int m; //struct::m is protected.
    typedef int value_type;
};

struct inherit_struct_using_declaration : struct_using_declaration{
    using struct_using_declaration::m;
    using struct_using_declaration::value_type;

    using struct_using_declaration::VirtualFunction;
    void VirtualFunction(int) override  {std::cout << "inherit_struct_using_declaration::VirtualFunction\n";}

    using struct_using_declaration::g;
    void g(int) {std::cout<<"inherit_struct_using_declaration::g\n";}

    using struct_using_declaration::Non_Virual_Function;
    void Non_Virual_Function(int) {std::cout << "inherit_struct_using_declaration::Non_Virual_Function Called\n";}
};
//---------------------------------------------------------------------------------------------

struct Class_Non_static_member_function{
    int data;
    Class_Non_static_member_function(int val);
    explicit Class_Non_static_member_function(std::string str);

    //const member function (definition).
    virtual int getData() const { return data;}
};
Class_Non_static_member_function::Class_Non_static_member_function(int val) :data(val) {
    std::cout<<"Constructor1 called, data = " << data <<'\n';
}

//Constructor with catch clause.
Class_Non_static_member_function::Class_Non_static_member_function(std::string str) try : data(std::stoi(str))
{
    std::cout<<"Constructor2 called, data = "<< data <<'\n';
}
catch (const std::exception&) {
    std::cout<<"Constructor2 failed, string was = " <<str<<'\n';
    throw;
}

struct Derived_Class_Non_static_member_function:Class_Non_static_member_function
{
    int data2;
    explicit Derived_Class_Non_static_member_function(int v1,int v2=11):Class_Non_static_member_function(v1),data2(v2) {}

    int getData() const override { return data * data2;}

    Derived_Class_Non_static_member_function& operator= (Derived_Class_Non_static_member_function other) &
    {
        std::swap(other.data, data);
        std::swap(other.data2,data2);
        return *this;
    }
};


//todo const- and volatile-qualified member functions
//file:///C:/Users/JIAN%20HE/Downloads/html-book-20220201/reference/en/cpp/language/member_functions.html

int main() {

    Derived_Class_Non_static_member_function d1(2);
    std::cout<<"1. d1.getData(): "<<d1.getData()<<'\n';

    Class_Non_static_member_function s2("2");


    try {
        Class_Non_static_member_function s3("NOT a Number");
    }
    catch (const std::exception&) {}
    std::cout<<"Class_Non_static_member_function.getData(): "<<s2.getData()<<'\n';
    Derived_Class_Non_static_member_function d2(3,4);

    d2 = d1;

    std::cout<<"Now Derived_Class_Non_static_member_function d2.data2:" <<d2.data2<<", d2.data: "<<d2.data<<'\n';

    std::cout<<"Now test for Derived_Class_Non_static_member_function.getData = data * data2 is true=  "<<d2.getData()<<'\n';







//    inherit_struct_using_declaration i;
//    struct_using_declaration& s = i;
////    i.m = 1;
//    s.VirtualFunction(1);
//    i.VirtualFunction(1);
//    i.g(1); // call derived int
//    i.g('A'); //call base g(char).
//    std::cout<<'\n';
//    i.Non_Virual_Function(1);
//    s.Non_Virual_Function(1);
//    member_templates();
//    f_class_Bit_field();
//    thisPointerClass t1(19);
//    std::cout<<"t1.x= "<<t1.x<<'\n';
//
//    inClassConstant i1;
//    i1.c6 = 89;
//    std::cout<<"i1.c6 value now "<<i1.c6<<'\n';
//    std::cout<<"In class constant demo: "<<inClassConstantF()<<'\n';
//    std::cout<<"Calling Point explicit construct> ";
//    g();
//    //
//    templateA a2{};
//    std::cout<<a2.v<<'\n';
//    std::cout<<'\n';
////    std::cout<<a2.v;
//    std::cout<<"original x value: "<<x<<'\n';
//    S s1;
//    std::cout<<"s1.n: "<<s1.n<<'\n';
//    std::cout<<"x: "<<x<<'\n';
//    /*
//     * If a member has default member initializer and also appears in the member initialization list in a constructor,
//    * the default member initializer is ignored for that constructor.
//    */
//    S s2(7);
//    std::cout<<x<<'\n';


    return 0;
}
