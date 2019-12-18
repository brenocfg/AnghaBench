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

/* Variables and functions */
 int stored_argc ; 
 int /*<<< orphan*/ * stored_argv ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const* const) ; 

int find_arg ( const char * const key )
{
    int i;

    for ( i = 0; i < stored_argc && strcasecmp ( stored_argv[i], key ); i++ ) {
        ;
    }

    return i < stored_argc ? i : -1;
}