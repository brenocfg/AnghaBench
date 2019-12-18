#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_9__ {int fd; unsigned int i_current_file; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 unsigned int FILE_COUNT ; 
 char* GetFilePath (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  OptimizeForRead (int) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*,...) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int vlc_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool SwitchFile( stream_t *p_access, unsigned i_file )
{
    access_sys_t *p_sys = p_access->p_sys;

    /* requested file already open? */
    if( p_sys->fd != -1 && p_sys->i_current_file == i_file )
        return true;

    /* close old file */
    if( p_sys->fd != -1 )
    {
        vlc_close( p_sys->fd );
        p_sys->fd = -1;
    }

    /* switch */
    if( i_file >= FILE_COUNT )
        return false;
    p_sys->i_current_file = i_file;

    /* open new file */
    char *psz_path = GetFilePath( p_access, i_file );
    if( !psz_path )
        return false;
    p_sys->fd = vlc_open( psz_path, O_RDONLY );

    if( p_sys->fd == -1 )
    {
        msg_Err( p_access, "Failed to open %s: %s", psz_path,
                 vlc_strerror_c(errno) );
        goto error;
    }

    /* cannot handle anything except normal files */
    struct stat st;
    if( fstat( p_sys->fd, &st ) || !S_ISREG( st.st_mode ) )
    {
        msg_Err( p_access, "%s is not a regular file", psz_path );
        goto error;
    }

    OptimizeForRead( p_sys->fd );

    msg_Dbg( p_access, "opened %s", psz_path );
    free( psz_path );
    return true;

error:
    vlc_dialog_display_error (p_access, _("File reading failed"), _("VLC could not"
        " open the file \"%s\" (%s)."), psz_path, vlc_strerror(errno) );
    if( p_sys->fd != -1 )
    {
        vlc_close( p_sys->fd );
        p_sys->fd = -1;
    }
    free( psz_path );
    return false;
}