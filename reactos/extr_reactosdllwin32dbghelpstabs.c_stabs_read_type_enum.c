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
struct symt {int dummy; } ;

/* Variables and functions */
 struct symt** stabs_find_ref (long,long) ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static struct symt** stabs_read_type_enum(const char** x)
{
    long        filenr, subnr;
    const char* iter;
    char*       end;

    iter = *x;
    if (*iter == '(')
    {
        ++iter;                             /* '('   */
        filenr = strtol(iter, &end, 10);    /* <int> */
        iter = ++end;                       /* ','   */
        subnr = strtol(iter, &end, 10);     /* <int> */
        iter = ++end;                       /* ')'   */
    }
    else
    {
        filenr = 0;
        subnr = strtol(iter, &end, 10);     /* <int> */
        iter = end;
    }
    *x = iter;
    return stabs_find_ref(filenr, subnr);
}