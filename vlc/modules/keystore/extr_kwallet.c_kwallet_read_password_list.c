#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* i_handle; char* psz_app_id; } ;
typedef  TYPE_1__ vlc_keystore_sys ;
typedef  int /*<<< orphan*/  vlc_keystore_entry ;
struct TYPE_8__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ vlc_keystore ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_ARRAY ; 
 scalar_t__ DBUS_TYPE_DICT_ENTRY ; 
 scalar_t__ DBUS_TYPE_INT32 ; 
 scalar_t__ DBUS_TYPE_STRING ; 
 scalar_t__ DBUS_TYPE_VARIANT ; 
 int /*<<< orphan*/ * calloc (unsigned int,int) ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,scalar_t__,char**) ; 
 scalar_t__ dbus_message_iter_get_arg_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_message_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ key2values (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 char* psz_folder ; 
 size_t vlc_b64_decode_binary (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/ * vlc_dbus_new_method (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * vlc_dbus_send_message (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_keystore_entry_set_secret (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_keystore_release_entries (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static vlc_keystore_entry*
kwallet_read_password_list( vlc_keystore* p_keystore, char* psz_entry_name,
                            unsigned int* pi_count )
{
    vlc_keystore_sys* p_sys = p_keystore->p_sys;
    DBusMessage* msg = NULL;
    DBusMessage* repmsg = NULL;
    DBusMessageIter args;
    DBusMessageIter sub_iter;
    DBusMessageIter dict_iter;
    DBusMessageIter var_iter;
    vlc_keystore_entry* p_entries = NULL;
    size_t i_size;
    uint8_t* p_secret_decoded = NULL;
    char* p_reply;
    char* p_secret;
    int i = 0;

    /* init */
    *pi_count = 0;
    if ( !( msg = vlc_dbus_new_method( p_keystore, "readPasswordList" ) ) )
    {
        msg_Err( p_keystore, "kwallet_read_password_list : vlc_dbus_new_method failed" );
        goto error;
    }

    /* argument init */
    dbus_message_iter_init_append( msg, &args );
    if ( !dbus_message_iter_append_basic( &args, DBUS_TYPE_INT32, &p_sys->i_handle ) ||
         !dbus_message_iter_append_basic( &args, DBUS_TYPE_STRING, &psz_folder ) ||
         !dbus_message_iter_append_basic( &args, DBUS_TYPE_STRING, &psz_entry_name ) ||
         !dbus_message_iter_append_basic( &args, DBUS_TYPE_STRING, &p_sys->psz_app_id ) )
        goto error;

    /* sending message */
    if ( !( repmsg = vlc_dbus_send_message( p_keystore, msg ) ) )
    {
        msg_Err( p_keystore, "kwallet_read_password_list : vlc_dbus_send_message failed" );
        goto error;
    }

    /* handling reply */
    if ( !dbus_message_iter_init( repmsg, &args ) )
    {
        msg_Err( p_keystore, "kwallet_read_password_list : Message has no arguments" );
        goto error;
    }
    else if ( dbus_message_iter_get_arg_type(&args) != DBUS_TYPE_ARRAY )
    {
        msg_Err( p_keystore, "kwallet_read_password_list : Wrong reply type" );
        goto error;
    }
    else
    {
        /* calculating p_entries's size */
        dbus_message_iter_recurse( &args, &sub_iter );
        do
        {
            if ( dbus_message_iter_get_arg_type( &sub_iter ) != DBUS_TYPE_DICT_ENTRY )
                continue;
            dbus_message_iter_recurse( &sub_iter, &dict_iter );
            if ( dbus_message_iter_get_arg_type( &dict_iter ) != DBUS_TYPE_STRING )
                continue;
            dbus_message_iter_next(&dict_iter);
            if ( dbus_message_iter_get_arg_type( &dict_iter ) != DBUS_TYPE_VARIANT )
                continue;
            ++( *pi_count );
       } while ( dbus_message_iter_next( &sub_iter ) );

        if ( *pi_count == 0 )
            goto error;
        if ( !( p_entries = calloc( *pi_count, sizeof( vlc_keystore_entry ) ) ) )
            goto error;

        dbus_message_iter_init( repmsg, &args );
        /* recurse into the reply array */
        dbus_message_iter_recurse( &args, &sub_iter );
        do
        {
            if ( dbus_message_iter_get_arg_type( &sub_iter ) != DBUS_TYPE_DICT_ENTRY )
            {
                msg_Err( p_keystore, "Wrong type not DBUS_TYPE_DICT_ENTRY" );
                continue;
            }
            /* recurse into the dict-entry in the array */
            dbus_message_iter_recurse( &sub_iter, &dict_iter );
            if ( dbus_message_iter_get_arg_type( &dict_iter ) != DBUS_TYPE_STRING )
            {
                msg_Err( p_keystore, "First type of Dict-Entry is not a string" );
                continue;
            }
            dbus_message_iter_get_basic( &dict_iter, &p_reply );
            dbus_message_iter_next(&dict_iter);
            if ( dbus_message_iter_get_arg_type( &dict_iter ) != DBUS_TYPE_VARIANT )
            {
                msg_Err( p_keystore, "Second type of Dict-Entry is not a variant" );
                continue;
            }
            /* recurse into the variant in the dict-entry */
            dbus_message_iter_recurse( &dict_iter, &var_iter );
            dbus_message_iter_get_basic( &var_iter, &p_secret );

            i_size = vlc_b64_decode_binary( &p_secret_decoded, p_secret);
            if ( key2values( p_reply, &p_entries[i] ) )
                goto error;
            if ( ( vlc_keystore_entry_set_secret( &p_entries[i],
                                                  p_secret_decoded,
                                                  i_size ) ) )
                goto error;

            free(p_secret_decoded);
            i += 1;
        } while ( dbus_message_iter_next( &sub_iter ) );
    }

    dbus_message_unref( msg );
    dbus_message_unref( repmsg );

    return p_entries;

error:
    free( p_secret_decoded );
    *pi_count = 0;
    if ( p_entries )
        vlc_keystore_release_entries( p_entries, i );
    if ( msg )
        dbus_message_unref( msg );
    if ( repmsg )
        dbus_message_unref( repmsg );
    return NULL;
}