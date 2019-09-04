#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  var_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned short IsBasetype ; 
 unsigned short IsByValue ; 
 unsigned short IsIn ; 
 unsigned short IsOut ; 
 unsigned short IsPipe ; 
 unsigned short IsReturn ; 
 unsigned short IsSimpleRef ; 
 unsigned short MustFree ; 
 unsigned short MustSize ; 
 unsigned char get_parameter_fc (int /*<<< orphan*/  const*,int,unsigned short*,unsigned int*,unsigned int*) ; 
 scalar_t__ max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointer_size ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned short) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 unsigned int string_of_type (unsigned char) ; 
 int strlen (char*) ; 

__attribute__((used)) static unsigned int write_new_procformatstring_type(FILE *file, int indent, const var_t *var,
                                                    int is_return, unsigned int *stack_offset)
{
    char buffer[128];
    unsigned int stack_size, typestring_offset;
    unsigned short flags;
    unsigned char fc = get_parameter_fc( var, is_return, &flags, &stack_size, &typestring_offset );

    strcpy( buffer, "/* flags:" );
    if (flags & MustSize) strcat( buffer, " must size," );
    if (flags & MustFree) strcat( buffer, " must free," );
    if (flags & IsPipe) strcat( buffer, " pipe," );
    if (flags & IsIn) strcat( buffer, " in," );
    if (flags & IsOut) strcat( buffer, " out," );
    if (flags & IsReturn) strcat( buffer, " return," );
    if (flags & IsBasetype) strcat( buffer, " base type," );
    if (flags & IsByValue) strcat( buffer, " by value," );
    if (flags & IsSimpleRef) strcat( buffer, " simple ref," );
    if (flags >> 13) sprintf( buffer + strlen(buffer), " srv size=%u,", (flags >> 13) * 8 );
    strcpy( buffer + strlen( buffer ) - 1, " */" );
    print_file( file, indent, "NdrFcShort(0x%hx),\t%s\n", flags, buffer );
    print_file( file, indent, "NdrFcShort(0x%x),	/* stack offset = %u */\n",
                *stack_offset, *stack_offset );
    if (flags & IsBasetype)
    {
        print_file( file, indent, "0x%02x,	/* %s */\n", fc, string_of_type(fc) );
        print_file( file, indent, "0x0,\n" );
    }
    else
        print_file( file, indent, "NdrFcShort(0x%x),	/* type offset = %u */\n",
                    typestring_offset, typestring_offset );
    *stack_offset += max( stack_size, pointer_size );
    return 6;
}