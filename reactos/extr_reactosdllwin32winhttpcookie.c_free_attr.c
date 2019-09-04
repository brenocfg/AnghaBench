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
struct attr {struct attr* value; struct attr* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (struct attr*) ; 

__attribute__((used)) static void free_attr( struct attr *attr )
{
    if (!attr) return;
    heap_free( attr->name );
    heap_free( attr->value );
    heap_free( attr );
}