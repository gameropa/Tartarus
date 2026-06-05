# Specific Styling Rules for C

## General Style

### Braces

We generally use the K&R style for braces. The only exceptions are functions, where we use the allman style.

For Example:

```c
int add(int a, int b)
{
        return a + b;
}
```

Everywhere else we use the K&R style:

```c
/* Structs */
struct A {
        int b;
};

/* Loops */
for (int i = 0; i < 3; ++i) {
        arr[i] *= 2;
}
```

If the control structure has only one line, we don't need braces necessarily.

```c
if (ptr == NULL)
        return false;
```

## Special Styling Guidelines

- **Don't use `typedef struct`:** Because we want to know, which datatype the variable or function parameter is, write the standard definition for structs:

```c
struct Vec3 {
        float x, y, z;
};
```

- **Don't use double slash comments (`// Comment`) for oneliner:** Use only block comments for your c code:

```c
/* One line comment. */

/*
 * This is a multi line
 * block comment.
*/
```

## Documentation

Use Doxygen documentation for your code, since it is the de-facto standard for c.
You don't have to document every function or makro. Small helper functions or makros which are only used by one file are excepted.

The documentation looks like this:

```c
/**
 * @brief This functions multiplies a and b.
 *
 * @param a     First parameter.
 * @param b     Second parameter.
 * @return int  Result of multiplication (product).
 */
int mult(int a, int b)
{
        return a * b;
}
```
