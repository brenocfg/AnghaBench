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
typedef  int UINT ;

/* Variables and functions */
#define  WM_ACTIVATE 168 
#define  WM_ACTIVATEAPP 167 
#define  WM_CHILDACTIVATE 166 
#define  WM_COMMAND 165 
#define  WM_CREATE 164 
#define  WM_CTLCOLORSTATIC 163 
#define  WM_DESTROY 162 
#define  WM_ERASEBKGND 161 
#define  WM_GETICON 160 
#define  WM_GETMINMAXINFO 159 
#define  WM_KEYDOWN 158 
#define  WM_KEYUP 157 
#define  WM_KILLFOCUS 156 
#define  WM_MOUSEHOVER 155 
#define  WM_MOUSELEAVE 154 
#define  WM_MOUSEMOVE 153 
#define  WM_MOVE 152 
#define  WM_NCACTIVATE 151 
#define  WM_NCCALCSIZE 150 
#define  WM_NCCREATE 149 
#define  WM_NCDESTROY 148 
#define  WM_NCHITTEST 147 
#define  WM_NCMOUSEHOVER 146 
#define  WM_NCMOUSELEAVE 145 
#define  WM_NCPAINT 144 
#define  WM_NOTIFY 143 
#define  WM_PAINT 142 
#define  WM_PARENTNOTIFY 141 
#define  WM_PRINTCLIENT 140 
#define  WM_QUERYNEWPALETTE 139 
#define  WM_SETCURSOR 138 
#define  WM_SETFOCUS 137 
#define  WM_SETICON 136 
#define  WM_SETTINGCHANGE 135 
#define  WM_SHOWWINDOW 134 
#define  WM_SIZE 133 
#define  WM_STYLECHANGED 132 
#define  WM_STYLECHANGING 131 
#define  WM_SYSTIMER 130 
#define  WM_WINDOWPOSCHANGED 129 
#define  WM_WINDOWPOSCHANGING 128 

__attribute__((used)) static char* get_msg_name(UINT msg)
{
    switch(msg)
    {
        case WM_CREATE: return "WM_CREATE";
        case WM_NCCREATE: return "WM_NCCREATE";
        case WM_PARENTNOTIFY: return "WM_PARENTNOTIFY";
        case WM_DESTROY: return "WM_DESTROY";
        case WM_NCDESTROY: return "WM_NCDESTROY";
        case WM_CHILDACTIVATE: return "WM_CHILDACTIVATE";
        case WM_NCACTIVATE: return "WM_NCACTIVATE";
        case WM_ACTIVATE: return "WM_ACTIVATE";
        case WM_ACTIVATEAPP: return "WM_ACTIVATEAPP";
        case WM_WINDOWPOSCHANGING: return "WM_WINDOWPOSCHANGING";
        case WM_WINDOWPOSCHANGED: return "WM_WINDOWPOSCHANGED";
        case WM_SETFOCUS: return "WM_SETFOCUS";
        case WM_KILLFOCUS: return "WM_KILLFOCUS";
        case WM_NCPAINT: return "WM_NCPAINT";
        case WM_PAINT: return "WM_PAINT";
        case WM_ERASEBKGND: return "WM_ERASEBKGND";
        case WM_SIZE: return "WM_SIZE";
        case WM_MOVE: return "WM_MOVE";
        case WM_SHOWWINDOW: return "WM_SHOWWINDOW";
        case WM_QUERYNEWPALETTE: return "WM_QUERYNEWPALETTE";
        case WM_MOUSELEAVE: return "WM_MOUSELEAVE";
        case WM_MOUSEHOVER: return "WM_MOUSEHOVER";
        case WM_NCMOUSELEAVE: return "WM_NCMOUSELEAVE";
        case WM_NCMOUSEHOVER: return "WM_NCMOUSEHOVER";
        case WM_NCHITTEST: return "WM_NCHITTEST";
        case WM_SETCURSOR: return "WM_SETCURSOR";
        case WM_MOUSEMOVE: return "WM_MOUSEMOVE";
        case WM_SYSTIMER: return "WM_SYSTIMER";
        case WM_GETMINMAXINFO: return "WM_GETMINMAXINFO";
        case WM_NCCALCSIZE: return "WM_NCCALCSIZE";
        case WM_SETTINGCHANGE: return "WM_SETTINGCHANGE";
        case WM_GETICON: return "WM_GETICON";
        case WM_SETICON: return "WM_SETICON";
        case WM_KEYDOWN: return "WM_KEYDOWN";
        case WM_KEYUP: return "WM_KEYUP";
        case WM_NOTIFY: return "WM_NOTIFY";
        case WM_COMMAND: return "WM_COMMAND";
        case WM_PRINTCLIENT: return "WM_PRINTCLIENT";
        case WM_CTLCOLORSTATIC: return "WM_CTLCOLORSTATIC";
        case WM_STYLECHANGING: return "WM_STYLECHANGING";
        case WM_STYLECHANGED: return "WM_STYLECHANGED";
        default: return NULL;
    }
}