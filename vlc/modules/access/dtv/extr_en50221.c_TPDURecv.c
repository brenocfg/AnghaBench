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
typedef  int uint8_t ;
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {int* pb_tc_has_data; int /*<<< orphan*/  obj; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ cam_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_READ_TIMEOUT ; 
 int DATA_INDICATOR ; 
 int /*<<< orphan*/  Dump (int,int*,int) ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  MAX_TPDU_SIZE ; 
 int POLLIN ; 
 int T_SB ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,...) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int vlc_strerror_c (scalar_t__) ; 
 int* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int TPDURecv( cam_t *p_cam, uint8_t i_slot, uint8_t *pi_tag,
                     uint8_t *p_data, int *pi_size )
{
    uint8_t i_tcid = i_slot + 1;
    int i_size;
    struct pollfd pfd[1];

    pfd[0].fd = p_cam->fd;
    pfd[0].events = POLLIN;

    while( poll(pfd, 1, CAM_READ_TIMEOUT ) == -1 )
        if( errno != EINTR )
        {
            msg_Err( p_cam->obj, "poll error: %s", vlc_strerror_c(errno) );
            return VLC_EGENERIC;
        }

    if ( !(pfd[0].revents & POLLIN) )
    {
        msg_Err( p_cam->obj, "CAM device poll time-out" );
        return VLC_EGENERIC;
    }

    if ( pi_size == NULL )
    {
        p_data = xmalloc( MAX_TPDU_SIZE );
    }

    for ( ; ; )
    {
        i_size = read( p_cam->fd, p_data, MAX_TPDU_SIZE );

        if ( i_size >= 0 || errno != EINTR )
            break;
    }

    if ( i_size < 5 )
    {
        msg_Err( p_cam->obj, "cannot read from CAM device (%d): %s", i_size,
                 vlc_strerror_c(errno) );
        if( pi_size == NULL )
            free( p_data );
        return VLC_EGENERIC;
    }

    if ( p_data[1] != i_tcid )
    {
        msg_Err( p_cam->obj, "invalid read from CAM device (%d instead of %d)",
                 p_data[1], i_tcid );
        if( pi_size == NULL )
            free( p_data );
        return VLC_EGENERIC;
    }

    *pi_tag = p_data[2];
    p_cam->pb_tc_has_data[i_slot] = (i_size >= 4
                                      && p_data[i_size - 4] == T_SB
                                      && p_data[i_size - 3] == 2
                                      && (p_data[i_size - 1] & DATA_INDICATOR))
                                        ?  true : false;

    Dump( false, p_data, i_size );

    if ( pi_size == NULL )
        free( p_data );
    else
        *pi_size = i_size;

    return VLC_SUCCESS;
}