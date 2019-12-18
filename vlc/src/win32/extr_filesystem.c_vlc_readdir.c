#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int drives; int insert_dot_dot; } ;
struct TYPE_4__ {char const* entry; int /*<<< orphan*/ * wdir; TYPE_1__ u; } ;
typedef  TYPE_2__ vlc_DIR ;
struct _wdirent {int /*<<< orphan*/  d_name; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 char const* FromWide (int /*<<< orphan*/ ) ; 
 struct _wdirent* _wreaddir (int /*<<< orphan*/ *) ; 
 int asprintf (char const**,char*,char) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char const*) ; 
 char const* strdup (char*) ; 

const char *vlc_readdir (DIR *dir)
{
    vlc_DIR *p_dir = (vlc_DIR *)dir;

    free(p_dir->entry);

#if !VLC_WINSTORE_APP
    /* Drive letters mode */
    if (p_dir->wdir == NULL)
    {
        DWORD drives = p_dir->u.drives;
        if (drives == 0)
        {
            p_dir->entry = NULL;
            return NULL; /* end */
        }

        unsigned int i;
        for (i = 0; !(drives & 1); i++)
            drives >>= 1;
        p_dir->u.drives &= ~(1UL << i);
        assert (i < 26);

        if (asprintf (&p_dir->entry, "%c:\\", 'A' + i) == -1)
            p_dir->entry = NULL;
    }
    else
#endif
    if (p_dir->u.insert_dot_dot)
    {
        /* Adds "..", gruik! */
        p_dir->u.insert_dot_dot = false;
        p_dir->entry = strdup ("..");
    }
    else
    {
        struct _wdirent *ent = _wreaddir (p_dir->wdir);
        p_dir->entry = (ent != NULL) ? FromWide (ent->d_name) : NULL;
    }
    return p_dir->entry;
}