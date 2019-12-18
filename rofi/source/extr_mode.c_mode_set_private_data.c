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
struct TYPE_3__ {int /*<<< orphan*/ * private_data; } ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 

void mode_set_private_data ( Mode *mode, void *pd )
{
    g_assert ( mode != NULL );
    if ( pd != NULL ) {
        g_assert ( mode->private_data == NULL );
    }
    mode->private_data = pd;
}