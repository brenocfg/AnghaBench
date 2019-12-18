#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vlc_fourcc_t ;
typedef  int /*<<< orphan*/  soxr_datatype_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOXR_FLOAT32_I ; 
 int /*<<< orphan*/  SOXR_FLOAT64_I ; 
 int /*<<< orphan*/  SOXR_INT16_I ; 
 int /*<<< orphan*/  SOXR_INT32_I ; 
#define  VLC_CODEC_FL32 131 
#define  VLC_CODEC_FL64 130 
#define  VLC_CODEC_S16N 129 
#define  VLC_CODEC_S32N 128 

__attribute__((used)) static bool
SoXR_GetFormat( vlc_fourcc_t i_format, soxr_datatype_t *p_type )
{
    switch( i_format )
    {
        case VLC_CODEC_FL64:
            *p_type = SOXR_FLOAT64_I;
            return true;
        case VLC_CODEC_FL32:
            *p_type = SOXR_FLOAT32_I;
            return true;
        case VLC_CODEC_S32N:
            *p_type = SOXR_INT32_I;
            return true;
        case VLC_CODEC_S16N:
            *p_type = SOXR_INT16_I;
            return true;
        default:
            return false;
    }
}