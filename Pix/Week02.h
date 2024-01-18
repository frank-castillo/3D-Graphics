#pragma once

// You dont need operator overloading to write good code
// every member function, it always takes a hidden parameter, a *this member, called the
// zero parameter, that is a pointer to the class and object calling the function
// 
// Member variables are what determine the size in memory
// We use the zero argument to determine and specify the object we are currently working on

// Operator overloading: trick compiler does so that you can write more mathematical looking
// code. You use an operator to use it as a function caller

// Self contain classes, so vector 3 only works with vector3
