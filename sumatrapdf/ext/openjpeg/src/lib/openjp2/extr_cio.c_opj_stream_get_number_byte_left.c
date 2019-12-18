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
struct TYPE_3__ {scalar_t__ m_byte_offset; scalar_t__ m_user_data_length; } ;
typedef  TYPE_1__ opj_stream_private_t ;
typedef  scalar_t__ OPJ_UINT64 ;
typedef  scalar_t__ OPJ_OFF_T ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

OPJ_OFF_T opj_stream_get_number_byte_left(const opj_stream_private_t * p_stream)
{
    assert(p_stream->m_byte_offset >= 0);
    assert(p_stream->m_user_data_length >= (OPJ_UINT64)p_stream->m_byte_offset);
    return p_stream->m_user_data_length ?
           (OPJ_OFF_T)(p_stream->m_user_data_length) - p_stream->m_byte_offset :
           0;
}