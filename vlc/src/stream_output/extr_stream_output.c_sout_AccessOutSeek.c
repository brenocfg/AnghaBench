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
struct TYPE_4__ {int (* pf_seek ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ sout_access_out_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

int sout_AccessOutSeek( sout_access_out_t *p_access, off_t i_pos )
{
    if (p_access->pf_seek == NULL)
        return VLC_EGENERIC;
    return p_access->pf_seek( p_access, i_pos );
}