#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_9__ {struct TYPE_9__* p_assocs; } ;
struct TYPE_8__ {size_t i_entry_count; TYPE_4__* p_entries; } ;
struct TYPE_6__ {TYPE_3__* p_ipma; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
typedef  TYPE_2__ MP4_Box_t ;
typedef  TYPE_3__ MP4_Box_data_ipma_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 

__attribute__((used)) static void MP4_FreeBox_ipma( MP4_Box_t *p_box )
{
    MP4_Box_data_ipma_t *p_data = p_box->data.p_ipma;
    for( uint32_t i=0; i<p_data->i_entry_count; i++ )
        free( p_data->p_entries[i].p_assocs );
    free( p_data->p_entries );
}