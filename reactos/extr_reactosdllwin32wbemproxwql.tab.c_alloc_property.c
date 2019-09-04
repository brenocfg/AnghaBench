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
struct property {int /*<<< orphan*/ * next; int /*<<< orphan*/  const* class; int /*<<< orphan*/  const* name; } ;
struct parser {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 struct property* alloc_mem (struct parser*,int) ; 

__attribute__((used)) static struct property *alloc_property( struct parser *parser, const WCHAR *class, const WCHAR *name )
{
    struct property *prop = alloc_mem( parser, sizeof(*prop) );
    if (prop)
    {
        prop->name  = name;
        prop->class = class;
        prop->next  = NULL;
    }
    return prop;
}