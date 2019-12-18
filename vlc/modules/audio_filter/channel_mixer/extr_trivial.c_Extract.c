#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pi_selections ;
struct TYPE_17__ {size_t i_bitspersample; } ;
struct TYPE_14__ {TYPE_8__ audio; } ;
struct TYPE_12__ {int /*<<< orphan*/  i_channels; } ;
struct TYPE_13__ {TYPE_1__ audio; } ;
struct TYPE_15__ {TYPE_3__ fmt_out; TYPE_2__ fmt_in; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_16__ {size_t i_nb_samples; int /*<<< orphan*/  p_buffer; int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 int AOUT_CHAN_MAX ; 
 int /*<<< orphan*/  aout_ChannelExtract (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int const*,size_t) ; 
 size_t aout_FormatNbChannels (TYPE_8__*) ; 
 TYPE_5__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  block_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *Extract( filter_t *p_filter, block_t *p_in_buf )
{
    size_t i_out_channels = aout_FormatNbChannels( &p_filter->fmt_out.audio );
    size_t i_out_size = p_in_buf->i_nb_samples
                      * p_filter->fmt_out.audio.i_bitspersample
                      * i_out_channels / 8;

    block_t *p_out_buf = block_Alloc( i_out_size );
    if( unlikely(p_out_buf == NULL) )
    {
        block_Release( p_in_buf );
        return NULL;
    }

    p_out_buf->i_nb_samples = p_in_buf->i_nb_samples;
    p_out_buf->i_dts        = p_in_buf->i_dts;
    p_out_buf->i_pts        = p_in_buf->i_pts;
    p_out_buf->i_length     = p_in_buf->i_length;

    static const int pi_selections[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8,
    };
    static_assert(sizeof(pi_selections)/sizeof(int) == AOUT_CHAN_MAX,
                  "channel max size mismatch!");

    aout_ChannelExtract( p_out_buf->p_buffer, i_out_channels,
                         p_in_buf->p_buffer, p_filter->fmt_in.audio.i_channels,
                         p_in_buf->i_nb_samples, pi_selections,
                         p_filter->fmt_out.audio.i_bitspersample );

    block_Release( p_in_buf );
    return p_out_buf;
}