#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int available; int /*<<< orphan*/  pipe_fd_write; int /*<<< orphan*/  lock; void* longitude; void* latitude; } ;
typedef  TYPE_1__ location_geoclue2_state_t ;
typedef  TYPE_1__* gpointer ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_9__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  GVariant ;
typedef  TYPE_3__ GError ;
typedef  int /*<<< orphan*/  GDBusProxy ;

/* Variables and functions */
 int /*<<< orphan*/  G_DBUS_PROXY_FLAGS_NONE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * g_dbus_proxy_get_cached_property (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_dbus_proxy_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dbus_proxy_new_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  g_error_free (TYPE_3__*) ; 
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_printerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_strcmp0 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_variant_get_child (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/  const**) ; 
 void* g_variant_get_double (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_error (TYPE_1__*) ; 
 int /*<<< orphan*/  pipeutils_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
geoclue_client_signal_cb(GDBusProxy *client, gchar *sender_name,
			 gchar *signal_name, GVariant *parameters,
			 gpointer user_data)
{
	location_geoclue2_state_t *state = user_data;

	/* Only handle LocationUpdated signals */
	if (g_strcmp0(signal_name, "LocationUpdated") != 0) {
		return;
	}

	/* Obtain location path */
	const gchar *location_path;
	g_variant_get_child(parameters, 1, "&o", &location_path);

	/* Obtain location */
	GError *error = NULL;
	GDBusProxy *location = g_dbus_proxy_new_sync(
		g_dbus_proxy_get_connection(client),
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		"org.freedesktop.GeoClue2",
		location_path,
		"org.freedesktop.GeoClue2.Location",
		NULL, &error);
	if (location == NULL) {
		g_printerr(_("Unable to obtain location: %s.\n"),
			   error->message);
		g_error_free(error);
		mark_error(state);
		return;
	}

	g_mutex_lock(&state->lock);

	/* Read location properties */
	GVariant *lat_v = g_dbus_proxy_get_cached_property(
		location, "Latitude");
	state->latitude = g_variant_get_double(lat_v);

	GVariant *lon_v = g_dbus_proxy_get_cached_property(
		location, "Longitude");
	state->longitude = g_variant_get_double(lon_v);

	state->available = 1;

	g_mutex_unlock(&state->lock);

	pipeutils_signal(state->pipe_fd_write);
}