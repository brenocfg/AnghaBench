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
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

void libvlc_media_player_set_android_context( libvlc_media_player_t *p_mi,
                                              void *p_awindow_handler )
{
    assert (p_mi != NULL);
#ifdef __ANDROID__
    var_SetAddress (p_mi, "drawable-androidwindow", p_awindow_handler);
#else
    (void) p_awindow_handler;
    libvlc_printerr ("can't set android context: ANDROID build required");
    assert(false);
    var_SetString (p_mi, "vout", "none");
    var_SetString (p_mi, "window", "none");
#endif
}