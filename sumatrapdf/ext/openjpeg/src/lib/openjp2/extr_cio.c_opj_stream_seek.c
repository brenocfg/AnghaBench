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
struct opj_event_mgr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* m_opj_seek ) (TYPE_1__*,scalar_t__,struct opj_event_mgr*) ;} ;
typedef  TYPE_1__ opj_stream_private_t ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__,struct opj_event_mgr*) ; 

OPJ_BOOL opj_stream_seek(opj_stream_private_t * p_stream, OPJ_OFF_T p_size,
                         struct opj_event_mgr * p_event_mgr)
{
    assert(p_size >= 0);
    return p_stream->m_opj_seek(p_stream, p_size, p_event_mgr);
}