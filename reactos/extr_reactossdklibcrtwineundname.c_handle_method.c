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
struct parsed_symbol {char* current; int flags; void* result; TYPE_1__ stack; } ;
struct datatype_t {char* left; int /*<<< orphan*/ * right; } ;
struct array {int dummy; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int UNDNAME_NAME_ONLY ; 
 int UNDNAME_NO_ACCESS_SPECIFIERS ; 
 int UNDNAME_NO_FUNCTION_RETURNS ; 
 int UNDNAME_NO_MEMBER_TYPE ; 
 int UNDNAME_NO_THISTYPE ; 
 int /*<<< orphan*/  demangle_datatype (struct parsed_symbol*,struct datatype_t*,struct array*,scalar_t__) ; 
 char* get_args (struct parsed_symbol*,struct array*,scalar_t__,char,char) ; 
 int /*<<< orphan*/  get_calling_convention (int /*<<< orphan*/ ,char const**,char const**,int) ; 
 char* get_class_string (struct parsed_symbol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_modifier (struct parsed_symbol*,char const**,char const**) ; 
 char* get_number (struct parsed_symbol*) ; 
 int /*<<< orphan*/  str_array_init (struct array*) ; 
 void* str_printf (struct parsed_symbol*,char*,char const*,...) ; 

__attribute__((used)) static BOOL handle_method(struct parsed_symbol* sym, BOOL cast_op)
{
    char                accmem;
    const char*         access = NULL;
    int                 access_id = -1;
    const char*         member_type = NULL;
    struct datatype_t   ct_ret;
    const char*         call_conv;
    const char*         modifier = NULL;
    const char*         exported;
    const char*         args_str = NULL;
    const char*         name = NULL;
    BOOL                ret = FALSE, has_args = TRUE, has_ret = TRUE;
    unsigned            mark;
    struct array        array_pmt;

    /* FIXME: why 2 possible letters for each option?
     * 'A' private:
     * 'B' private:
     * 'C' private: static
     * 'D' private: static
     * 'E' private: virtual
     * 'F' private: virtual
     * 'G' private: thunk
     * 'H' private: thunk
     * 'I' protected:
     * 'J' protected:
     * 'K' protected: static
     * 'L' protected: static
     * 'M' protected: virtual
     * 'N' protected: virtual
     * 'O' protected: thunk
     * 'P' protected: thunk
     * 'Q' public:
     * 'R' public:
     * 'S' public: static
     * 'T' public: static
     * 'U' public: virtual
     * 'V' public: virtual
     * 'W' public: thunk
     * 'X' public: thunk
     * 'Y'
     * 'Z'
     * "$0" private: thunk vtordisp
     * "$1" private: thunk vtordisp
     * "$2" protected: thunk vtordisp
     * "$3" protected: thunk vtordisp
     * "$4" public: thunk vtordisp
     * "$5" public: thunk vtordisp
     * "$B" vcall thunk
     * "$R" thunk vtordispex
     */
    accmem = *sym->current++;
    if (accmem == '$')
    {
        if (*sym->current >= '0' && *sym->current <= '5')
            access_id = (*sym->current - '0') / 2;
        else if (*sym->current == 'R')
            access_id = (sym->current[1] - '0') / 2;
        else if (*sym->current != 'B')
            goto done;
    }
    else if (accmem >= 'A' && accmem <= 'Z')
        access_id = (accmem - 'A') / 8;
    else
        goto done;

    switch (access_id)
    {
    case 0: access = "private: "; break;
    case 1: access = "protected: "; break;
    case 2: access = "public: "; break;
    }
    if (accmem == '$' || (accmem - 'A') % 8 == 6 || (accmem - 'A') % 8 == 7)
        access = str_printf(sym, "[thunk]:%s", access ? access : " ");

    if (accmem == '$' && *sym->current != 'B')
        member_type = "virtual ";
    else if (accmem <= 'X')
    {
        switch ((accmem - 'A') % 8)
        {
        case 2: case 3: member_type = "static "; break;
        case 4: case 5: case 6: case 7: member_type = "virtual "; break;
        }
    }

    if (sym->flags & UNDNAME_NO_ACCESS_SPECIFIERS)
        access = NULL;
    if (sym->flags & UNDNAME_NO_MEMBER_TYPE)
        member_type = NULL;

    name = get_class_string(sym, 0);

    if (accmem == '$' && *sym->current == 'B') /* vcall thunk */
    {
        const char *n;

        sym->current++;
        n = get_number(sym);

        if(!n || *sym->current++ != 'A') goto done;
        name = str_printf(sym, "%s{%s,{flat}}' }'", name, n);
        has_args = FALSE;
        has_ret = FALSE;
    }
    else if (accmem == '$' && *sym->current == 'R') /* vtordispex thunk */
    {
        const char *n1, *n2, *n3, *n4;

        sym->current += 2;
        n1 = get_number(sym);
        n2 = get_number(sym);
        n3 = get_number(sym);
        n4 = get_number(sym);

        if(!n1 || !n2 || !n3 || !n4) goto done;
        name = str_printf(sym, "%s`vtordispex{%s,%s,%s,%s}' ", name, n1, n2, n3, n4);
    }
    else if (accmem == '$') /* vtordisp thunk */
    {
        const char *n1, *n2;

        sym->current++;
        n1 = get_number(sym);
        n2 = get_number(sym);

        if (!n1 || !n2) goto done;
        name = str_printf(sym, "%s`vtordisp{%s,%s}' ", name, n1, n2);
    }
    else if ((accmem - 'A') % 8 == 6 || (accmem - 'A') % 8 == 7) /* a thunk */
        name = str_printf(sym, "%s`adjustor{%s}' ", name, get_number(sym));

    if (has_args && (accmem == '$' ||
                (accmem <= 'X' && (accmem - 'A') % 8 != 2 && (accmem - 'A') % 8 != 3)))
    {
        const char *ptr_modif;
        /* Implicit 'this' pointer */
        /* If there is an implicit this pointer, const modifier follows */
        if (!get_modifier(sym, &modifier, &ptr_modif)) goto done;
        if (modifier || ptr_modif) modifier = str_printf(sym, "%s %s", modifier, ptr_modif);
    }

    if (!get_calling_convention(*sym->current++, &call_conv, &exported,
                                sym->flags))
        goto done;

    str_array_init(&array_pmt);

    /* Return type, or @ if 'void' */
    if (has_ret && *sym->current == '@')
    {
        ct_ret.left = "void";
        ct_ret.right = NULL;
        sym->current++;
    }
    else if (has_ret)
    {
        if (!demangle_datatype(sym, &ct_ret, &array_pmt, FALSE))
            goto done;
    }
    if (!has_ret || sym->flags & UNDNAME_NO_FUNCTION_RETURNS)
        ct_ret.left = ct_ret.right = NULL;
    if (cast_op)
    {
        name = str_printf(sym, "%s%s%s", name, ct_ret.left, ct_ret.right);
        ct_ret.left = ct_ret.right = NULL;
    }

    mark = sym->stack.num;
    if (has_args && !(args_str = get_args(sym, &array_pmt, TRUE, '(', ')'))) goto done;
    if (sym->flags & UNDNAME_NAME_ONLY) args_str = modifier = NULL;
    if (sym->flags & UNDNAME_NO_THISTYPE) modifier = NULL;
    sym->stack.num = mark;

    /* Note: '()' after 'Z' means 'throws', but we don't care here
     * Yet!!! FIXME
     */
    sym->result = str_printf(sym, "%s%s%s%s%s%s%s%s%s%s%s",
                             access, member_type, ct_ret.left,
                             (ct_ret.left && !ct_ret.right) ? " " : NULL,
                             call_conv, call_conv ? " " : NULL, exported,
                             name, args_str, modifier, ct_ret.right);
    ret = TRUE;
done:
    return ret;
}