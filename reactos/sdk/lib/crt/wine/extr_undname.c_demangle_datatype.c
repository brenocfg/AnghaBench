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
struct datatype_t {char* left; char* right; } ;
struct array {int dummy; } ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,char) ; 
 void* FALSE ; 
 void* TRUE ; 
 int UNDNAME_NO_ALLOCATION_LANGUAGE ; 
 int UNDNAME_NO_COMPLEX_TYPE ; 
 int /*<<< orphan*/  assert (struct datatype_t*) ; 
 int atoi (char const*) ; 
 char* get_args (struct parsed_symbol*,struct array*,void*,char,char) ; 
 int /*<<< orphan*/  get_calling_convention (int /*<<< orphan*/ ,char const**,char const**,int) ; 
 void* get_class_name (struct parsed_symbol*) ; 
 char* get_extended_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_modified_type (struct datatype_t*,struct parsed_symbol*,struct array*,char,void*) ; 
 int /*<<< orphan*/  get_modifier (struct parsed_symbol*,char const**,char const**) ; 
 char const* get_number (struct parsed_symbol*) ; 
 char* get_simple_type (char) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 void* str_array_get_ref (struct array*,char) ; 
 int /*<<< orphan*/  str_array_push (struct parsed_symbol*,char*,int,struct array*) ; 
 void* str_printf (struct parsed_symbol*,char*,char const*,...) ; 

__attribute__((used)) static BOOL demangle_datatype(struct parsed_symbol* sym, struct datatype_t* ct,
                              struct array* pmt_ref, BOOL in_args)
{
    char                dt;
    BOOL                add_pmt = TRUE;

    assert(ct);
    ct->left = ct->right = NULL;
    
