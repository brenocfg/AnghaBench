#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t i_sid; } ;
typedef  TYPE_1__ vlc_keystore_sys ;
struct TYPE_6__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ vlc_keystore ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/ * dbus_message_new_method_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * ppsz_sAddr ; 
 int /*<<< orphan*/ * ppsz_sPath ; 
 int /*<<< orphan*/  psz_kwallet_interface ; 

__attribute__((used)) static DBusMessage*
vlc_dbus_new_method( vlc_keystore* p_keystore, const char* psz_method )
{
    vlc_keystore_sys* p_sys = p_keystore->p_sys;
    DBusMessage* msg;

    msg = dbus_message_new_method_call( ppsz_sAddr[p_sys->i_sid],
                                        ppsz_sPath[p_sys->i_sid],
                                        psz_kwallet_interface,
                                        psz_method );
    if ( !msg )
    {
        msg_Err( p_keystore, "vlc_dbus_new_method : Failed to create message" );
        return NULL;
    }

    return msg;
}