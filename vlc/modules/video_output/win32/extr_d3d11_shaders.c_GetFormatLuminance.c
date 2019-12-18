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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int transfer; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 float DEFAULT_BRIGHTNESS ; 
 float MAX_HLG_BRIGHTNESS ; 
 float MAX_PQ_BRIGHTNESS ; 
#define  TRANSFER_FUNC_BT470_BG 133 
#define  TRANSFER_FUNC_BT470_M 132 
#define  TRANSFER_FUNC_BT709 131 
#define  TRANSFER_FUNC_HLG 130 
#define  TRANSFER_FUNC_SMPTE_ST2084 129 
#define  TRANSFER_FUNC_SRGB 128 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int) ; 

float GetFormatLuminance(vlc_object_t *o, const video_format_t *fmt)
{
    switch (fmt->transfer)
    {
        case TRANSFER_FUNC_SMPTE_ST2084:
            /* that's the default PQ value if the metadata are not set */
            return MAX_PQ_BRIGHTNESS;
        case TRANSFER_FUNC_HLG:
            return MAX_HLG_BRIGHTNESS;
        case TRANSFER_FUNC_BT470_BG:
        case TRANSFER_FUNC_BT470_M:
        case TRANSFER_FUNC_BT709:
        case TRANSFER_FUNC_SRGB:
            return DEFAULT_BRIGHTNESS;
        default:
            msg_Dbg(o, "unhandled source transfer %d", fmt->transfer);
            return DEFAULT_BRIGHTNESS;
    }
}