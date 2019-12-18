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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_5__ {unsigned int i_anc_size; unsigned int i_active_size; int i_line_buffer; int /*<<< orphan*/  const* p_line_buffer; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const uint8_t *GetLine( demux_t *p_demux, const uint8_t **pp_parser,
                               const uint8_t *p_end )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    unsigned int i_total_size = p_sys->i_anc_size + p_sys->i_active_size;
    const uint8_t *p_tmp;

    if ( p_sys->i_line_buffer )
    {
        unsigned int i_remaining = i_total_size - p_sys->i_line_buffer;
        memcpy( p_sys->p_line_buffer + p_sys->i_line_buffer,
                                   *pp_parser, i_remaining );
        *pp_parser += i_remaining;
        p_sys->i_line_buffer = 0;

        return p_sys->p_line_buffer;
    }

    if ( p_end - *pp_parser < (int)i_total_size )
    {
        memcpy( p_sys->p_line_buffer, *pp_parser,
                                   p_end - *pp_parser );
        p_sys->i_line_buffer = p_end - *pp_parser;
        return NULL;
    }

    p_tmp = *pp_parser;
    *pp_parser += i_total_size;
    return p_tmp;
}