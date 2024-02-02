#include <stdio.h>

/*
    Chapter 10: Program Structure
    Subchapter: Principles of Componentization:
        1) Coupling and Cohesion;
        2) Code Reuse;
        3) Data Abstractions;
        4) Opaque types;
    Pages: 185 - 189
*/

int main(void)
{
    /* When it comes to structuring your program, the best way
        To go about it is to divide the program into a few modules:
        1) directory for header files (include);
        2) directory for source files (src/source); 
        3) directory for executable files (".o" and binary files); 
        4) other directories based on translation phases

        It is possible to write a program using only main() function,
        but this approach will never land you a job.

        Instead, main() function better be perceived as a shared boundary or inteface,
        Which allows different components share and exchange information
        
        Any program starts with main() function - the main entry point, the main interface that is
        Shared by the rest of API. You can't write and execute code without the main() function

        When dealing with components of a program and sticking to the principle of componentization,
        The following things need to be taken account of:
        1) Cohesion;
        2) Coupling;
        3) Code reuse (subroutines);
        4) Data abstractions and ADTs (Abstraction data types): public / private interfaces, implementation thereof, opaque types;

        1) Cohesion is a measure of the commonality between elements of a programming interface;

           One's program structures has low cohesion if source files and headers have a concoction
           of functionalities, each of which has a different purpose
        
         For example, strlen() and sin(), while declared in the same header, have no commonality whatsoever,
         If they were declared in separate headers, the cohesion would be higher.
       
         For example, we have a separate header for the functionality of handling strings and character data:
         strcpy(), strlen(), strstr(), etc.

            The rule of thumb: the more diverse a header file is, the less cohesion it has
            <string.h> and <stdio.h> are highly cohesive becasue the former deals with character data only,
            and the latter I/O operations only. Also, it's simply harder to figure out the purpose the public if everything is stored in 1 file.
            Strive for high cohesion.

        2) Coupling is a measure of the interdependency of programming interfaces and ADTS/CDTS;

            If you have a tightly coupled header, you cannot include it by iteself without
            Having to include other headers in a certain order. Interfaces declared in header A cannot
            be included without including header B first, for example.

            If you have a loosely coupled public interface or header, it is self-sufficient
            And does not require additional inclusions from a user.

            Moreover, chanes made in a tightly coupled public interface may have a ripple effect across your project 
            A rule of thumb is strive for high cohesion and low coupling. 

        3) Code reuse is the practice of implementing functionality only once,
            And then reusing it in various parts of the program in order to avoid code duplication

            Functions are the the lowest-level reusable units of functionality
            Any repeatable logic is a good candiate to become a function or a subroutine
            Keeping implementation in a form of a function makes your code easier to maintain
            vs. ad hoc implementations because the code is contained in 1 place 

            Functions can be specific and general.
            If a function is specific, it is fast and effective, but can be applied to a limited number of purposes
            A function that adds 2 numbers cannot (and shouldn't be) calculate the square root.

            If a function is general-purpose, it can allow for more possible operations and greater flexibility
            At the cost of being less fast and less effective.

            A rule of thumb: strive for balance between specificity and generality of subroutines.


        4) Data abstractions are the clear separation of the interface and its implementation details
            An instance of data abstraction is printf() function in that we know what it does, what functionality it provides
            But the implementation or how it is done is hidden from a user.

            Another instance of data abstraction is data abstraction type (ADT), in particular, opaque types.
            Abstraction data type is a set of values (and operations that can be done with them) built on top of defined data types.
            For example, 'FILE *' is an opaque abtract data type because the implementation of the data type is hidden
            We know that the pointer to typedef stuct FILE handles file streams, but the details as well as the structure fields are hidden.

            There are several data type abstractions in C:
             1) functions/subroutines and their private / public interfaces;
             2) opaque or incomplete data types, esp. a pointer to an opaque data type;
             3) all instances of typedefs;

             Public interface is an instance of collection of data-type definitions, function declarations and constant definitions placed in a header file.

             The implementation of the data abstractions are placed in other internal header files or source files.

             For example, <string.h> provides the public interface for string-related functionality
             And <threads.h> provide the API for handling threads:
             1) Both serve different pursposes and are not interdependentwhich makes them very cohesive and loosly coupled;
             2) Both use their own internal headers and source files;
             3) both contain ADTs such as opaque types (such as thread_t, etc);

             NOTE: data types such as int, double, struct, union, etc. are well-defined built-in primitives
             But you can build a unique ADT using them; 

             Other ADTS: List, Queue, Tree, Stack, Map, Array

        5) Opaque (private) data types are incomplete data types that discribe an identifier,
            But lack information defining its size and layout 
            opaque data types are an instance of an ADT 

            The incomplete type is accessible to users via an interface, while its details
            Are hidden and available to implementation */

          FILE *fp = NULL; // FILE is not visible to us, but visible to implementation

    return 0;
}
