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
struct vlc_player_title_list {int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_atomic_rc_inc (int /*<<< orphan*/ *) ; 

struct vlc_player_title_list *
vlc_player_title_list_Hold(struct vlc_player_title_list *titles)
{
    vlc_atomic_rc_inc(&titles->rc);
    return titles;
}