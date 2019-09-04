#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int WPARAM ;
struct TYPE_13__ {int x; int y; } ;
struct TYPE_20__ {int /*<<< orphan*/  mouseData; TYPE_1__ pt; } ;
struct TYPE_19__ {int x; int y; } ;
struct TYPE_15__ {TYPE_2__* user_df; } ;
struct TYPE_17__ {int dwCoopLevel; int /*<<< orphan*/  crit; TYPE_4__* dinput; TYPE_3__ data_format; } ;
struct TYPE_12__ {int lX; int lY; int lZ; int* rgbButtons; } ;
struct TYPE_18__ {int clipped; TYPE_5__ base; TYPE_10__ m_state; int /*<<< orphan*/  need_warp; int /*<<< orphan*/  warp_override; } ;
struct TYPE_16__ {int /*<<< orphan*/  evsequence; } ;
struct TYPE_14__ {int dwFlags; } ;
typedef  TYPE_6__ SysMouseImpl ;
typedef  TYPE_7__ POINT ;
typedef  TYPE_8__ MSLLHOOKSTRUCT ;
typedef  int /*<<< orphan*/  LPDIRECTINPUTDEVICE8A ;
typedef  scalar_t__ LPARAM ;

/* Variables and functions */
 int DIDFT_MAKEINSTANCE (scalar_t__) ; 
 int DIDFT_PSHBUTTON ; 
 int DIDFT_RELAXIS ; 
 int DIDF_ABSAXIS ; 
 int DISCL_EXCLUSIVE ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentTime () ; 
 int /*<<< orphan*/  GetCursorPos (TYPE_7__*) ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARP_DISABLE ; 
 int /*<<< orphan*/  WARP_FORCE_ON ; 
 scalar_t__ WINE_MOUSE_BUTTONS_INSTANCE ; 
 scalar_t__ WINE_MOUSE_X_AXIS_INSTANCE ; 
 scalar_t__ WINE_MOUSE_Y_AXIS_INSTANCE ; 
 scalar_t__ WINE_MOUSE_Z_AXIS_INSTANCE ; 
#define  WM_LBUTTONDOWN 137 
#define  WM_LBUTTONUP 136 
#define  WM_MBUTTONDOWN 135 
#define  WM_MBUTTONUP 134 
#define  WM_MOUSEMOVE 133 
#define  WM_MOUSEWHEEL 132 
#define  WM_RBUTTONDOWN 131 
#define  WM_RBUTTONUP 130 
#define  WM_XBUTTONDOWN 129 
#define  WM_XBUTTONUP 128 
 int /*<<< orphan*/  _dump_mouse_state (TYPE_10__*) ; 
 TYPE_6__* impl_from_IDirectInputDevice8A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_event (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dinput_mouse_hook( LPDIRECTINPUTDEVICE8A iface, WPARAM wparam, LPARAM lparam )
{
    MSLLHOOKSTRUCT *hook = (MSLLHOOKSTRUCT *)lparam;
    SysMouseImpl* This = impl_from_IDirectInputDevice8A(iface);
    int wdata = 0, inst_id = -1, ret = 0;

    TRACE("msg %lx @ (%d %d)\n", wparam, hook->pt.x, hook->pt.y);

    EnterCriticalSection(&This->base.crit);

    switch(wparam) {
        case WM_MOUSEMOVE:
        {
            POINT pt, pt1;

            GetCursorPos(&pt);
            This->m_state.lX += pt.x = hook->pt.x - pt.x;
            This->m_state.lY += pt.y = hook->pt.y - pt.y;

            if (This->base.data_format.user_df->dwFlags & DIDF_ABSAXIS)
            {
                pt1.x = This->m_state.lX;
                pt1.y = This->m_state.lY;
            } else
                pt1 = pt;

            if (pt.x)
            {
                inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_X_AXIS_INSTANCE) | DIDFT_RELAXIS;
                wdata = pt1.x;
            }
            if (pt.y)
            {
                /* Already have X, need to queue it */
                if (inst_id != -1)
                    queue_event(iface, inst_id,
                                wdata, GetCurrentTime(), This->base.dinput->evsequence);
                inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_Y_AXIS_INSTANCE) | DIDFT_RELAXIS;
                wdata = pt1.y;
            }

            if (pt.x || pt.y)
            {
                if ((This->warp_override == WARP_FORCE_ON) ||
                    (This->warp_override != WARP_DISABLE && (This->base.dwCoopLevel & DISCL_EXCLUSIVE)))
                    This->need_warp = TRUE;
            }
            break;
        }
        case WM_MOUSEWHEEL:
            inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_Z_AXIS_INSTANCE) | DIDFT_RELAXIS;
            This->m_state.lZ += wdata = (short)HIWORD(hook->mouseData);
            /* FarCry crashes if it gets a mouse wheel message */
            /* FIXME: should probably filter out other messages too */
            ret = This->clipped;
            break;
        case WM_LBUTTONDOWN:
            inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_BUTTONS_INSTANCE + 0) | DIDFT_PSHBUTTON;
            This->m_state.rgbButtons[0] = wdata = 0x80;
	    break;
	case WM_LBUTTONUP:
            inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_BUTTONS_INSTANCE + 0) | DIDFT_PSHBUTTON;
            This->m_state.rgbButtons[0] = wdata = 0x00;
	    break;
	case WM_RBUTTONDOWN:
            inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_BUTTONS_INSTANCE + 1) | DIDFT_PSHBUTTON;
            This->m_state.rgbButtons[1] = wdata = 0x80;
	    break;
	case WM_RBUTTONUP:
            inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_BUTTONS_INSTANCE + 1) | DIDFT_PSHBUTTON;
            This->m_state.rgbButtons[1] = wdata = 0x00;
	    break;
	case WM_MBUTTONDOWN:
            inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_BUTTONS_INSTANCE + 2) | DIDFT_PSHBUTTON;
            This->m_state.rgbButtons[2] = wdata = 0x80;
	    break;
	case WM_MBUTTONUP:
            inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_BUTTONS_INSTANCE + 2) | DIDFT_PSHBUTTON;
            This->m_state.rgbButtons[2] = wdata = 0x00;
	    break;
        case WM_XBUTTONDOWN:
            inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_BUTTONS_INSTANCE + 2 + HIWORD(hook->mouseData)) | DIDFT_PSHBUTTON;
            This->m_state.rgbButtons[2 + HIWORD(hook->mouseData)] = wdata = 0x80;
            break;
        case WM_XBUTTONUP:
            inst_id = DIDFT_MAKEINSTANCE(WINE_MOUSE_BUTTONS_INSTANCE + 2 + HIWORD(hook->mouseData)) | DIDFT_PSHBUTTON;
            This->m_state.rgbButtons[2 + HIWORD(hook->mouseData)] = wdata = 0x00;
            break;
    }


    if (inst_id != -1)
    {
        _dump_mouse_state(&This->m_state);
        queue_event(iface, inst_id,
                    wdata, GetCurrentTime(), This->base.dinput->evsequence++);
    }

    LeaveCriticalSection(&This->base.crit);
    return ret;
}