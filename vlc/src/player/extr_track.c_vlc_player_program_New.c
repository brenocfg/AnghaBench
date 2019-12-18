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
struct vlc_player_program {int group_id; int selected; int scrambled; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_player_program*) ; 
 struct vlc_player_program* malloc (int) ; 
 int /*<<< orphan*/  vlc_player_program_DupTitle (int,char const*) ; 

struct vlc_player_program *
vlc_player_program_New(int id, const char *name)
{
    struct vlc_player_program *prgm = malloc(sizeof(*prgm));
    if (!prgm)
        return NULL;
    prgm->name = vlc_player_program_DupTitle(id, name);
    if (!prgm->name)
    {
        free(prgm);
        return NULL;
    }
    prgm->group_id = id;
    prgm->selected = prgm->scrambled = false;

    return prgm;
}