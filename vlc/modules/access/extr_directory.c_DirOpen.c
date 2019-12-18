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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/ * psz_filepath; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DirInit (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/ * vlc_opendir (int /*<<< orphan*/ *) ; 

int DirOpen (vlc_object_t *obj)
{
    stream_t *access = (stream_t *)obj;

    if (access->psz_filepath == NULL)
        return VLC_EGENERIC;

    DIR *dir = vlc_opendir(access->psz_filepath);
    if (dir == NULL)
        return VLC_EGENERIC;

    return DirInit(access, dir);
}