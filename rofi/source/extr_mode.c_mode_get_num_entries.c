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
struct TYPE_4__ {unsigned int (* _get_num_entries ) (TYPE_1__ const*) ;} ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 unsigned int stub1 (TYPE_1__ const*) ; 

unsigned int mode_get_num_entries ( const Mode *mode )
{
    g_assert ( mode != NULL );
    g_assert ( mode->_get_num_entries != NULL );
    return mode->_get_num_entries ( mode );
}