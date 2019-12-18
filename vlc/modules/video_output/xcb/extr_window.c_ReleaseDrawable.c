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
typedef  scalar_t__ xcb_window_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/ * VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  serializer ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,char*) ; 
 scalar_t__* var_GetAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ReleaseDrawable (vlc_object_t *obj, xcb_window_t window)
{
    vlc_object_t *vlc = VLC_OBJECT(vlc_object_instance(obj));
    xcb_window_t *used;
    size_t n = 0;

    vlc_mutex_lock (&serializer);
    used = var_GetAddress(vlc, "xid-in-use");
    assert (used);
    while (used[n] != window)
    {
        assert (used[n]);
        n++;
    }
    do
        used[n] = used[n + 1];
    while (used[++n]);

    if (!used[0])
        var_SetAddress(vlc, "xid-in-use", NULL);
    else
        used = NULL;

    vlc_mutex_unlock (&serializer);

    free( used );

    /* Variables are reference-counted... */
    var_Destroy(vlc, "xid-in-use");
}