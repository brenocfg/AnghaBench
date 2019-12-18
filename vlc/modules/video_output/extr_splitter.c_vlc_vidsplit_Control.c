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
typedef  int /*<<< orphan*/  vout_display_t ;
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
#define  VOUT_DISPLAY_CHANGE_DISPLAY_FILLED 132 
#define  VOUT_DISPLAY_CHANGE_DISPLAY_SIZE 131 
#define  VOUT_DISPLAY_CHANGE_SOURCE_ASPECT 130 
#define  VOUT_DISPLAY_CHANGE_SOURCE_CROP 129 
#define  VOUT_DISPLAY_CHANGE_ZOOM 128 

__attribute__((used)) static int vlc_vidsplit_Control(vout_display_t *vd, int query, va_list args)
{
    (void) vd; (void) args;

    switch (query) {
        case VOUT_DISPLAY_CHANGE_DISPLAY_SIZE:
        case VOUT_DISPLAY_CHANGE_DISPLAY_FILLED:
        case VOUT_DISPLAY_CHANGE_ZOOM:
        case VOUT_DISPLAY_CHANGE_SOURCE_ASPECT:
        case VOUT_DISPLAY_CHANGE_SOURCE_CROP:
            return VLC_SUCCESS;
    }
    return VLC_EGENERIC;
}