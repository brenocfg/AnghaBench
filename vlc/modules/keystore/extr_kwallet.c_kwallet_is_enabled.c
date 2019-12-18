#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_keystore ;
typedef  int dbus_bool_t ;
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  TYPE_1__ DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  dbus_error_init (TYPE_1__*) ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_method_call (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * ppsz_sAddr ; 
 int /*<<< orphan*/ * vlc_dbus_send_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kwallet_is_enabled( vlc_keystore* p_keystore, int i_sid, bool* b_is_enabled )
{
    VLC_UNUSED( p_keystore );
    DBusMessage* msg = NULL;
    DBusMessage* repmsg = NULL;
    DBusMessageIter args;
    DBusError error;
    dbus_bool_t b_reply;
    int i_ret = VLC_EGENERIC;

    /* init */
    msg = dbus_message_new_method_call( "org.freedesktop.DBus",
                                        "/",
                                        "org.freedesktop.DBus",
                                        "NameHasOwner" );
    if ( !msg )
    {
        msg_Err( p_keystore, "vlc_dbus_new_method : Failed to create message" );
        goto end;
    }

    /* argument init */
    dbus_message_iter_init_append( msg, &args );
    if ( !dbus_message_iter_append_basic( &args, DBUS_TYPE_STRING, &ppsz_sAddr[i_sid] ) )
        goto end;

    /* sending message */
    repmsg = vlc_dbus_send_message( p_keystore, msg );
    if ( !repmsg )
    {
        msg_Err( p_keystore, "kwallet_is_enabled : vlc_dbus_send_message failed");
        goto end;
    }

    /* handling reply */
    dbus_error_init( &error );
    if ( !dbus_message_get_args( repmsg, &error, DBUS_TYPE_BOOLEAN,
                                 &b_reply, DBUS_TYPE_INVALID ) )
    {
        msg_Err( p_keystore, "kwallet_is_enabled : "
                 "dbus_message_get_args failed\n%s", error.message );
        dbus_error_free( &error );
        goto end;
    }

    *b_is_enabled = b_reply;

    i_ret = VLC_SUCCESS;

end:

    if ( msg )
        dbus_message_unref( msg );
    if ( repmsg )
        dbus_message_unref( repmsg );

    return i_ret;
}