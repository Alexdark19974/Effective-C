#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Chapter 2: Object, Functions, and Types
        Subchapter: Tags
    Pages: 30 - 3
*/

void tags(void);
void typedefs(void);
void self_referential_structs(void);

int main(void)
{
    tags();

    return EXIT_SUCCESS;
}

struct s { // s is a tag
    char buf[128];
};

void self_referential_structs(void)
{
    /* Self-referential structures do require tags */
    struct tnode {
        int count;
        /* you can't omit the tag because the structure has not been declared yet */
        struct /*tnode*/ tnode *left; // if you comment out "tnode", a warning will be generated
        struct tnode *right;
    };

    /* Declare typedef tnode to be used as a type name later */
    typedef struct treenode {
        int count;
        struct treenode *left;
        struct treenode *right;
    } tnode;

    tnode node; // now you can use type name;

    /* If you really want to use typenames inside struture definition */
    /* First define typedef for structure and its tag, then apply to self-referential members */
    typedef struct Tnode Tnode;
    struct Tnode {
        int count;
        Tnode *left;
        Tnode *right;
    };

    // struct Treenode Node; // error
    struct Treenode;
    // struct Treenode Node; // error: incomplete type (incomplete declaration of struct)
    struct Treenode {
        int data;
    };
    struct Treenode Node; // OK
}

void typedefs(void)
{
    typedef struct ss { int x; } t; // t is an alias for struct ss

    /* anonymous/tagless structs/unions are fine too */
    typedef struct { int x; } f;
    typedef enum { Jan, Feb } Month;

    /* when typedef is applied to function declaration, readability is improved too */
    // function type that points to void (*)(int)
    typedef void fv(int);
    // function pointer type that points to void (*)(int);
    typedef void (*pfv)(int);

    /* 1) function signal that accepts 2 params: int and a pointer to a function 
     * That accepts param int and returns nothing;
     * 2) function signal returns pointer to a function that accepts param int 
     *    And returns nothing */
    /*1*/void (*signal(int, void func(int)))(int);
    /*2*/fv *signal(int, fv *);
    /*3*/pfv signal(int, pfv);

    fv print_hello_world; // declare function print_hello_world with function type fv

    signal(5, print_hello_world); // 2 args: signum and a callback function

    print_hello_world(5);

    fv *print_hello_world_p = &print_hello_world;
    print_hello_world_p(6);

    pfv print_hello_world_pp = &print_hello_world;
    print_hello_world_pp(7);

    signal(5, print_hello_world); // 2 args: signum and a callback function
}

void (*signal(int signum, void func(int)/*fv *func*//* pfv func */))(int)
{
    func(signum);
    printf("signum=%d func pointer = %p\n", signum, func);
    return NULL;
}

void print_hello_world(int num)
{
    printf("Hello, World! %d\n", num);
}

void tags(void)
{
    /* tags are used in strucutres, unions and enumerations */
    /* tags are not type names so you can't use them solely to declare a variable */
    // s s; // error
    struct s s; // tags exist in a different namespace, so having the same name of a tag and an identifier is fine (though, arguably, is more confusing)
    struct s *p; // pointer to struct s

    enum day { sun, mon, tue, wed, thu, fri, sat };
    // day today; // error: tag name != type name
    enum day tomorrow; // OK

    /* struct/unions/enumerations tags can be considered type name */
    /* So you can use typedef to define an alias for a tag */
    /* Take a look at anonymous structs and enumerations */
    typedefs();
    self_referential_structs();
}
