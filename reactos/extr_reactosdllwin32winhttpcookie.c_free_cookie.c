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
struct TYPE_4__ {struct TYPE_4__* path; struct TYPE_4__* value; struct TYPE_4__* name; } ;
typedef  TYPE_1__ cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static void free_cookie( cookie_t *cookie )
{
    heap_free( cookie->name );
    heap_free( cookie->value );
    heap_free( cookie->path );
    heap_free( cookie );
}