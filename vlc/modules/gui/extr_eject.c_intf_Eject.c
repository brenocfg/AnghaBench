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
typedef  char const vlc_object_t ;
typedef  char WCHAR ;
struct TYPE_3__ {char* lpstrElementName; int /*<<< orphan*/  wDeviceID; scalar_t__ lpstrDeviceType; } ;
typedef  TYPE_1__ MCI_OPEN_PARMS ;
typedef  scalar_t__ LPCTSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CDROMEJECT ; 
 scalar_t__ EjectSCSI (int) ; 
 int /*<<< orphan*/  MCI_CLOSE ; 
 scalar_t__ MCI_DEVTYPE_CD_AUDIO ; 
 int /*<<< orphan*/  MCI_OPEN ; 
 int MCI_OPEN_ELEMENT ; 
 int MCI_OPEN_SHAREABLE ; 
 int MCI_OPEN_TYPE ; 
 int MCI_OPEN_TYPE_ID ; 
 int /*<<< orphan*/  MCI_SET ; 
 int MCI_SET_DOOR_OPEN ; 
 int MCI_WAIT ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mciSendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (char const*,char*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (char const*,char*) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_open (char const*,int) ; 
 int /*<<< orphan*/  wcscpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intf_Eject( vlc_object_t *p_this, const char *psz_device )
{
    VLC_UNUSED(p_this);

#if defined(_WIN32)
    MCI_OPEN_PARMS op;
    DWORD i_flags;
    WCHAR psz_drive[4];

    memset( &op, 0, sizeof(MCI_OPEN_PARMS) );
    op.lpstrDeviceType = (LPCTSTR)MCI_DEVTYPE_CD_AUDIO;

    wcscpy( psz_drive, TEXT("X:") );
    psz_drive[0] = psz_device[0];
    op.lpstrElementName = psz_drive;

    /* Set the flags for the device type */
    i_flags = MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID |
              MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE;

    if( mciSendCommand( 0, MCI_OPEN, i_flags, (uintptr_t)&op ) )
        return VLC_EGENERIC;

    /* Eject disc */
    mciSendCommand( op.wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN, 0 );
    /* Release access to the device */
    mciSendCommand( op.wDeviceID, MCI_CLOSE, MCI_WAIT, 0 );

    return VLC_SUCCESS;

#elif defined (__linux__) || defined (HAVE_DVD_H)
    /* This code could be extended to support CD/DVD-ROM chargers */
    int fd = vlc_open( psz_device, O_RDONLY | O_NONBLOCK );
    if( fd == -1 )
    {
        msg_Err( p_this, "could not open device %s", psz_device );
        return VLC_EGENERIC;
    }

# if defined(__linux__)
    /* Try a simple ATAPI eject */
    if( ioctl( fd, CDROMEJECT, 0 ) < 0
     && EjectSCSI( fd ) )
# else
    if( ioctl( fd, CDROMEJECT, 0 ) < 0 )
# endif
    {
        msg_Err( p_this, "could not eject %s", psz_device );
        vlc_close( fd );
        return VLC_EGENERIC;
    }
    vlc_close( fd );
    return VLC_SUCCESS;

#else
    VLC_UNUSED( psz_device );
    msg_Warn( p_this, "CD-Rom ejection unsupported on this platform" );
    return VLC_EGENERIC;
#endif
}