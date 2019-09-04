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
struct counter {struct counter* path; scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (struct counter*) ; 

__attribute__((used)) static void destroy_counter( struct counter *counter )
{
    counter->magic = 0;
    heap_free( counter->path );
    heap_free( counter );
}