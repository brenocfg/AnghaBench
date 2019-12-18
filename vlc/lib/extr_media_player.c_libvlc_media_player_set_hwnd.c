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
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,char*,uintptr_t) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

void libvlc_media_player_set_hwnd( libvlc_media_player_t *p_mi,
                                   void *drawable )
{
    assert (p_mi != NULL);
#if defined (_WIN32) || defined (__OS2__)
    var_SetString (p_mi, "dec-dev", "");
    var_SetString (p_mi, "vout", "");
    var_SetString (p_mi, "window",
                   (drawable != NULL) ? "embed-hwnd,any" : "");
    var_SetInteger (p_mi, "drawable-hwnd", (uintptr_t)drawable);
#else
    (void) drawable;
    libvlc_printerr ("can't set hwnd: WIN32 build required");
    assert(false);
    var_SetString (p_mi, "vout", "none");
    var_SetString (p_mi, "window", "none");
#endif
}