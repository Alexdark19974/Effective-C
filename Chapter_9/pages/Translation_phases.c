#include <stdio.h>

/* Chapter 9: Preprocessor
    Subchapter: The Compilation Process
   Pages: 169 - 170 */

/* Follow: https://jsommers.github.io/cbook/programstructure for more information */

void preprocessor_directives(void);
void include_directive(void);

void translation_stages(void);
int main(void)
{
    translation_stages();
}

void translation_stages(void)
{
    /* Preprocessor - a stage in translation of a source code into its executable state
       Here are the translation phases;
       1) Character mapping;
       2) Line splicing;
       3) Tokenization;
       4) Preprocessing;
       5) Character-set mapping;
       6) String concatenation;
       7) Translation; (into assembly)
       8) Linkage;

       To focus more on general phases of translation, there are 4 phases from source files into executables:

       Preprocessing (.i) -> (Assembling (.s.) and Compiling (.o)) -> Linking -> executable file

       1.Before the source code is translated into object code, the preprocessor steps in and handles a slew of things:
       1) Macro identifiers, expansion using the replacement list;
       2) Executing directives such as #include, #define, etc.;
       3) Conditional translation;
       4) comment removal; */

    /* C compilers make a top-to-bottom pass over source code files,
       That's why all declarations must precede their definitions */

    /* Compile this program with flag -E to see the output:
       "gcc translation_stages -E -o compilation_stages.i" */

    /* 2. After macros are resolved, the translation unit is compiled into assembly source code/instructions
       That are readable by your current processor
       Compile with flag -S and extention .s to see the intermediary assembly output file

       Before it is turned into object code (.o extention) - actual machine instructions or binary code
       Compile with flag -c to produce an object file

       This phase also inovles multiple compilations flags such as -Wall -Wextra --pedantic, etc. */

    /* 3. Linking stages invlolves taking >= 1 object files (.o, .so, etc.) and producing an executable binary program
       Linker is responsible for linking libraries (and other executables) and resolving dependencies between declarations and definitions
       Compile with flag -o to produce an executable object
     Follow Chapter 10 to read up more on this topic */
}

