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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int ulLo; } ;
typedef  TYPE_1__ QWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DosTmrQueryTime (TYPE_1__*) ; 
 int rand () ; 

void vlc_rand_bytes (void *buf, size_t len)
{
    QWORD qwTime;
    uint8_t *p_buf = (uint8_t *)buf;

    while (len > 0)
    {
        DosTmrQueryTime( &qwTime );

        *p_buf++ = ( uint8_t )( qwTime.ulLo * rand());
        len--;
    }
}