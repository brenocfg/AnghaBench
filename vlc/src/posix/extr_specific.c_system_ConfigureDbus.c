#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_int_t ;
typedef  int dbus_bool_t ;
struct TYPE_6__ {char const* const message; } ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  TYPE_1__ DBusError ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_BUS_SESSION ; 
 int /*<<< orphan*/  DBUS_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_OBJECT_PATH ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 char* MPRIS_APPEND ; 
 int /*<<< orphan*/  MPRIS_BUS_NAME ; 
 int /*<<< orphan*/  MPRIS_OBJECT_PATH ; 
 int /*<<< orphan*/  MPRIS_TRACKLIST_INTERFACE ; 
 int /*<<< orphan*/ * dbus_bus_get (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * dbus_connection_send_with_reply_and_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  dbus_error_init (TYPE_1__*) ; 
 int dbus_message_append_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbus_message_new_method_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_threads_init_default () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libvlc_InternalAddIntf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const* const) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (char const* const,char*) ; 
 scalar_t__ unlikely (int) ; 
 char* var_GetString (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 char* vlc_path2uri (char const* const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void system_ConfigureDbus(libvlc_int_t *vlc, int argc,
                                 const char *const argv[])
{
/* FIXME: could be replaced by using Unix sockets */
#ifdef HAVE_DBUS
# define MPRIS_APPEND "/org/mpris/MediaPlayer2/TrackList/Append"
# define MPRIS_BUS_NAME "org.mpris.MediaPlayer2.vlc"
# define MPRIS_OBJECT_PATH "/org/mpris/MediaPlayer2"
# define MPRIS_TRACKLIST_INTERFACE "org.mpris.MediaPlayer2.TrackList"

    dbus_threads_init_default();

    if (var_InheritBool(vlc, "dbus"))
        libvlc_InternalAddIntf(vlc, "dbus,none");

    if (!var_InheritBool(vlc, "one-instance")
     && !(var_InheritBool(vlc, "one-instance-when-started-from-file")
       && var_InheritBool(vlc, "started-from-file")))
         return;

    for (int i = 0; i < argc; i++)
        if (argv[i][0] == ':')
        {
            msg_Err(vlc, "item option %s incompatible with single instance",
                    argv[i]);
            return;
        }

    char *name = var_GetString(vlc, "dbus-mpris-name");
    if (name != NULL)
    {
        bool singleton = !strcmp(name, MPRIS_BUS_NAME);
        free(name);
        if (singleton)
        {
            msg_Dbg(vlc, "no running VLC instance - continuing normally...");
            return; /* This is the single instance */
        }
    }

    /* Initialise D-Bus interface, check for other instances */
    DBusError err;
    dbus_error_init(&err);

    /* connect to the session bus */
    DBusConnection *conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (conn == NULL)
    {
        msg_Err(vlc, "D-Bus session bus connection failure: %s",
                 err.message);
        dbus_error_free(&err);
        return;
    }

    msg_Warn(vlc, "running VLC instance - exiting...");

    const dbus_bool_t play = !var_InheritBool(vlc, "playlist-enqueue");

    for (int i = 0; i < argc; i++)
    {
        DBusMessage *req = dbus_message_new_method_call(MPRIS_BUS_NAME,
            MPRIS_OBJECT_PATH, MPRIS_TRACKLIST_INTERFACE, "AddTrack");
        if (unlikely(req == NULL))
            continue;

        /* We need to resolve relative paths in this instance */
        char *mrlbuf = NULL;
        const char *mrl;

        if (strstr(argv[i], "://"))
            mrl = argv[i];
        else
        {
            mrlbuf = vlc_path2uri(argv[i], NULL);
            if (unlikely(mrlbuf == NULL))
            {
                dbus_message_unref(req);
                continue;
            }
            mrl = mrlbuf;
        }

        /* append MRLs */
        msg_Dbg(vlc, "adding track %s to running instance", mrl);

        const char *after_track = MPRIS_APPEND;
        dbus_bool_t ok = dbus_message_append_args(req, DBUS_TYPE_STRING, &mrl,
                                           DBUS_TYPE_OBJECT_PATH, &after_track,
                                           DBUS_TYPE_BOOLEAN, &play,
                                           DBUS_TYPE_INVALID);
        free(mrlbuf);
        if (unlikely(!ok))
        {
             dbus_message_unref(req);
             continue;
        }

        /* send message and get a handle for a reply */
        DBusMessage *reply = dbus_connection_send_with_reply_and_block(conn,
                                                                req, -1, &err);
        dbus_message_unref(req);
        if (reply == NULL)
        {
            msg_Err(vlc, "D-Bus error: %s", err.message);
            dbus_error_free(&err);
            continue;
        }
        dbus_message_unref(reply);
    }

    /* we unreference the connection when we've finished with it */
    dbus_connection_unref(conn);
    exit(0);
#else
    (void) vlc; (void) argc; (void) argv;
#endif // HAVE_DBUS
}