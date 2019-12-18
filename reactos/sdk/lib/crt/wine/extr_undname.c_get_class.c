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
struct array {unsigned int start; unsigned int num; } ;
struct parsed_symbol {char* current; char const* result; struct array stack; struct array names; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* get_literal_string (struct parsed_symbol*) ; 
 char* get_number (struct parsed_symbol*) ; 
 char* get_template_name (struct parsed_symbol*) ; 
 char* str_array_get_ref (struct array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_array_init (struct array*) ; 
 int /*<<< orphan*/  str_array_push (struct parsed_symbol*,char const*,int,struct array*) ; 
 char* str_printf (struct parsed_symbol*,char*,char const*) ; 
 int /*<<< orphan*/  symbol_demangle (struct parsed_symbol*) ; 

__attribute__((used)) static BOOL get_class(struct parsed_symbol* sym)
{
    const char* name = NULL;

    while (*sym->current != '@')
    {
        switch (*sym->current)
        {
        case '\0': return FALSE;

        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
        case '8': case '9':
            name = str_array_get_ref(&sym->names, *sym->current++ - '0');
            break;
        case '?':
            switch (*++sym->current)
            {
            case '$':
                sym->current++;
                if ((name = get_template_name(sym)) &&
                    !str_array_push(sym, name, -1, &sym->names))
                    return FALSE;
                break;
            case '?':
                {
                    struct array stack = sym->stack;
                    unsigned int start = sym->names.start;
                    unsigned int num = sym->names.num;

                    str_array_init( &sym->stack );
                    if (symbol_demangle( sym )) name = str_printf( sym, "`%s'", sym->result );
                    sym->names.start = start;
                    sym->names.num = num;
                    sym->stack = stack;
                }
                break;
            default:
                if (!(name = get_number( sym ))) return FALSE;
                name = str_printf( sym, "`%s'", name );
                break;
            }
            break;
        default:
            name = get_literal_string(sym);
            break;
        }
        if (!name || !str_array_push(sym, name, -1, &sym->stack))
            return FALSE;
    }
    sym->current++;
    return TRUE;
}