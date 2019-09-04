#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int num; } ;
struct parsed_symbol {char* current; int flags; TYPE_1__ stack; } ;
struct datatype_t {char* left; int /*<<< orphan*/  right; } ;
struct array {int dummy; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int UNDNAME_NO_LEADING_UNDERSCORES ; 
 int UNDNAME_NO_MS_KEYWORDS ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  demangle_datatype (struct parsed_symbol*,struct datatype_t*,struct array*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_modifier (struct parsed_symbol*,char const**,char const**) ; 
 char const* get_number (struct parsed_symbol*) ; 
 void* str_printf (struct parsed_symbol*,char*,char const*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static BOOL get_modified_type(struct datatype_t *ct, struct parsed_symbol* sym,
                              struct array *pmt_ref, char modif, BOOL in_args)
{
    const char* modifier;
    const char* str_modif;
    const char *ptr_modif = "";

    if (*sym->current == 'E')
    {
        if (!(sym->flags & UNDNAME_NO_MS_KEYWORDS))
        {
            if (sym->flags & UNDNAME_NO_LEADING_UNDERSCORES)
                ptr_modif = " ptr64";
            else
                ptr_modif = " __ptr64";
        }
        sym->current++;
    }

    switch (modif)
    {
    case 'A': str_modif = str_printf(sym, " &%s", ptr_modif); break;
    case 'B': str_modif = str_printf(sym, " &%s volatile", ptr_modif); break;
    case 'P': str_modif = str_printf(sym, " *%s", ptr_modif); break;
    case 'Q': str_modif = str_printf(sym, " *%s const", ptr_modif); break;
    case 'R': str_modif = str_printf(sym, " *%s volatile", ptr_modif); break;
    case 'S': str_modif = str_printf(sym, " *%s const volatile", ptr_modif); break;
    case '?': str_modif = ""; break;
    default: return FALSE;
    }

    if (get_modifier(sym, &modifier, &ptr_modif))
    {
        unsigned            mark = sym->stack.num;
        struct datatype_t   sub_ct;

        /* multidimensional arrays */
        if (*sym->current == 'Y')
        {
            const char* n1;
            int num;

            sym->current++;
            if (!(n1 = get_number(sym))) return FALSE;
            num = atoi(n1);

            if (str_modif[0] == ' ' && !modifier)
                str_modif++;

            if (modifier)
            {
                str_modif = str_printf(sym, " (%s%s)", modifier, str_modif);
                modifier = NULL;
            }
            else
                str_modif = str_printf(sym, " (%s)", str_modif);

            while (num--)
                str_modif = str_printf(sym, "%s[%s]", str_modif, get_number(sym));
        }

        /* Recurse to get the referred-to type */
        if (!demangle_datatype(sym, &sub_ct, pmt_ref, FALSE))
            return FALSE;
        if (modifier)
            ct->left = str_printf(sym, "%s %s%s", sub_ct.left, modifier, str_modif );
        else
        {
            /* don't insert a space between duplicate '*' */
            if (!in_args && str_modif[0] && str_modif[1] == '*' && sub_ct.left[strlen(sub_ct.left)-1] == '*')
                str_modif++;
            ct->left = str_printf(sym, "%s%s", sub_ct.left, str_modif );
        }
        ct->right = sub_ct.right;
        sym->stack.num = mark;
    }
    return TRUE;
}