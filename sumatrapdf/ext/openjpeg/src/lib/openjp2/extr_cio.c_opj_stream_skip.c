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
struct TYPE_4__ {scalar_t__ (* m_opj_skip ) (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ opj_stream_private_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  scalar_t__ OPJ_OFF_T ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ stub1 (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

OPJ_OFF_T opj_stream_skip(opj_stream_private_t * p_stream, OPJ_OFF_T p_size,
                          opj_event_mgr_t * p_event_mgr)
{
    assert(p_size >= 0);
    return p_stream->m_opj_skip(p_stream, p_size, p_event_mgr);
}