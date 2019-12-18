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
struct TYPE_3__ {int i_frame_size; unsigned int i_frame_length; } ;
typedef  TYPE_1__ vlc_dts_header_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_DTS_HEADER_SIZE ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (unsigned int*) ; 
 scalar_t__ vlc_dts_header_Parse (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DtsCheckSync( const uint8_t *p_peek, unsigned *pi_samples )
{
    VLC_UNUSED(pi_samples);

    vlc_dts_header_t dts;
    if( vlc_dts_header_Parse( &dts, p_peek, VLC_DTS_HEADER_SIZE ) == VLC_SUCCESS
     && dts.i_frame_size > 0 && dts.i_frame_size <= 8192 )
    {
        if( pi_samples )
            *pi_samples = dts.i_frame_length;
        return dts.i_frame_size;
    }
    else
        return VLC_EGENERIC;
}