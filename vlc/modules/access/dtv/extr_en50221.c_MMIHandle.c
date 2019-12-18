#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ cam_t ;

/* Variables and functions */
#define  AOT_CLOSE_MMI 133 
#define  AOT_DISPLAY_CONTROL 132 
#define  AOT_ENQ 131 
#define  AOT_LIST_LAST 130 
#define  AOT_MENU_LAST 129 
 int* APDUGetLength (int*,int*) ; 
 int APDUGetTag (int*,int) ; 
#define  DCC_SET_MMI_MODE 128 
 int /*<<< orphan*/  MMIDisplayReply (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MMIHandleEnq (TYPE_1__*,int,int*,int) ; 
 int /*<<< orphan*/  MMIHandleMenu (TYPE_1__*,int,int,int*,int) ; 
 int MM_HIGH_LEVEL ; 
 int /*<<< orphan*/  SessionSendClose (TYPE_1__*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void MMIHandle( cam_t *p_cam, int i_session_id,
                       uint8_t *p_apdu, int i_size )
{
    int i_tag = APDUGetTag( p_apdu, i_size );

    switch ( i_tag )
    {
    case AOT_DISPLAY_CONTROL:
    {
        int l;
        uint8_t *d = APDUGetLength( p_apdu, &l );

        if ( l > 0 )
        {
            switch ( *d )
            {
            case DCC_SET_MMI_MODE:
                if ( l == 2 && d[1] == MM_HIGH_LEVEL )
                    MMIDisplayReply( p_cam, i_session_id );
                else
                    msg_Err( p_cam->obj, "unsupported MMI mode %02x", d[1] );
                break;

            default:
                msg_Err( p_cam->obj, "unsupported display control command %02x",
                         *d );
                break;
            }
        }
        break;
    }

    case AOT_ENQ:
        MMIHandleEnq( p_cam, i_session_id, p_apdu, i_size );
        break;

    case AOT_LIST_LAST:
    case AOT_MENU_LAST:
        MMIHandleMenu( p_cam, i_session_id, i_tag, p_apdu, i_size );
        break;

    case AOT_CLOSE_MMI:
        SessionSendClose( p_cam, i_session_id );
        break;

    default:
        msg_Err( p_cam->obj, "unexpected tag in MMIHandle (0x%x)", i_tag );
    }
}