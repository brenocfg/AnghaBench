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
struct statfs {int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_mntfromname; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct mntent {int /*<<< orphan*/  mnt_dir; int /*<<< orphan*/  mnt_fsname; } ;
typedef  int /*<<< orphan*/  mbuf ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_NOWAIT ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (char*) ; 
 int /*<<< orphan*/  endmntent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getfsstat (struct statfs*,int,int /*<<< orphan*/ ) ; 
 struct mntent* getmntent_r (int /*<<< orphan*/ *,struct mntent*,char*,int) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 char* realpath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setmntent (char*,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void FindMountPoint(char **file)
{
    char *device = *file;
#ifdef HAVE_GETMNTENT_R
    /* bd path may be a symlink (e.g. /dev/dvd -> /dev/sr0), so make sure
     * we look up the real device */
    char *bd_device = realpath(device, NULL);
    if (bd_device == NULL)
        return;

    struct stat st;
    if (lstat (bd_device, &st) == 0 && S_ISBLK (st.st_mode)) {
        FILE *mtab = setmntent ("/proc/self/mounts", "r");
        if (mtab) {
            struct mntent *m, mbuf;
            char buf [8192];

            while ((m = getmntent_r (mtab, &mbuf, buf, sizeof(buf))) != NULL) {
                if (!strcmp (m->mnt_fsname, bd_device)) {
                    free(device);
                    *file = strdup(m->mnt_dir);
                    break;
                }
            }
            endmntent (mtab);
        }
    }
    free(bd_device);

#elif defined(__APPLE__)
    struct stat st;
    if (!stat (device, &st) && S_ISBLK (st.st_mode)) {
        int fs_count = getfsstat (NULL, 0, MNT_NOWAIT);
        if (fs_count > 0) {
            struct statfs mbuf[128];
            getfsstat (mbuf, fs_count * sizeof(mbuf[0]), MNT_NOWAIT);
            for (int i = 0; i < fs_count; ++i)
                if (!strcmp (mbuf[i].f_mntfromname, device)) {
                    free(device);
                    *file = strdup(mbuf[i].f_mntonname);
                    return;
                }
        }
    }
#else
# warning Disc device to mount point not implemented
    VLC_UNUSED( device );
#endif
}