#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_default_sample_size; int /*<<< orphan*/  i_default_sample_duration; } ;
struct TYPE_4__ {int i_flags; int /*<<< orphan*/  i_track_ID; int /*<<< orphan*/  i_default_sample_size; int /*<<< orphan*/  i_default_sample_duration; } ;
typedef  int /*<<< orphan*/  MP4_Box_t ;
typedef  TYPE_1__ MP4_Box_data_tfhd_t ;

/* Variables and functions */
 TYPE_3__* BOXDATA (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * MP4_GetTrexByTrackID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MP4_TFHD_DFLT_SAMPLE_DURATION ; 
 int MP4_TFHD_DFLT_SAMPLE_SIZE ; 

__attribute__((used)) static void MP4_GetDefaultSizeAndDuration( MP4_Box_t *p_moov,
                                           const MP4_Box_data_tfhd_t *p_tfhd_data,
                                           uint32_t *pi_default_size,
                                           uint32_t *pi_default_duration )
{
    if( p_tfhd_data->i_flags & MP4_TFHD_DFLT_SAMPLE_DURATION )
        *pi_default_duration = p_tfhd_data->i_default_sample_duration;

    if( p_tfhd_data->i_flags & MP4_TFHD_DFLT_SAMPLE_SIZE )
        *pi_default_size = p_tfhd_data->i_default_sample_size;

    if( !*pi_default_duration || !*pi_default_size )
    {
        const MP4_Box_t *p_trex = MP4_GetTrexByTrackID( p_moov, p_tfhd_data->i_track_ID );
        if ( p_trex )
        {
            if ( !*pi_default_duration )
                *pi_default_duration = BOXDATA(p_trex)->i_default_sample_duration;
            if ( !*pi_default_size )
                *pi_default_size = BOXDATA(p_trex)->i_default_sample_size;
        }
    }
}