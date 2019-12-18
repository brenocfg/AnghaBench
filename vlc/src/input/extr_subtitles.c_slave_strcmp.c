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
struct TYPE_2__ {int /*<<< orphan*/  psz_uri; } ;
typedef  TYPE_1__ input_item_slave_t ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slave_strcmp( const void *a, const void *b )
{
    const input_item_slave_t *p_slave0 = *((const input_item_slave_t **) a);
    const input_item_slave_t *p_slave1 = *((const input_item_slave_t **) b);

    if( p_slave0 == NULL || p_slave1 == NULL )
        return 0;

    /* We can compare these uris since they come from the file system */
#ifdef HAVE_STRCOLL
    return strcoll( p_slave0->psz_uri, p_slave1->psz_uri );
#else
    return strcmp( p_slave0->psz_uri, p_slave1->psz_uri );
#endif
}