#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct block_extension_t {int b_progressive; int i_nb_fields; int b_top_field_first; scalar_t__ i_aspect; } ;
struct TYPE_7__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {int i_vblock_size; int i_width; int i_height; scalar_t__ i_incr; int /*<<< orphan*/  i_next_vdate; int /*<<< orphan*/  p_es_video; scalar_t__ i_aspect; scalar_t__ i_forced_aspect; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  Unpack01 (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unpack2 (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unpack3 (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_3__* block_Alloc (int) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct block_extension_t*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int HandleVideo( demux_t *p_demux, const uint8_t *p_buffer )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t *p_current_picture = block_Alloc( p_sys->i_vblock_size );
    if( unlikely( !p_current_picture ) )
        return VLC_ENOMEM;
    uint8_t *p_y = p_current_picture->p_buffer;
    uint8_t *p_u = p_y + p_sys->i_width * p_sys->i_height;
    uint8_t *p_v = p_u + p_sys->i_width * p_sys->i_height / 4;
    unsigned int i_total_size = p_sys->i_width * 2;
    unsigned int i_current_line;
    struct block_extension_t ext;

    for ( i_current_line = 0; i_current_line < p_sys->i_height;
          i_current_line++ )
    {
        bool b_field = (i_current_line >= p_sys->i_height / 2);
        unsigned int i_field_line = b_field ?
            i_current_line - (p_sys->i_height + 1) / 2 :
            i_current_line;
        unsigned int i_real_line = b_field + i_field_line * 2;
        const uint8_t *p_line = p_buffer + i_current_line * p_sys->i_width * 2;

        if ( !(i_field_line % 2) && !b_field )
            Unpack01( p_line, i_total_size,
                      p_y + p_sys->i_width * i_real_line,
                      p_u + (p_sys->i_width / 2) * (i_real_line / 2),
                      p_v + (p_sys->i_width / 2) * (i_real_line / 2) );
        else if ( !(i_field_line % 2) )
            Unpack01( p_line, i_total_size,
                      p_y + p_sys->i_width * i_real_line,
                      p_u + (p_sys->i_width / 2) * (i_real_line / 2 + 1),
                      p_v + (p_sys->i_width / 2) * (i_real_line / 2 + 1) );
       else if ( !b_field )
            Unpack2( p_line, i_total_size,
                     p_y + p_sys->i_width * i_real_line,
                     p_u + (p_sys->i_width / 2) * (i_real_line / 2 - 1),
                     p_v + (p_sys->i_width / 2) * (i_real_line / 2 - 1) );
       else
            Unpack3( p_line, i_total_size,
                     p_y + p_sys->i_width * i_real_line,
                     p_u + (p_sys->i_width / 2) * (i_real_line / 2),
                     p_v + (p_sys->i_width / 2) * (i_real_line / 2) );
    }

    /* FIXME: progressive formats ? */
    ext.b_progressive = false;
    ext.i_nb_fields = 2;
    ext.b_top_field_first = true;
    ext.i_aspect = p_sys->i_forced_aspect ? p_sys->i_forced_aspect :
                   p_sys->i_aspect;

    memcpy( &p_current_picture->p_buffer[p_sys->i_vblock_size
                                          - sizeof(struct block_extension_t)],
            &ext, sizeof(struct block_extension_t) );

    p_current_picture->i_dts = p_current_picture->i_pts = p_sys->i_next_vdate;
    es_out_Send( p_demux->out, p_sys->p_es_video, p_current_picture );

    es_out_SetPCR( p_demux->out, p_sys->i_next_vdate );
    p_sys->i_next_vdate += p_sys->i_incr;
    return VLC_SUCCESS;
}