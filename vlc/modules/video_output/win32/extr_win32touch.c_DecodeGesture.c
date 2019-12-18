#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* OurCloseGestureInfoHandle ) (int /*<<< orphan*/ ) ;scalar_t__ (* DecodeGestureImpl ) (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ;scalar_t__ (* OurGetGestureInfo ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_1__ win32_gesture_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int cbSize; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HGESTUREINFO ;
typedef  TYPE_2__ GESTUREINFO ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

LRESULT DecodeGesture( vlc_object_t *p_this, win32_gesture_sys_t *p_gesture,
                       HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    if( !p_gesture )
        return DefWindowProc( hWnd, message, wParam, lParam );

    GESTUREINFO gi;
    ZeroMemory( &gi, sizeof( GESTUREINFO ) );
    gi.cbSize = sizeof( GESTUREINFO );

    BOOL bResult  = p_gesture->OurGetGestureInfo((HGESTUREINFO)lParam, &gi);
    BOOL bHandled = FALSE; /* Needed to release the handle */

    if( bResult )
        bHandled = p_gesture->DecodeGestureImpl(p_this, p_gesture, &gi);
    else
    {
        DWORD dwErr = GetLastError();
        if( dwErr > 0 )
            msg_Err( p_this, "Could not retrieve a valid GESTUREINFO structure" );
    }

    if( bHandled )
    {
        /* Close the Handle, if we handled the gesture, a contrario
         * from the doc example */
        p_gesture->OurCloseGestureInfoHandle((HGESTUREINFO)lParam);
        return 0;
    }
    else
        return DefWindowProc( hWnd, message, wParam, lParam );
}