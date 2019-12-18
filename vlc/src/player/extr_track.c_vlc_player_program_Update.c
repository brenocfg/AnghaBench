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
struct vlc_player_program {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * vlc_player_program_DupTitle (int,char const*) ; 

int
vlc_player_program_Update(struct vlc_player_program *prgm, int id,
                          const char *name)
{
    free((char *)prgm->name);
    prgm->name = vlc_player_program_DupTitle(id, name);
    return prgm->name != NULL ? VLC_SUCCESS : VLC_ENOMEM;
}