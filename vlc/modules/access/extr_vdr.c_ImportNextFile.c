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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  file_sizes; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_APPEND (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FILE_COUNT ; 
 char* GetFilePath (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*,...) ; 
 scalar_t__ vlc_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ImportNextFile( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;

    char *psz_path = GetFilePath( p_access, FILE_COUNT );
    if( !psz_path )
        return false;

    struct stat st;
    if( vlc_stat( psz_path, &st ) )
    {
        msg_Dbg( p_access, "could not stat %s: %s", psz_path,
                 vlc_strerror_c(errno) );
        free( psz_path );
        return false;
    }
    if( !S_ISREG( st.st_mode ) )
    {
        msg_Dbg( p_access, "%s is not a regular file", psz_path );
        free( psz_path );
        return false;
    }
    msg_Dbg( p_access, "%s exists", psz_path );
    free( psz_path );

    ARRAY_APPEND( p_sys->file_sizes, st.st_size );
    p_sys->size += st.st_size;

    return true;
}