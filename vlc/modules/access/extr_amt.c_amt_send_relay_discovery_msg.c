#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulNonce ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  chaSendBuffer ;
struct TYPE_6__ {unsigned int glob_ulNonce; int /*<<< orphan*/  relayDiscoAddr; int /*<<< orphan*/  sAMT; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int AMT_DISCO_MSG_LEN ; 
 char AMT_RELAY_DISCO ; 
 int /*<<< orphan*/  errno ; 
 unsigned int htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned int*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand () ; 
 int sendto (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amt_send_relay_discovery_msg( stream_t *p_access, char *relay_ip )
{
    char          chaSendBuffer[AMT_DISCO_MSG_LEN];
    unsigned int  ulNonce;
    int           nRet;
    access_sys_t *sys = p_access->p_sys;

    /* initialize variables */
    memset( chaSendBuffer, 0, sizeof(chaSendBuffer) );
    ulNonce = 0;
    nRet = 0;

    /*
     * create AMT discovery message format
     * +---------------------------------------------------+
     * | Msg Type(1Byte)| Reserved (3 byte)| nonce (4byte) |
     * +---------------------------------------------------+
     */

    chaSendBuffer[0] = AMT_RELAY_DISCO;
    chaSendBuffer[1] = 0;
    chaSendBuffer[2] = 0;
    chaSendBuffer[3] = 0;

    /* create nonce and copy into send buffer */
    srand( (unsigned int)time(NULL) );
    ulNonce = htonl( rand() );
    memcpy( &chaSendBuffer[4], &ulNonce, sizeof(ulNonce) );
    sys->glob_ulNonce = ulNonce;

    /* send it */
    nRet = sendto( sys->sAMT, chaSendBuffer, sizeof(chaSendBuffer), 0,\
            (struct sockaddr *)&sys->relayDiscoAddr, sizeof(struct sockaddr) );

    if( nRet < 0)
        msg_Err( p_access, "Sendto failed to %s with error %d.", relay_ip, errno);
}