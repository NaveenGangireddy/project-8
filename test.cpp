#include <iostream>
using namespace std;

class A
{
        private:
                int var;
        public:
                A(){
                        var=3;
                }
                void operator +(A a);
};
void A::operator + (A a)
{
        cout<<"Result = "<<a.var+var<<endl;

}

int main()
{
        cout<<"Sample Programm for Testing.."<<endl;
        
	A a1;
        A a2;
        a1+a2;
	cout<<"Hey CHEkitasssssssss gumastasssssssss...."<<endl;
        return 0;
}

