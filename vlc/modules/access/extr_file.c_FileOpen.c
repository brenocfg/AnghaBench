#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_7__ {char* psz_location; char* psz_filepath; int /*<<< orphan*/  psz_name; int /*<<< orphan*/ * pf_seek; TYPE_2__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/ * pf_block; int /*<<< orphan*/  pf_read; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_8__ {int fd; int b_pace_control; } ;
typedef  TYPE_2__ access_sys_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DirInit (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_NOCACHE ; 
 int /*<<< orphan*/  F_RDAHEAD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  FileControl ; 
 int /*<<< orphan*/ * FileSeek ; 
 scalar_t__ IsRemote (int,char*) ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  POSIX_FADV_NOREUSE ; 
 int /*<<< orphan*/  POSIX_FADV_WILLNEED ; 
 int /*<<< orphan*/  Read ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * fdopendir (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*,...) ; 
 int /*<<< orphan*/  posix_fadvise (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int strtol (char*,char**,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_dup (int) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 
 int vlc_open (char*,int) ; 
 int vlc_openat (int,char*,int) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 
 char* vlc_uri_decode_duplicate (char*) ; 

int FileOpen( vlc_object_t *p_this )
{
    stream_t *p_access = (stream_t*)p_this;

    /* Open file */
    int fd = -1;

    if (!strcasecmp (p_access->psz_name, "fd"))
    {
        char *end;
        int oldfd = strtol (p_access->psz_location, &end, 10);

        if (*end == '\0')
            fd = vlc_dup (oldfd);
        else if (*end == '/' && end > p_access->psz_location)
        {
            char *name = vlc_uri_decode_duplicate (end - 1);
            if (name != NULL)
            {
                name[0] = '.';
                fd = vlc_openat (oldfd, name, O_RDONLY | O_NONBLOCK);
                free (name);
            }
        }
    }
    else
    {
        if (unlikely(p_access->psz_filepath == NULL))
            return VLC_EGENERIC;
        fd = vlc_open (p_access->psz_filepath, O_RDONLY | O_NONBLOCK);
    }

    if (fd == -1)
    {
        msg_Err (p_access, "cannot open file %s (%s)",
                 p_access->psz_filepath ? p_access->psz_filepath
                                        : p_access->psz_location,
                 vlc_strerror_c(errno));
        return VLC_EGENERIC;
    }

    struct stat st;
    if (fstat (fd, &st))
    {
        msg_Err (p_access, "read error: %s", vlc_strerror_c(errno));
        goto error;
    }

#if O_NONBLOCK
    /* Force blocking mode back */
    fcntl (fd, F_SETFL, fcntl (fd, F_GETFL) & ~O_NONBLOCK);
#endif

    /* Directories can be opened and read from, but only readdir() knows
     * how to parse the data. The directory plugin will do it. */
    if (S_ISDIR (st.st_mode))
    {
#ifdef HAVE_FDOPENDIR
        DIR *p_dir = fdopendir(fd);
        if (!p_dir) {
            msg_Err (p_access, "fdopendir error: %s", vlc_strerror_c(errno));
            goto error;
        }
        return DirInit (p_access, p_dir);
#else
        msg_Dbg (p_access, "ignoring directory");
        goto error;
#endif
    }

    access_sys_t *p_sys = vlc_obj_malloc(p_this, sizeof (*p_sys));
    if (unlikely(p_sys == NULL))
        goto error;
    p_access->pf_read = Read;
    p_access->pf_block = NULL;
    p_access->pf_control = FileControl;
    p_access->p_sys = p_sys;
    p_sys->fd = fd;

    if (S_ISREG (st.st_mode) || S_ISBLK (st.st_mode))
    {
        p_access->pf_seek = FileSeek;
        p_sys->b_pace_control = true;

        /* Demuxers will need the beginning of the file for probing. */
        posix_fadvise (fd, 0, 4096, POSIX_FADV_WILLNEED);
        /* In most cases, we only read the file once. */
        posix_fadvise (fd, 0, 0, POSIX_FADV_NOREUSE);
#ifdef F_NOCACHE
        fcntl (fd, F_NOCACHE, 0);
#endif
#ifdef F_RDAHEAD
        if (IsRemote(fd, p_access->psz_filepath))
            fcntl (fd, F_RDAHEAD, 0);
        else
            fcntl (fd, F_RDAHEAD, 1);
#endif
    }
    else
    {
        p_access->pf_seek = NULL;
        p_sys->b_pace_control = strcasecmp (p_access->psz_name, "stream");
    }

    return VLC_SUCCESS;

error:
    vlc_close (fd);
    return VLC_EGENERIC;
}