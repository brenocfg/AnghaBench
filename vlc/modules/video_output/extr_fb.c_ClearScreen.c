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
struct TYPE_3__ {int chroma; int video_size; int /*<<< orphan*/  video_ptr; } ;
typedef  TYPE_1__ vout_display_sys_t ;
typedef  int uint32_t ;

/* Variables and functions */
#define  VLC_CODEC_UYVY 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ClearScreen(vout_display_sys_t *sys)
{
    switch (sys->chroma) {
    /* XXX: add other chromas */
    case VLC_CODEC_UYVY: {
        unsigned int j, size = sys->video_size / 4;
        uint32_t *ptr = (uint32_t*)((uintptr_t)(sys->video_ptr + 3) & ~3);
        for(j=0; j < size; j++)
            ptr[j] = 0x10801080;    /* U = V = 16, Y = 128 */
        break;
    }
    default:    /* RGB */
        memset(sys->video_ptr, 0, sys->video_size);
    }
}