# C++ Coding Convention

- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [Naming Convention in C++](https://www.geeksforgeeks.org/naming-convention-in-c/)

## Contents

1. [The `#define` Guard](#the-define-guard)
2. [Local Variables](#local-variables)

## Naming Convention

### Class and Class Attributes Names

- The class name should be a noun.
- Use upper case letters as word separators, and lower case for the rest of the word.
- The first character in the class name must be in upper case.
- No underscores (`_`) are permitted in the class name.

```c++
class PascalCase
{
public:
    void camelCase();
    int perimeter;

private:
    int mLength;
    int mWidth;
    int mCamelCase;
}

struct PascalCase
{
    int x;
    int y;
};
```

### Function

```c++
void camelCase();
```

### Variables

```c++
// Common
int var;
int snake_case;

// Pointer
int *var;
int *snake_case;

// Constant
const double UPPER_CASE = 1.23;

// Class variable
int mCamelCase;
```

### File Name

```c++
// Class
PascalCase.cpp
PascalCase.h

// Others
snake_case.cpp
snake_case.h
```

## The `#define` Guard

All header files should have #define guards to prevent multiple inclusion. The format of the symbol name should be <PROJECT>_<PATH>_<FILE>_H_.

To guarantee uniqueness, they should be based on the full path in a project's source tree. For example, the file foo/src/bar/baz.h in project foo should have the following guard:

---
```c++
#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_

...

#endif  // FOO_BAR_BAZ_H_
```
---

## Local Variables

Place a function's variables in the narrowest scope possible, and initialize variables in the declaration.

C++ allows you to declare variables anywhere in a function. We encourage you to declare them in a scope as local as possible, and as close to the first use as possible. This makes it easier for the reader to find the declaration and see what type the variable is and what it was initialized to. In particular, initialization should be used instead of declaration and assignment, e.g.,:

---
```c++
int i;
i = f();      // Bad -- initialization separate from declaration.
```
```c++
int i = f();  // Good -- declaration has initialization.
```
---
```c++
std::vector<int> v;
v.push_back(1);  // Prefer initializing using brace initialization.
v.push_back(2);
```
```c++
std::vector<int> v = {1, 2};  // Good -- v starts initialized.
```
---
Variables needed for `if`, `while` and `for` statements should normally be declared within those statements, so that such variables are confined to those scopes. E.g.:

```c++
while (const char* p = strchr(str, '/')) str = p + 1;
```
---
There is one caveat: if the variable is an object, its constructor is invoked every time it enters scope and is created, and its destructor is invoked every time it goes out of scope.

```c++
// Inefficient implementation:
for (int i = 0; i < 1000000; ++i) {
Foo f;  // My ctor and dtor get called 1000000 times each.
f.DoSomething(i);
}
```

It may be more efficient to declare such a variable used in a loop outside that loop:

```c++
Foo f;  // My ctor and dtor get called once each.
for (int i = 0; i < 1000000; ++i) {
f.DoSomething(i);
}
```
---
**Last Updated:** 24.07.29
