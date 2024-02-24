#include <stdio.h>

/* Chapter 10: Program Structure
    Subchapters: Executables and Linkage
   Pages: 189 - 192 */

extern void executables(void); // implicitly external linkage
/* extern */void linkage(void); // implicitly external linkage
static void _Static_func(void); // visibility is restricted to the file
/* extern */ void _Static_func(void); // "extern has no effect here, reduntant declaration"
static int k = 1;
extern int l = 1; // may produce a warning, but declaring file-scope variable with "extern" and initializing it is valid; it's identical to int l = 1;
//l = 0; // extern int l and l both refer to the same entity

/* perfectly valid: this will be be reeduced to 1 object */
int t = 1;
int t;

/* valid */
static int c;
extern int c = 1; // "extern" specifies that the object is defined somewhere else

/* invalid: mixing external and internal linkage is undefined behavior and will produce an error  */
// static int c = 1;
//  int c = 1; // do not mix static and external linkage

int main(void)
{
    executables();
    linkage();

}


void executables(void)
{
    /* As we know, after the compilation phase, there's the last stage - link phase
    Link phase takes object code (.o) of all translation units (including libraries)
    And link them together to form an executable */

    /* Instead of implementing the whole program logic in 1 source file, 
    Dividing your program into modules, and compiling them separatelyand then linking them 
    Allows you to compile certain modules that need updating and then linking them with
    the rest of the modules. */

    /* Benefits of dividing your program into dinstinct compilable modules are plenty:
        1) Makes code easier to maintain;
        2) Ensures encapsulation, promotes high cohesion and low coupling;
        3) Reduces compile time (you need to compile 1 module instead of many)
        4) Changes made in 1 module do not affect the rest of the modules */

    /* Libraries - a collection of sources files turned into executable components
    That cannot be executed on their own
    For example, glibc is a library that comes pre-built (no compilation needed) with implementation 
    To access public interface of glibc, we need to include its headers:
    <stdio.h>, <stdlib.h>, etc. 

    Libraries allow you to focus on the logic of your program while building your code
    On top of them */

    /* As with all executables, libraries are linked into your program 
    There are 2 kinds of libraries: static (or an archive .ar) and dynamic (shared dynamic object or .so)
    */

    /* 1) static library:
        - the whole code of the library is incorporated into your program at link time;
        - access to the library's interface if faster;
        - the size of the program is bigger; */

    /* 2) dynamic library:
        - can be loaded into the RAM once and used by all programs;
        - takes less space, promotes usage of only certain components;
        - can be installed separately from the program, thus not tied to the program release;
        - breaking changes are possible affecting other programs using the library;

        Shared objects are more popular.
    */
}

void linkage(void)
{
    /* linkage is the process of name/identifier/symbol resolution, identifying 
    whether the same identifier refers to the same entity across many source files, or within
    a particular file scope, or is unique within a block scope without "extern" specifier
    There are 3 kinds of linkage:
    1) external;
    2) internal;
    3) no linkage; */

    /* 3) no linkage refers to unique identifiers that are declared within the block scope and which have no "extern" keyword, nor they are externally linked */
    int a = 0;
    void (*func)(int a);
    void another_func(void);

    /* None of the objects are available outside the block scope of linkage() */
    /* Each instance of a unique object will be treated as a separate object, unless you declare it with "extern" specifier*/

    // int a; // the object with the same indentifier is redifined (error)

    /* Identifiers within block scope with "extern" keyword haave external linkage 
    Because "extern" here literally means "Defined somewhere else" */
    extern int l; // l here and l at the beginning are the same symbols
    printf("l=%d\n", l);
    // extern int la = 2; // using extern will produce an error, because we attempt to declare AND define/initialize 'la' within block-scope while it has to be defined within file-scope
    /* Initialization of declared object equals its definition (memory allocated for it) */

    /* 2. Internal linkage applies to objects decalred within file-scope with a "static" keyword
     objects with internal linkage are not visible outside the file scope.

    Static identifiers WILL refer to the same entity within file-scope unless a unique identifier with the same name is declared within block-scope
    Without specifier "extern"*/

    extern int k; // file-scope k and block-scope k refer to the same entity
    printf("k = %d\n", k);
    /* "Static" keyword at file-scope makes linkage internal while using it within block-scope denotes static storage duration and no linkage */

    static int f = 0; // initialized before before runtime, static storage duration without linkage (unique object)

    /* 3. external linkage applies to objects that can be referred to across many source files, potentially throughout the whole program
    "extern" explicitly makes linkage external. It also means "declare but not define" and "declaration and definition/initialization is somewhere else" within block scope

    Any identifier with external linkage will refer to as the same entity across the program

    At file-scope, declaring an object with "extern" and intializing it is the same as declaring an identifier which has implicit external linkage
    Succh objects, unless initialized, will be initialized to 0 */

    /* You can declare multiple global objects with external linkage with the same name, and they will be reduced to 1 object */

    /* Any object declared at file-scope with or without "extern" has implicit external linkage unless
    An object can have external linkage within block-scope if "extern" keyword is applied WITHOUT initializing it */

    extern int jj;
    /* Do NOT mix external and internal declarations (may lead to undefined behavior) */
    static int d = 0; // d does not have linkage, thus no reference
    // extern int d = 1; // Undefined, moreover, will not compile due to redifinition and defining extern varable within block scope
    extern int b;
}

