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
struct parsed_symbol {char* current; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 char* und_alloc (struct parsed_symbol*,int) ; 

__attribute__((used)) static const char* get_number(struct parsed_symbol* sym)
{
    char*       ptr;
    BOOL        sgn = FALSE;

    if (*sym->current == '?')
    {
        sgn = TRUE;
        sym->current++;
    }
    if (*sym->current >= '0' && *sym->current <= '8')
    {
        ptr = und_alloc(sym, 3);
        if (sgn) ptr[0] = '-';
        ptr[sgn ? 1 : 0] = *sym->current + 1;
        ptr[sgn ? 2 : 1] = '\0';
        sym->current++;
    }
    else if (*sym->current == '9')
    {
        ptr = und_alloc(sym, 4);
        if (sgn) ptr[0] = '-';
        ptr[sgn ? 1 : 0] = '1';
        ptr[sgn ? 2 : 1] = '0';
        ptr[sgn ? 3 : 2] = '\0';
        sym->current++;
    }
    else if (*sym->current >= 'A' && *sym->current <= 'P')
    {
        int ret = 0;

        while (*sym->current >= 'A' && *sym->current <= 'P')
        {
            ret *= 16;
            ret += *sym->current++ - 'A';
        }
        if (*sym->current != '@') return NULL;

        ptr = und_alloc(sym, 17);
        sprintf(ptr, "%s%u", sgn ? "-" : "", ret);
        sym->current++;
    }
    else return NULL;
    return ptr;
}