#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_6__ {scalar_t__ sa_family; } ;
struct ifreq {char* ifc_buf; int ifc_len; TYPE_1__ ifr_broadaddr; } ;
struct ifconf {char* ifc_buf; int ifc_len; TYPE_1__ ifr_broadaddr; } ;
typedef  int /*<<< orphan*/  sock_t ;
typedef  int /*<<< orphan*/  i_faces ;
struct TYPE_7__ {scalar_t__ uint32; int /*<<< orphan*/  in_addr; } ;
struct TYPE_8__ {TYPE_2__ ip4; scalar_t__ family; } ;
struct TYPE_9__ {int /*<<< orphan*/  port; TYPE_3__ ip; } ;
typedef  TYPE_4__ IP_Port ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int MAX_INTERFACES ; 
 int /*<<< orphan*/  SIOCGIFBRDADDR ; 
 int /*<<< orphan*/  SIOCGIFCONF ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int broadcast_count ; 
 TYPE_4__* broadcast_ip_port ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fetch_broadcast_info(uint16_t port)
{
    /* Not sure how many platforms this will run on,
     * so it's wrapped in __linux for now.
     * Definitely won't work like this on Windows...
     */
    broadcast_count = 0;
    sock_t sock = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return;

    /* Configure ifconf for the ioctl call. */
    struct ifreq i_faces[MAX_INTERFACES];
    memset(i_faces, 0, sizeof(struct ifreq) * MAX_INTERFACES);

    struct ifconf ifconf;
    ifconf.ifc_buf = (char *)i_faces;
    ifconf.ifc_len = sizeof(i_faces);

    if (ioctl(sock, SIOCGIFCONF, &ifconf) < 0) {
        close(sock);
        return;
    }

    /* ifconf.ifc_len is set by the ioctl() to the actual length used;
     * on usage of the complete array the call should be repeated with
     * a larger array, not done (640kB and 16 interfaces shall be
     * enough, for everybody!)
     */
    int i, count = ifconf.ifc_len / sizeof(struct ifreq);

    for (i = 0; i < count; i++) {
        /* there are interfaces with are incapable of broadcast */
        if (ioctl(sock, SIOCGIFBRDADDR, &i_faces[i]) < 0)
            continue;

        /* moot check: only AF_INET returned (backwards compat.) */
        if (i_faces[i].ifr_broadaddr.sa_family != AF_INET)
            continue;

        struct sockaddr_in *sock4 = (struct sockaddr_in *)&i_faces[i].ifr_broadaddr;

        if (broadcast_count >= MAX_INTERFACES) {
            close(sock);
            return;
        }

        IP_Port *ip_port = &broadcast_ip_port[broadcast_count];
        ip_port->ip.family = AF_INET;
        ip_port->ip.ip4.in_addr = sock4->sin_addr;

        if (ip_port->ip.ip4.uint32 == 0) {
            continue;
        }

        ip_port->port = port;
        broadcast_count++;
    }

    close(sock);
}