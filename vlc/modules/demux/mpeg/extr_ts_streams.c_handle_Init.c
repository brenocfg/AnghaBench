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
struct TYPE_4__ {void* p_sys; } ;
typedef  TYPE_1__ dvbpsi_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVBPSI_MSG_DEBUG ; 
 int /*<<< orphan*/  dvbpsi_messages ; 
 TYPE_1__* dvbpsi_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool handle_Init( demux_t *p_demux, dvbpsi_t **handle )
{
    *handle = dvbpsi_new( &dvbpsi_messages, DVBPSI_MSG_DEBUG );
    if( !*handle )
        return false;
    (*handle)->p_sys = (void *) p_demux;
    return true;
}