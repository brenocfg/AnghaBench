#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  resources ;
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ cam_t ;

/* Variables and functions */
#define  AOT_PROFILE 129 
 int AOT_PROFILE_CHANGE ; 
#define  AOT_PROFILE_ENQ 128 
 int APDUGetTag (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  APDUSend (TYPE_1__*,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RI_APPLICATION_INFORMATION ; 
 int /*<<< orphan*/  RI_CONDITIONAL_ACCESS_SUPPORT ; 
 int /*<<< orphan*/  RI_DATE_TIME ; 
 int /*<<< orphan*/  RI_MMI ; 
 int /*<<< orphan*/  RI_RESOURCE_MANAGER ; 
 int htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ResourceManagerHandle( cam_t * p_cam, int i_session_id,
                                   uint8_t *p_apdu, int i_size )
{
    int i_tag = APDUGetTag( p_apdu, i_size );

    switch ( i_tag )
    {
    case AOT_PROFILE_ENQ:
    {
        int resources[] = { htonl(RI_RESOURCE_MANAGER),
                            htonl(RI_APPLICATION_INFORMATION),
                            htonl(RI_CONDITIONAL_ACCESS_SUPPORT),
                            htonl(RI_DATE_TIME),
                            htonl(RI_MMI)
                          };
        APDUSend( p_cam, i_session_id, AOT_PROFILE, (uint8_t*)resources,
                  sizeof(resources) );
        break;
    }
    case AOT_PROFILE:
        APDUSend( p_cam, i_session_id, AOT_PROFILE_CHANGE, NULL, 0 );
        break;

    default:
        msg_Err( p_cam->obj, "unexpected tag in ResourceManagerHandle (0x%x)",
                 i_tag );
    }
}