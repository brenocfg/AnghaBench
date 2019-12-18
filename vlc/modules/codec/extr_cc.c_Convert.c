#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int eia608_status_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_7__ {int const i_field; int /*<<< orphan*/  p_dtvcc; scalar_t__ p_cea708; scalar_t__ p_eia608; int /*<<< orphan*/  i_channel; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_DTVCC_Demuxer_Push (int /*<<< orphan*/ ,scalar_t__ const,int const*) ; 
 int /*<<< orphan*/  Debug (int /*<<< orphan*/ ) ; 
 int EIA608_STATUS_CHANGED ; 
 int EIA608_STATUS_DISPLAY ; 
 int Eia608Parse (scalar_t__,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/ * Subtitle (TYPE_1__*,scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  decoder_QueueSub (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ vlc_tick_from_samples (unsigned int,int) ; 

__attribute__((used)) static void Convert( decoder_t *p_dec, vlc_tick_t i_pts,
                     const uint8_t *p_buffer, size_t i_buffer )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    unsigned i_ticks = 0;
    while( i_buffer >= 3 )
    {
        if( (p_buffer[0] & 0x04) /* Valid bit */ )
        {
            const vlc_tick_t i_spupts = i_pts + vlc_tick_from_samples(i_ticks, 1200/3);
            /* Mask off the specific i_field bit, else some sequences can be lost. */
            if ( p_sys->p_eia608 &&
                (p_buffer[0] & 0x03) == p_sys->i_field )
            {
                eia608_status_t i_status = Eia608Parse( p_sys->p_eia608,
                                                        p_sys->i_channel, &p_buffer[1] );

                /* a caption is ready or removed, process its screen */
                /*
                 * In case of rollup/painton with 1 packet/frame, we need
                 * to update on Changed status.
                 * Batch decoding might be incorrect if those in
                 * large number of commands (mp4, ...) then.
                 * see CEAv1.2zero.trp tests */
                if( i_status & (EIA608_STATUS_DISPLAY | EIA608_STATUS_CHANGED) )
                {
                    Debug(printf("\n"));
                    subpicture_t *p_spu = Subtitle( p_dec, p_sys->p_eia608, i_spupts );
                    if( p_spu )
                        decoder_QueueSub( p_dec, p_spu );
                }
            }
            else if( p_sys->p_cea708 && (p_buffer[0] & 0x03) >= 2 )
            {
                CEA708_DTVCC_Demuxer_Push( p_sys->p_dtvcc, i_spupts, p_buffer );
            }
        }

        i_ticks++;

        i_buffer -= 3;
        p_buffer += 3;
    }
}