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

/* Variables and functions */
#define  INPUT_CONTROL_JUMP_POSITION 144 
#define  INPUT_CONTROL_JUMP_TIME 143 
#define  INPUT_CONTROL_NAV_ACTIVATE 142 
#define  INPUT_CONTROL_NAV_DOWN 141 
#define  INPUT_CONTROL_NAV_LEFT 140 
#define  INPUT_CONTROL_NAV_MENU 139 
#define  INPUT_CONTROL_NAV_POPUP 138 
#define  INPUT_CONTROL_NAV_RIGHT 137 
#define  INPUT_CONTROL_NAV_UP 136 
#define  INPUT_CONTROL_SET_POSITION 135 
#define  INPUT_CONTROL_SET_SEEKPOINT 134 
#define  INPUT_CONTROL_SET_SEEKPOINT_NEXT 133 
#define  INPUT_CONTROL_SET_SEEKPOINT_PREV 132 
#define  INPUT_CONTROL_SET_TIME 131 
#define  INPUT_CONTROL_SET_TITLE 130 
#define  INPUT_CONTROL_SET_TITLE_NEXT 129 
#define  INPUT_CONTROL_SET_TITLE_PREV 128 

__attribute__((used)) static bool ControlIsSeekRequest( int i_type )
{
    switch( i_type )
    {
    case INPUT_CONTROL_SET_POSITION:
    case INPUT_CONTROL_JUMP_POSITION:
    case INPUT_CONTROL_SET_TIME:
    case INPUT_CONTROL_JUMP_TIME:
    case INPUT_CONTROL_SET_TITLE:
    case INPUT_CONTROL_SET_TITLE_NEXT:
    case INPUT_CONTROL_SET_TITLE_PREV:
    case INPUT_CONTROL_SET_SEEKPOINT:
    case INPUT_CONTROL_SET_SEEKPOINT_NEXT:
    case INPUT_CONTROL_SET_SEEKPOINT_PREV:
    case INPUT_CONTROL_NAV_ACTIVATE:
    case INPUT_CONTROL_NAV_UP:
    case INPUT_CONTROL_NAV_DOWN:
    case INPUT_CONTROL_NAV_LEFT:
    case INPUT_CONTROL_NAV_RIGHT:
    case INPUT_CONTROL_NAV_POPUP:
    case INPUT_CONTROL_NAV_MENU:
        return true;
    default:
        return false;
    }
}