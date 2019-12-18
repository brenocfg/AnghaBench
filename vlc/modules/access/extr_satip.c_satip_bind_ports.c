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
typedef  int uint8_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {int udp_port; scalar_t__ udp_sock; scalar_t__ rtcp_sock; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 void* net_OpenDgram (TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_rand_bytes (int*,int) ; 

__attribute__((used)) static int satip_bind_ports(stream_t *access)
{
    access_sys_t *sys = access->p_sys;
    uint8_t rnd;

    vlc_rand_bytes(&rnd, 1);
    sys->udp_port = 9000 + (rnd * 2); /* randomly chosen, even start point */
    while (sys->udp_sock < 0) {
        sys->udp_sock = net_OpenDgram(access, "0.0.0.0", sys->udp_port, NULL,
                0, IPPROTO_UDP);
        if (sys->udp_sock < 0) {
            if (sys->udp_port == 65534)
                break;

            sys->udp_port += 2;
            continue;
        }

        sys->rtcp_sock = net_OpenDgram(access, "0.0.0.0", sys->udp_port + 1, NULL,
                0, IPPROTO_UDP);
        if (sys->rtcp_sock < 0) {
            close(sys->udp_sock);
            sys->udp_port += 2;
            continue;
        }
    }

    if (sys->udp_sock < 0) {
        msg_Err(access, "Could not open two adjacent ports for RTP and RTCP data");
        return VLC_EGENERIC;
    }

    return 0;
}