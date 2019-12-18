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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_4__ {int (* pf_control ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int demux_vaControl( demux_t *demux, int query, va_list args )
{
    return demux->pf_control( demux, query, args );
}