#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {int i_vcdimage_handle; char* psz_dev; int i_device_handle; int /*<<< orphan*/  toc; } ;
typedef  TYPE_1__ vcddev_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int OpenVCDImage (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int os2_vcd_open (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 scalar_t__ strdup (char const*) ; 
 int strlen (char const*) ; 
 int vlc_open (char const*,int) ; 
 scalar_t__ vlc_stat (char const*,struct stat*) ; 
 int win32_vcd_open (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 

vcddev_t *ioctl_Open( vlc_object_t *p_this, const char *psz_dev )
{
    int i_ret;
    int b_is_file;
    vcddev_t *p_vcddev;
#if !defined( _WIN32 ) && !defined( __OS2__ )
    struct stat fileinfo;
#endif

    if( !psz_dev ) return NULL;

    /*
     *  Initialize structure with default values
     */
    p_vcddev = malloc( sizeof(*p_vcddev) );
    if( p_vcddev == NULL )
        return NULL;
    p_vcddev->i_vcdimage_handle = -1;
    p_vcddev->psz_dev = NULL;
    memset( &p_vcddev->toc, 0, sizeof(p_vcddev->toc) );
    b_is_file = 1;

    /*
     *  Check if we are dealing with a device or a file (vcd image)
     */
#if defined( _WIN32 ) || defined( __OS2__ )
    if( (strlen( psz_dev ) == 2 && psz_dev[1] == ':') )
    {
        b_is_file = 0;
    }

#else
    if( vlc_stat( psz_dev, &fileinfo ) < 0 )
    {
        free( p_vcddev );
        return NULL;
    }

    /* Check if this is a block/char device */
    if( S_ISBLK( fileinfo.st_mode ) || S_ISCHR( fileinfo.st_mode ) )
        b_is_file = 0;
#endif

    if( b_is_file )
    {
        i_ret = OpenVCDImage( p_this, psz_dev, p_vcddev );
    }
    else
    {
        /*
         *  open the vcd device
         */

#ifdef _WIN32
        i_ret = win32_vcd_open( p_this, psz_dev, p_vcddev );
#elif defined( __OS2__ )
        i_ret = os2_vcd_open( p_this, psz_dev, p_vcddev );
#else
        p_vcddev->i_device_handle = -1;
        p_vcddev->i_device_handle = vlc_open( psz_dev, O_RDONLY | O_NONBLOCK );
        i_ret = (p_vcddev->i_device_handle == -1) ? -1 : 0;
#endif
    }

    if( i_ret == 0 )
    {
        p_vcddev->psz_dev = (char *)strdup( psz_dev );
    }
    else
    {
        free( p_vcddev );
        p_vcddev = NULL;
    }

    return p_vcddev;
}