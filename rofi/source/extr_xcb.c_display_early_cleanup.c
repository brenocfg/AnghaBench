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
struct TYPE_2__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_keyboard () ; 
 int /*<<< orphan*/  release_pointer () ; 
 TYPE_1__* xcb ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 

void display_early_cleanup ( void )
{
    release_keyboard ( );
    release_pointer ( );
    xcb_flush ( xcb->connection );
}