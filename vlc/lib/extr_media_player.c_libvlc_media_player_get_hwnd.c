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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ var_GetInteger (int /*<<< orphan*/ *,char*) ; 

void *libvlc_media_player_get_hwnd( libvlc_media_player_t *p_mi )
{
    assert (p_mi != NULL);
#if defined (_WIN32) || defined (__OS2__)
    return (void *)(uintptr_t)var_GetInteger (p_mi, "drawable-hwnd");
#else
    (void) p_mi;
    return NULL;
#endif
}