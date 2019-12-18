#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_player_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_mi; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_player_retain (int /*<<< orphan*/ *) ; 

libvlc_media_player_t * libvlc_media_list_player_get_media_player(libvlc_media_list_player_t * p_mlp)
{
    libvlc_media_player_retain(p_mlp->p_mi);
    return p_mlp->p_mi;
}