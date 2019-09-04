#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sa_family_t ;
struct TYPE_7__ {void* uint32; } ;
struct TYPE_6__ {int* uint8; void** uint32; } ;
struct TYPE_8__ {TYPE_2__ ip4; scalar_t__ family; TYPE_1__ ip6; } ;
typedef  TYPE_3__ IP ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 void* INADDR_BROADCAST ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  ip_reset (TYPE_3__*) ; 

__attribute__((used)) static IP broadcast_ip(sa_family_t family_socket, sa_family_t family_broadcast)
{
    IP ip;
    ip_reset(&ip);

    if (family_socket == AF_INET6) {
        if (family_broadcast == AF_INET6) {
            ip.family = AF_INET6;
            /* FF02::1 is - according to RFC 4291 - multicast all-nodes link-local */
            /* FE80::*: MUST be exact, for that we would need to look over all
             * interfaces and check in which status they are */
            ip.ip6.uint8[ 0] = 0xFF;
            ip.ip6.uint8[ 1] = 0x02;
            ip.ip6.uint8[15] = 0x01;
        } else if (family_broadcast == AF_INET) {
            ip.family = AF_INET6;
            ip.ip6.uint32[0] = 0;
            ip.ip6.uint32[1] = 0;
            ip.ip6.uint32[2] = htonl(0xFFFF);
            ip.ip6.uint32[3] = INADDR_BROADCAST;
        }
    } else if (family_socket == AF_INET) {
        if (family_broadcast == AF_INET) {
            ip.family = AF_INET;
            ip.ip4.uint32 = INADDR_BROADCAST;
        }
    }

    return ip;
}