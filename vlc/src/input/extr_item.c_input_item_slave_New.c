#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_type; int i_priority; int b_forced; int /*<<< orphan*/  psz_uri; } ;
typedef  TYPE_1__ input_item_slave_t ;
typedef  enum slave_type { ____Placeholder_slave_type } slave_type ;
typedef  enum slave_priority { ____Placeholder_slave_priority } slave_priority ;

/* Variables and functions */
 TYPE_1__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

input_item_slave_t *input_item_slave_New(const char *psz_uri, enum slave_type i_type,
                                       enum slave_priority i_priority)
{
    if( !psz_uri )
        return NULL;

    input_item_slave_t *p_slave = malloc( sizeof( *p_slave ) + strlen( psz_uri ) + 1 );
    if( !p_slave )
        return NULL;

    p_slave->i_type = i_type;
    p_slave->i_priority = i_priority;
    p_slave->b_forced = false;
    strcpy( p_slave->psz_uri, psz_uri );

    return p_slave;
}