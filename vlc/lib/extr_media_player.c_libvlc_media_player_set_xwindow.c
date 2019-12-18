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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

void libvlc_media_player_set_xwindow( libvlc_media_player_t *p_mi,
                                      uint32_t drawable )
{
    assert (p_mi != NULL);

    var_SetString (p_mi, "dec-dev", "");
    var_SetString (p_mi, "vout", "");
    var_SetString (p_mi, "window", drawable ? "embed-xid,any" : "");
    var_SetInteger (p_mi, "drawable-xid", drawable);
}