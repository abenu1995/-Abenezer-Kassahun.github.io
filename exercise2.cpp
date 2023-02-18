#include <iostream>

using namespace std;

int main(){

double sales = 95000;
cout << "Sales:$"<< sales<< endl;

const double statetaxrate = 0.04;
cout<<"State tax rate:$"<< sales*statetaxrate<<endl;

const double countytaxrate = 0.02;
cout<<"County tax rate:$"<< sales*countytaxrate<<endl;


const double totaltaxrate = statetaxrate+countytaxrate;
cout<<"Total tax rate:$"<<sales*totaltaxrate;  


 
return 0;
}