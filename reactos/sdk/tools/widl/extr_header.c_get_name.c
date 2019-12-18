#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ var_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_PROPGET ; 
 int /*<<< orphan*/  ATTR_PROPPUT ; 
 int /*<<< orphan*/  ATTR_PROPPUTREF ; 
 scalar_t__ is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

const char *get_name(const var_t *v)
{
    static char buffer[256];

    if (is_attr( v->attrs, ATTR_PROPGET ))
        strcpy( buffer, "get_" );
    else if (is_attr( v->attrs, ATTR_PROPPUT ))
        strcpy( buffer, "put_" );
    else if (is_attr( v->attrs, ATTR_PROPPUTREF ))
        strcpy( buffer, "putref_" );
    else
        buffer[0] = 0;
    strcat( buffer, v->name );
    return buffer;
}