#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_beginx; int i_beginy; int i_lasty; int b_2fingers; int i_type; scalar_t__ i_ullArguments; int /*<<< orphan*/  i_action; } ;
typedef  TYPE_2__ win32_gesture_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int x; int y; } ;
struct TYPE_8__ {int dwID; int dwFlags; scalar_t__ ullArguments; TYPE_1__ ptsLocation; } ;
typedef  TYPE_3__ GESTUREINFO ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ACTIONID_JUMP_BACKWARD_MEDIUM ; 
 int ACTIONID_JUMP_BACKWARD_SHORT ; 
 int ACTIONID_JUMP_FORWARD_MEDIUM ; 
 int ACTIONID_JUMP_FORWARD_SHORT ; 
 int ACTIONID_LEAVE_FULLSCREEN ; 
 int ACTIONID_PLAY_PAUSE ; 
 int ACTIONID_TOGGLE_FULLSCREEN ; 
 int ACTIONID_VOL_DOWN ; 
 int ACTIONID_VOL_UP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GESTURE_ACTION_BRIGHTNESS ; 
 int /*<<< orphan*/  GESTURE_ACTION_JUMP ; 
 int /*<<< orphan*/  GESTURE_ACTION_UNDEFINED ; 
 int /*<<< orphan*/  GESTURE_ACTION_VOLUME ; 
#define  GF_BEGIN 135 
#define  GF_END 134 
#define  GID_BEGIN 133 
#define  GID_END 132 
#define  GID_PAN 131 
#define  GID_TWOFINGERTAP 130 
#define  GID_ZOOM 129 
 int /*<<< orphan*/  TRUE ; 
#define  WM_VSCROLL 128 
 int abs (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL DecodeGestureAction( vlc_object_t *p_this, win32_gesture_sys_t *p_gesture, const GESTUREINFO* p_gi )
{
    BOOL bHandled = FALSE; /* Needed to release the handle */
    switch ( p_gi->dwID )
    {
        case GID_BEGIN:
            /* Set the win32_gesture_sys_t values */
            p_gesture->i_beginx      = p_gi->ptsLocation.x;
            p_gesture->i_beginy      = p_gi->ptsLocation.y;
            p_gesture->i_lasty       = p_gesture->i_beginy;
            p_gesture->b_2fingers    = false;
            break;
        case GID_END:
            if( p_gesture->i_type != 0 &&
                p_gesture->i_action == GESTURE_ACTION_JUMP )
            {
                int action_id;
                if( p_gesture->i_beginx > p_gi->ptsLocation.x )
                {
                    if( p_gesture->b_2fingers )
                        action_id = ACTIONID_JUMP_BACKWARD_MEDIUM;
                    else
                        action_id = ACTIONID_JUMP_BACKWARD_SHORT;
                }
                else
                {
                    if( p_gesture->b_2fingers )
                        action_id = ACTIONID_JUMP_FORWARD_MEDIUM;
                    else
                        action_id = ACTIONID_JUMP_FORWARD_SHORT;
                }
                var_SetInteger( vlc_object_instance(p_this), "key-action", action_id );
            }
            /* Reset the values */
            p_gesture->i_action = GESTURE_ACTION_UNDEFINED;
            p_gesture->i_type = p_gesture->i_beginx = p_gesture->i_beginy = -1;
            p_gesture->b_2fingers = false;
            break;
        case GID_PAN:
            p_gesture->i_type = GID_PAN;
            bHandled = TRUE;

            if (p_gi->dwFlags & GF_BEGIN) {
                p_gesture->i_beginx = p_gi->ptsLocation.x;
                p_gesture->i_beginy = p_gi->ptsLocation.y;
            }

            if( (DWORD)p_gi->ullArguments > 0 )
                p_gesture->b_2fingers = true;

            if( p_gesture->i_action == GESTURE_ACTION_UNDEFINED )
            {
                if( abs( p_gesture->i_beginx - p_gi->ptsLocation.x ) +
                    abs( p_gesture->i_beginy - p_gi->ptsLocation.y ) > 50 )
                {
                    if( abs( p_gesture->i_beginx - p_gi->ptsLocation.x ) >
                        abs( p_gesture->i_beginy - p_gi->ptsLocation.y ) )
                       p_gesture->i_action =  GESTURE_ACTION_JUMP;
                    else if ( p_gesture->b_2fingers )
                       p_gesture->i_action = GESTURE_ACTION_BRIGHTNESS;
                    else
                       p_gesture->i_action =  GESTURE_ACTION_VOLUME;
                }
            }

            if( p_gesture->i_action == GESTURE_ACTION_VOLUME )
            {
                int offset = p_gesture->i_lasty - p_gi->ptsLocation.y;

                if( offset > 100)
                    var_SetInteger( vlc_object_instance(p_this), "key-action", ACTIONID_VOL_UP );
                else if( offset < -100)
                    var_SetInteger( vlc_object_instance(p_this), "key-action", ACTIONID_VOL_DOWN );
                else
                    break;

                p_gesture->i_lasty = p_gi->ptsLocation.y;
            }
            else if ( p_gesture->i_action == GESTURE_ACTION_BRIGHTNESS )
            {
                /* Currently unimplemented
                if( p_gesture->i_lasty == -1 )
                    p_gesture->i_lasty = p_gesture->i_beginy;

                if( p_gesture->i_lasty - p_gesture->i_beginy > 80 )
                {
                    var_SetInteger( vlc_object_instance(p_this), "key-action", ACTIONID_BRIGHTNESS_DOWN );
                    p_gesture->i_lasty = p_gi->ptsLocation.y;
                }
                else if ( p_gesture->i_lasty - p_gesture->i_beginy < 80 )
                {
                    var_SetInteger( vlc_object_instance(p_this), "key-action", ACTIONID_BRIGHTNESS_UP );
                    p_gesture->i_lasty = p_gi->ptsLocation.y;
                } */
            }
            break;
        case GID_TWOFINGERTAP:
            p_gesture->i_type = GID_TWOFINGERTAP;
            var_SetInteger( vlc_object_instance(p_this), "key-action", ACTIONID_PLAY_PAUSE );
            bHandled = TRUE;
            break;
        case GID_ZOOM:
            p_gesture->i_type = GID_ZOOM;
            switch( p_gi->dwFlags )
            {
                case GF_BEGIN:
                    p_gesture->i_ullArguments = p_gi->ullArguments;
                    break;
                case GF_END:
                    {
                        double k = (double)(p_gi->ullArguments) /
                                   (double)(p_gesture->i_ullArguments);
                        if( k > 1 )
                            var_SetInteger( vlc_object_instance(p_this), "key-action",
                                    ACTIONID_TOGGLE_FULLSCREEN );
                        else
                            var_SetInteger( vlc_object_instance(p_this), "key-action",
                                    ACTIONID_LEAVE_FULLSCREEN );
                    }
                    break;
                default:
                    msg_Err( p_this, "Unmanaged dwFlag: %lx", p_gi->dwFlags );
            }
            bHandled = TRUE;
            break;
        case WM_VSCROLL:
            bHandled = TRUE;
            break;
        default:
            break;
    }
    return bHandled;
}