#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_5__ {int /*<<< orphan*/  fifo; } ;
typedef  TYPE_2__ filter_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DoRealWork (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * block_FifoGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *Thread( void *data )
{
    filter_t *p_filter = data;
    filter_sys_t *sys = p_filter->p_sys;

    for (;;)
    {
        block_t *block = block_FifoGet( sys->fifo );

        int canc = vlc_savecancel( );
        block_Release( DoRealWork( p_filter, block ) );
        vlc_restorecancel( canc );
    }
    vlc_assert_unreachable();
}