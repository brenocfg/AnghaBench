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
typedef  int /*<<< orphan*/  location_geoclue2_state_t ;
typedef  int /*<<< orphan*/ * gpointer ;
typedef  char gchar ;
struct TYPE_7__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  GVariant ;
typedef  TYPE_1__ GError ;
typedef  int /*<<< orphan*/  GDBusProxy ;
typedef  int /*<<< orphan*/  GDBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ACCESS_ERROR ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_DBUS_CALL_FLAGS_NONE ; 
 int /*<<< orphan*/  G_DBUS_PROXY_FLAGS_NONE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* g_dbus_error_get_remote_error (TYPE_1__*) ; 
 scalar_t__ g_dbus_error_is_remote_error (TYPE_1__*) ; 
 int /*<<< orphan*/ * g_dbus_proxy_call_sync (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/ * g_dbus_proxy_new_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,char*,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_printerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ g_strcmp0 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_variant_get (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/ * g_variant_new (char*,...) ; 
 int /*<<< orphan*/  g_variant_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geoclue_client_signal_cb ; 
 int /*<<< orphan*/  mark_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_denial_message () ; 

__attribute__((used)) static void
on_name_appeared(GDBusConnection *conn, const gchar *name,
		 const gchar *name_owner, gpointer user_data)
{
	location_geoclue2_state_t *state = user_data;

	/* Obtain GeoClue Manager */
	GError *error = NULL;
	GDBusProxy *geoclue_manager = g_dbus_proxy_new_sync(
		conn,
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		"org.freedesktop.GeoClue2",
		"/org/freedesktop/GeoClue2/Manager",
		"org.freedesktop.GeoClue2.Manager",
		NULL, &error);
	if (geoclue_manager == NULL) {
		g_printerr(_("Unable to obtain GeoClue Manager: %s.\n"),
			   error->message);
		g_error_free(error);
		mark_error(state);
		return;
	}

	/* Obtain GeoClue Client path */
	error = NULL;
	GVariant *client_path_v =
		g_dbus_proxy_call_sync(geoclue_manager,
				       "GetClient",
				       NULL,
				       G_DBUS_CALL_FLAGS_NONE,
				       -1, NULL, &error);
	if (client_path_v == NULL) {
		g_printerr(_("Unable to obtain GeoClue client path: %s.\n"),
			   error->message);
		g_error_free(error);
		g_object_unref(geoclue_manager);
		mark_error(state);
		return;
	}

	const gchar *client_path;
	g_variant_get(client_path_v, "(&o)", &client_path);

	/* Obtain GeoClue client */
	error = NULL;
	GDBusProxy *geoclue_client = g_dbus_proxy_new_sync(
		conn,
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		"org.freedesktop.GeoClue2",
		client_path,
		"org.freedesktop.GeoClue2.Client",
		NULL, &error);
	if (geoclue_client == NULL) {
		g_printerr(_("Unable to obtain GeoClue Client: %s.\n"),
			   error->message);
		g_error_free(error);
		g_variant_unref(client_path_v);
		g_object_unref(geoclue_manager);
		mark_error(state);
		return;
	}

	g_variant_unref(client_path_v);

	/* Set desktop id (basename of the .desktop file) */
	error = NULL;
	GVariant *ret_v = g_dbus_proxy_call_sync(
		geoclue_client,
		"org.freedesktop.DBus.Properties.Set",
		g_variant_new("(ssv)",
		"org.freedesktop.GeoClue2.Client",
		"DesktopId",
		g_variant_new("s", "redshift")),
		G_DBUS_CALL_FLAGS_NONE,
		-1, NULL, &error);
	if (ret_v == NULL) {
		/* Ignore this error for now. The property is not available
		   in early versions of GeoClue2. */
	} else {
		g_variant_unref(ret_v);
	}

	/* Set distance threshold */
	error = NULL;
	ret_v = g_dbus_proxy_call_sync(
		geoclue_client,
		"org.freedesktop.DBus.Properties.Set",
		g_variant_new("(ssv)",
		"org.freedesktop.GeoClue2.Client",
		"DistanceThreshold",
		g_variant_new("u", 50000)),
		G_DBUS_CALL_FLAGS_NONE,
		-1, NULL, &error);
	if (ret_v == NULL) {
		g_printerr(_("Unable to set distance threshold: %s.\n"),
			   error->message);
		g_error_free(error);
		g_object_unref(geoclue_client);
		g_object_unref(geoclue_manager);
		mark_error(state);
		return;
	}

	g_variant_unref(ret_v);

	/* Attach signal callback to client */
	g_signal_connect(geoclue_client, "g-signal",
			 G_CALLBACK(geoclue_client_signal_cb),
			 user_data);

	/* Start GeoClue client */
	error = NULL;
	ret_v = g_dbus_proxy_call_sync(geoclue_client,
				       "Start",
				       NULL,
				       G_DBUS_CALL_FLAGS_NONE,
				       -1, NULL, &error);
	if (ret_v == NULL) {
		g_printerr(_("Unable to start GeoClue client: %s.\n"),
			   error->message);
		if (g_dbus_error_is_remote_error(error)) {
			gchar *dbus_error = g_dbus_error_get_remote_error(
				error);
			if (g_strcmp0(dbus_error, DBUS_ACCESS_ERROR) == 0) {
				print_denial_message();
			}
			g_free(dbus_error);
		}
		g_error_free(error);
		g_object_unref(geoclue_client);
		g_object_unref(geoclue_manager);
		mark_error(state);
		return;
	}

	g_variant_unref(ret_v);
}