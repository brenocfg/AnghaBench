#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* i_handle; char* psz_app_id; } ;
typedef  TYPE_1__ vlc_keystore_sys ;
struct TYPE_13__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ vlc_keystore ;
struct TYPE_14__ {char* message; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  TYPE_3__ DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INT32 ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  dbus_error_free (TYPE_3__*) ; 
 int /*<<< orphan*/  dbus_error_init (TYPE_3__*) ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ kwallet_has_entry (TYPE_2__*,char*,int*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 char* psz_folder ; 
 int /*<<< orphan*/ * vlc_dbus_new_method (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * vlc_dbus_send_message (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kwallet_remove_entry( vlc_keystore* p_keystore, char* psz_entry_name )
{
    vlc_keystore_sys* p_sys = p_keystore->p_sys;
    DBusMessage* msg = NULL;
    DBusMessage* repmsg = NULL;
    DBusError error;
    DBusMessageIter args;
    int i_reply;
    bool b_has_entry = false;
    int i_ret = VLC_EGENERIC;

    if ( kwallet_has_entry( p_keystore, psz_entry_name, &b_has_entry ) )
    {
        msg_Err( p_keystore, "kwallet_remove_entry : kwallet_has_entry failed" );
        return VLC_EGENERIC;
    }
    if ( !b_has_entry )
    {
        msg_Err( p_keystore, "kwallet_remove_entry : there is no such entry :"
                "%s", psz_entry_name );
        return VLC_EGENERIC;
    }

    /* init */
    if ( !( msg = vlc_dbus_new_method( p_keystore, "removeEntry" ) ) )
    {
        msg_Err( p_keystore, "kwallet_remove_entry : vlc_dbus_new_method failed" );
        return VLC_EGENERIC;
    }

    /* argument init */
    dbus_message_iter_init_append( msg, &args );
    if ( !dbus_message_iter_append_basic( &args, DBUS_TYPE_INT32, &p_sys->i_handle ) ||
         !dbus_message_iter_append_basic( &args, DBUS_TYPE_STRING, &psz_folder ) ||
         !dbus_message_iter_append_basic( &args, DBUS_TYPE_STRING, &psz_entry_name ) ||
         !dbus_message_iter_append_basic( &args, DBUS_TYPE_STRING, &p_sys->psz_app_id ) )
        goto end;

    /* sending message */
    if ( !( repmsg = vlc_dbus_send_message( p_keystore, msg ) ) )
    {
        msg_Err( p_keystore, "kwallet_remove_entry : vlc_dbus_send_message failed" );
        goto end;
    }

    /* handling reply */
    dbus_error_init( &error );
    if ( !dbus_message_get_args( repmsg, &error, DBUS_TYPE_INT32,
                                 &i_reply, DBUS_TYPE_INVALID ) )
    {
        msg_Err( p_keystore, "kwallet_remove entry :"
                 " dbus_message_get_args failed\n%s", error.message );
        dbus_error_free( &error );
        goto end;
    }

    i_ret = VLC_SUCCESS;

end:

    if ( msg )
        dbus_message_unref( msg );
    if ( repmsg )
        dbus_message_unref( repmsg );

    return i_ret;
}