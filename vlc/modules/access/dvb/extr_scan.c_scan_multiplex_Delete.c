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
typedef  int /*<<< orphan*/  scan_multiplex_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_multiplex_Clean (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scan_multiplex_Delete( scan_multiplex_t *p_mplex )
{
    scan_multiplex_Clean( p_mplex );
    free( p_mplex );
}