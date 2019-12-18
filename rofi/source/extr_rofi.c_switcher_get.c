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
 int /*<<< orphan*/  mode_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * modi ; 
 unsigned int num_modi ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int switcher_get ( const char *name )
{
    for ( unsigned int i = 0; i < num_modi; i++ ) {
        if ( strcmp ( mode_get_name ( modi[i] ), name ) == 0 ) {
            return i;
        }
    }
    return -1;
}