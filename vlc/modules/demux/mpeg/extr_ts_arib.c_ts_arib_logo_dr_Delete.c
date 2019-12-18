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
struct TYPE_4__ {struct TYPE_4__* p_logo_char; } ;
typedef  TYPE_1__ ts_arib_logo_dr_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void ts_arib_logo_dr_Delete( ts_arib_logo_dr_t *p_dr )
{
    free( p_dr->p_logo_char );
    free( p_dr );
}