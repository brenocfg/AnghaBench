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
typedef  char uint16_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  iso_dsc ;

/* Variables and functions */
 int DVD_VIDEO_LB_LEN ; 
 scalar_t__ ENOENT ; 
 int GetWLE (char*) ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ errno ; 
 int fstat (int,struct stat*) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_open (char const*,int) ; 

__attribute__((used)) static int ProbeDVD( const char *psz_name )
{
    if( !*psz_name )
        /* Triggers libdvdcss autodetection */
        return VLC_SUCCESS;

    int fd = vlc_open( psz_name, O_RDONLY | O_NONBLOCK );
    if( fd == -1 )
#ifdef HAVE_FDOPENDIR
        return VLC_EGENERIC;
#else
        return (errno == ENOENT) ? VLC_EGENERIC : VLC_SUCCESS;
#endif

    int ret = VLC_EGENERIC;
    struct stat stat_info;

    if( fstat( fd, &stat_info ) == -1 )
         goto bailout;
    if( !S_ISREG( stat_info.st_mode ) )
    {
        if( S_ISDIR( stat_info.st_mode ) || S_ISBLK( stat_info.st_mode ) )
            ret = VLC_SUCCESS; /* Let dvdnav_open() do the probing */
        goto bailout;
    }

    /* ISO 9660 volume descriptor */
    char iso_dsc[6];
    if( lseek( fd, 0x8000 + 1, SEEK_SET ) == -1
     || read( fd, iso_dsc, sizeof (iso_dsc) ) < (int)sizeof (iso_dsc)
     || memcmp( iso_dsc, "CD001\x01", 6 ) )
        goto bailout;

    /* Try to find the anchor (2 bytes at LBA 256) */
    uint16_t anchor;

    if( lseek( fd, 256 * DVD_VIDEO_LB_LEN, SEEK_SET ) != -1
     && read( fd, &anchor, 2 ) == 2
     && GetWLE( &anchor ) == 2 )
        ret = VLC_SUCCESS; /* Found a potential anchor */
bailout:
    vlc_close( fd );
    return ret;
}