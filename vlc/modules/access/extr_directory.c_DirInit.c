#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_readdir; TYPE_2__* p_sys; int /*<<< orphan*/  psz_filepath; int /*<<< orphan*/  psz_location; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {int /*<<< orphan*/ * dir; int /*<<< orphan*/ * base_uri; } ;
typedef  TYPE_2__ access_sys_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  DirRead ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 int asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vlc_path2uri (int /*<<< orphan*/ ,char*) ; 

int DirInit (stream_t *access, DIR *dir)
{
    access_sys_t *sys = vlc_obj_malloc(VLC_OBJECT(access), sizeof (*sys));
    if (unlikely(sys == NULL))
        goto error;

    if (!strcmp(access->psz_name, "fd"))
    {
        if (unlikely(asprintf(&sys->base_uri, "fd://%s",
                              access->psz_location) == -1))
            sys->base_uri = NULL;
    }
    else
        sys->base_uri = vlc_path2uri(access->psz_filepath, "file");
    if (unlikely(sys->base_uri == NULL))
        goto error;

    sys->dir = dir;

    access->p_sys = sys;
    access->pf_readdir = DirRead;
    access->pf_control = access_vaDirectoryControlHelper;
    return VLC_SUCCESS;

error:
    closedir(dir);
    return VLC_ENOMEM;
}