    switch (dt = *sym->current++)
    {
    case '_':
        /* MS type: __int8,__int16 etc */
        ct->left = get_extended_type(*sym->current++);
        break;
    case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'M':
    case 'N': case 'O': case 'X': case 'Z':
        /* Simple data types */
        ct->left = get_simple_type(dt);
        add_pmt = FALSE;
        break;
    case 'T': /* union */
    case 'U': /* struct */
    case 'V': /* class */
    case 'Y': /* cointerface */
        /* Class/struct/union/cointerface */
        {
            const char* struct_name = NULL;
            const char* type_name = NULL;

            if (!(struct_name = get_class_name(sym)))
                goto done;
            if (!(sym->flags & UNDNAME_NO_COMPLEX_TYPE)) 
            {
                switch (dt)
                {
                case 'T': type_name = "union ";  break;
                case 'U': type_name = "struct "; break;
                case 'V': type_name = "class ";  break;
                case 'Y': type_name = "cointerface "; break;
                }
            }
            ct->left = str_printf(sym, "%s%s", type_name, struct_name);
        }
        break;
    case '?':
        /* not all the time is seems */
        if (in_args)
        {
            const char*   ptr;
            if (!(ptr = get_number(sym))) goto done;
            ct->left = str_printf(sym, "`template-parameter-%s'", ptr);
        }
        else
        {
            if (!get_modified_type(ct, sym, pmt_ref, '?', in_args)) goto done;
        }
        break;
    case 'A': /* reference */
    case 'B': /* volatile reference */
        if (!get_modified_type(ct, sym, pmt_ref, dt, in_args)) goto done;
        break;
    case 'Q': /* const pointer */
    case 'R': /* volatile pointer */
    case 'S': /* const volatile pointer */
        if (!get_modified_type(ct, sym, pmt_ref, in_args ? dt : 'P', in_args)) goto done;
        break;
    case 'P': /* Pointer */
        if (isdigit(*sym->current))
	{
            /* FIXME:
             *   P6 = Function pointer
             *   P8 = Member function pointer
             *   others who knows.. */
            if (*sym->current == '8')
            {
                char*                   args = NULL;
                const char*             call_conv;
                const char*             exported;
                struct datatype_t       sub_ct;
                unsigned                mark = sym->stack.num;
                const char*             class;
                const char*             modifier;
                const char*             ptr_modif;

                sym->current++;

                if (!(class = get_class_name(sym)))
                    goto done;
                if (!get_modifier(sym, &modifier, &ptr_modif))
                    goto done;
                if (modifier)
                    modifier = str_printf(sym, "%s %s", modifier, ptr_modif);
                else if(ptr_modif[0])
                    modifier = str_printf(sym, " %s", ptr_modif);
                if (!get_calling_convention(*sym->current++,
                            &call_conv, &exported,
                            sym->flags & ~UNDNAME_NO_ALLOCATION_LANGUAGE))
                    goto done;
                if (!demangle_datatype(sym, &sub_ct, pmt_ref, FALSE))
                    goto done;

                args = get_args(sym, pmt_ref, TRUE, '(', ')');
                if (!args) goto done;
                sym->stack.num = mark;

                ct->left  = str_printf(sym, "%s%s (%s %s::*",
                        sub_ct.left, sub_ct.right, call_conv, class);
                ct->right = str_printf(sym, ")%s%s", args, modifier);
            }
            else if (*sym->current == '6')
            {
                char*                   args = NULL;
                const char*             call_conv;
                const char*             exported;
                struct datatype_t       sub_ct;
                unsigned                mark = sym->stack.num;

                sym->current++;

                if (!get_calling_convention(*sym->current++,
                                            &call_conv, &exported, 
                                            sym->flags & ~UNDNAME_NO_ALLOCATION_LANGUAGE) ||
                    !demangle_datatype(sym, &sub_ct, pmt_ref, FALSE))
                    goto done;

                args = get_args(sym, pmt_ref, TRUE, '(', ')');
                if (!args) goto done;
                sym->stack.num = mark;

                ct->left  = str_printf(sym, "%s%s (%s*", 
                                       sub_ct.left, sub_ct.right, call_conv);
                ct->right = str_printf(sym, ")%s", args);
            }
            else goto done;
	}
	else if (!get_modified_type(ct, sym, pmt_ref, 'P', in_args)) goto done;
        break;
    case 'W':
        if (*sym->current == '4')
        {
            char*               enum_name;
            sym->current++;
            if (!(enum_name = get_class_name(sym)))
                goto done;
            if (sym->flags & UNDNAME_NO_COMPLEX_TYPE)
                ct->left = enum_name;
            else
                ct->left = str_printf(sym, "enum %s", enum_name);
        }
        else goto done;
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        /* Referring back to previously parsed type */
        /* left and right are pushed as two separate strings */
        if (!pmt_ref) goto done;
        ct->left = str_array_get_ref(pmt_ref, (dt - '0') * 2);
        ct->right = str_array_get_ref(pmt_ref, (dt - '0') * 2 + 1);
        if (!ct->left) goto done;
        add_pmt = FALSE;
        break;
    case '$':
        switch (*sym->current++)
        {
        case '0':
            if (!(ct->left = get_number(sym))) goto done;
            break;
        case 'D':
            {
                const char*   ptr;
                if (!(ptr = get_number(sym))) goto done;
                ct->left = str_printf(sym, "`template-parameter%s'", ptr);
            }
            break;
        case 'F':
            {
                const char*   p1;
                const char*   p2;
                if (!(p1 = get_number(sym))) goto done;
                if (!(p2 = get_number(sym))) goto done;
                ct->left = str_printf(sym, "{%s,%s}", p1, p2);
            }
            break;
        case 'G':
            {
                const char*   p1;
                const char*   p2;
                const char*   p3;
                if (!(p1 = get_number(sym))) goto done;
                if (!(p2 = get_number(sym))) goto done;
                if (!(p3 = get_number(sym))) goto done;
                ct->left = str_printf(sym, "{%s,%s,%s}", p1, p2, p3);
            }
            break;
        case 'Q':
            {
                const char*   ptr;
                if (!(ptr = get_number(sym))) goto done;
                ct->left = str_printf(sym, "`non-type-template-parameter%s'", ptr);
            }
            break;
        case '$':
            if (*sym->current == 'B')
            {
                unsigned            mark = sym->stack.num;
                struct datatype_t   sub_ct;
                const char*         arr = NULL;
                sym->current++;

                /* multidimensional arrays */
                if (*sym->current == 'Y')
                {
                    const char* n1;
                    int num;

                    sym->current++;
                    if (!(n1 = get_number(sym))) goto done;
                    num = atoi(n1);

                    while (num--)
                        arr = str_printf(sym, "%s[%s]", arr, get_number(sym));
                }

                if (!demangle_datatype(sym, &sub_ct, pmt_ref, FALSE)) goto done;

                if (arr)
                    ct->left = str_printf(sym, "%s %s", sub_ct.left, arr);
                else
                    ct->left = sub_ct.left;
                ct->right = sub_ct.right;
                sym->stack.num = mark;
            }
            else if (*sym->current == 'C')
            {
                const char *ptr, *ptr_modif;

                sym->current++;
                if (!get_modifier(sym, &ptr, &ptr_modif)) goto done;
                if (!demangle_datatype(sym, ct, pmt_ref, in_args)) goto done;
                ct->left = str_printf(sym, "%s %s", ct->left, ptr);
            }
            break;
        }
        break;
    default :
        ERR("Unknown type %c\n", dt);
        break;
    }
    if (add_pmt && pmt_ref && in_args)
    {
        /* left and right are pushed as two separate strings */
        if (!str_array_push(sym, ct->left ? ct->left : "", -1, pmt_ref) ||
            !str_array_push(sym, ct->right ? ct->right : "", -1, pmt_ref))
            return FALSE;
    }
done:
    
    return ct->left != NULL;
}