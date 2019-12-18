#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned long long psz_wallet; unsigned long long psz_app_id; unsigned int i_handle; } ;
typedef  TYPE_1__ vlc_keystore_sys ;
struct TYPE_14__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ vlc_keystore ;
struct TYPE_15__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  TYPE_3__ DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INT32 ; 
 int /*<<< orphan*/  DBUS_TYPE_INT64 ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  dbus_error_free (TYPE_3__*) ; 
 int /*<<< orphan*/  dbus_error_init (TYPE_3__*) ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ kwallet_create_folder (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ kwallet_has_folder (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  psz_folder ; 
 int /*<<< orphan*/ * vlc_dbus_new_method (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * vlc_dbus_send_message (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kwallet_open( vlc_keystore* p_keystore )
{
    vlc_keystore_sys* p_sys = p_keystore->p_sys;
    DBusMessage* msg = NULL;
    DBusMessage* repmsg = NULL;
    DBusMessageIter args;
    DBusError error;
    unsigned long long ull_win_id = 0;
    unsigned int ui_reply = 1;
    bool b_has_folder;
    int i_ret = VLC_EGENERIC;

    /* init */
    msg = vlc_dbus_new_method( p_keystore, "open" );
    if ( !msg )
    {
        msg_Err( p_keystore, "kwallet_open : vlc_dbus_new_method failed");
        return VLC_EGENERIC;
    }

    /* Init args */
    dbus_message_iter_init_append(msg, &args);
    if ( !dbus_message_iter_append_basic( &args, DBUS_TYPE_STRING, &p_sys->psz_wallet ) ||
         !dbus_message_iter_append_basic( &args, DBUS_TYPE_INT64, &ull_win_id ) ||
         !dbus_message_iter_append_basic( &args, DBUS_TYPE_STRING, &p_sys->psz_app_id ) )
        goto end;

    /* sending message */
    repmsg = vlc_dbus_send_message( p_keystore, msg );
    if ( !repmsg )
    {
        msg_Err( p_keystore, "kwallet_open : vlc_dbus_send_message failed" );
        goto end;
    }

    /* reply arguments */
    dbus_error_init( &error );
    if ( !dbus_message_get_args( repmsg, &error, DBUS_TYPE_INT32,
                                 &ui_reply, DBUS_TYPE_INVALID ) )
    {
        msg_Err( p_keystore, "kwallet_open :"
                 " dbus_message_get_args failed\n%s", error.message );
        dbus_error_free( &error );
        goto end;
    }
    p_sys->i_handle = ui_reply;

    /* opening the vlc password folder == VLC_KEYSTORE_NAME */
    if ( kwallet_has_folder( p_keystore, psz_folder, &b_has_folder ) )
        goto end;
    if ( !b_has_folder )
    {
        if ( kwallet_create_folder( p_keystore, psz_folder ) )
        {
            msg_Err( p_keystore, "kwallet_open : could not create folder %s",
                     psz_folder );
            goto end;
        }
    }

    i_ret = VLC_SUCCESS;

end:

    if ( msg )
        dbus_message_unref( msg );
    if ( repmsg )
        dbus_message_unref( repmsg );

    return i_ret;
}