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
struct vlc_player_program {int /*<<< orphan*/  scrambled; int /*<<< orphan*/  selected; int /*<<< orphan*/  name; int /*<<< orphan*/  group_id; } ;

/* Variables and functions */
 struct vlc_player_program* vlc_player_program_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct vlc_player_program *
vlc_player_program_Dup(const struct vlc_player_program *src)
{
    struct vlc_player_program *dup =
        vlc_player_program_New(src->group_id, src->name);

    if (!dup)
        return NULL;
    dup->selected = src->selected;
    dup->scrambled = src->scrambled;
    return dup;
}