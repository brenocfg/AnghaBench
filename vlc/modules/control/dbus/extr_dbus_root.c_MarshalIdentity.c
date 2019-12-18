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
typedef  int /*<<< orphan*/  intf_thread_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int
MarshalIdentity( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    const char *psz_id = _("VLC media player");

    if (!dbus_message_iter_append_basic( container, DBUS_TYPE_STRING, &psz_id ))
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}