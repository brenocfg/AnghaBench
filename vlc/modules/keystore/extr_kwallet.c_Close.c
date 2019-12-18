#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_keystore ;
struct TYPE_4__ {struct TYPE_4__* psz_wallet; struct TYPE_4__* psz_app_id; int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_connection_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void
Close( vlc_object_t* p_this )
{
    vlc_keystore *p_keystore = ( vlc_keystore* )p_this;

    dbus_connection_close( p_keystore->p_sys->connection );
    dbus_connection_unref( p_keystore->p_sys->connection );
    free( p_keystore->p_sys->psz_app_id );
    free( p_keystore->p_sys->psz_wallet );
    free( p_keystore->p_sys );
}