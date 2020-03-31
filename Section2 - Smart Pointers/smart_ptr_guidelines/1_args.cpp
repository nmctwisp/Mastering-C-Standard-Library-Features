#include <memory>

// Mutating an object: pass-by-reference
void f0(int&);

// Observing an object: pass-by-reference
void f1(const int&);

// Mutating a smart pointer: pass-by-reference.
void f2(std::unique_ptr<int>&);
void f3(std::shared_ptr<int>&);
void f4(std::weak_ptr<int>&);

// Observing a smart pointer: pass-by-reference.
void f5(const std::unique_ptr<int>&);
void f6(const std::shared_ptr<int>&);
void f7(const std::weak_ptr<int>&);

// Transfering ownership: pass-by-value
void f8(std::unique_ptr<int>);

// Sharing ownership: pass-by-value
void f9(std::shared_ptr<int>);

// WHEN YOU DO NOT CARE ABOUT THE OWNERSHIP AND ONLY CARE ABOUT THE VALUE
// THAT A RAW POINTER IS POINTING TO

// Mutating an optional object: pass-by-raw-pointer
void f10(int*);

// Observing an optional object: pass-by-raw-pointer
void f11(const int*);