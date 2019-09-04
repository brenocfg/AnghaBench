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
 int /*<<< orphan*/  isdigit (char const) ; 
 struct symt** stabs_read_type_enum (char const**) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static struct symt* stabs_parse_type(const char* stab)
{
    const char* c = stab - 1;

    /*
     * Look through the stab definition, and figure out what struct symt
     * this represents.  If we have something we know about, assign the
     * type.
     * According to "The \"stabs\" debug format" (Rev 2.130) the name may be
     * a C++ name and contain double colons e.g. foo::bar::baz:t5=*6.
     */
    do
    {
        if ((c = strchr(c + 1, ':')) == NULL) return NULL;
    } while (*++c == ':');

    /*
     * The next characters say more about the type (i.e. data, function, etc)
     * of symbol.  Skip them.  (C++ for example may have Tt).
     * Actually this is a very weak description; I think Tt is the only
     * multiple combination we should see.
     */
    while (*c && *c != '(' && !isdigit(*c))
        c++;
    /*
     * The next is either an integer or a (integer,integer).
     * The stabs_read_type_enum() takes care that stab_types is large enough.
     */
    return *stabs_read_type_enum(&c);
}