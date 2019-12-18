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
struct TYPE_4__ {scalar_t__ id; } ;
typedef  TYPE_1__ opj_dec_memory_marker_handler_t ;
typedef  scalar_t__ OPJ_UINT32 ;

/* Variables and functions */
 TYPE_1__* j2k_memory_marker_handler_tab ; 

__attribute__((used)) static const opj_dec_memory_marker_handler_t * opj_j2k_get_marker_handler(
    OPJ_UINT32 p_id)
{
    const opj_dec_memory_marker_handler_t *e;
    for (e = j2k_memory_marker_handler_tab; e->id != 0; ++e) {
        if (e->id == p_id) {
            break; /* we find a handler corresponding to the marker ID*/
        }
    }
    return e;
}