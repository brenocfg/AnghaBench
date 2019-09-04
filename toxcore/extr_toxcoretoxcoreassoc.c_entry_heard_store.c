#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_13__ {scalar_t__ family; } ;
struct TYPE_10__ {TYPE_9__ ip; } ;
struct TYPE_12__ {scalar_t__ heard_family; int /*<<< orphan*/  heard_at; TYPE_1__ assoc_heard6; TYPE_1__ assoc_heard4; } ;
struct TYPE_11__ {int /*<<< orphan*/  timestamp; TYPE_1__ ip_port; } ;
typedef  TYPE_1__ IP_Port ;
typedef  TYPE_2__ IPPTs ;
typedef  TYPE_3__ Client_entry ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CANDIDATES_HEARD_TIMEOUT ; 
 scalar_t__ LAN_ip (TYPE_9__) ; 
 scalar_t__ ipport_equal (TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  ipport_isset (TYPE_1__*) ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int entry_heard_store(Client_entry *entry, const IPPTs *ippts)
{
    if (!entry || !ippts)
        return 0;

    if (!ipport_isset(&ippts->ip_port))
        return 0;

    IP_Port  *heard;
    const IP_Port  *ipp = &ippts->ip_port;

    if (ipp->ip.family == AF_INET)
        heard = &entry->assoc_heard4;
    else if (ipp->ip.family == AF_INET6)
        heard = &entry->assoc_heard6;
    else
        return 0;

    if (ipport_equal(ipp, heard))
        return 0;

    if (!ipport_isset(heard)) {
        *heard = *ipp;
        entry->heard_at = ippts->timestamp;
        entry->heard_family = ipp->ip.family;
        return 1;
    }

    /* don't destroy a good address with a crappy one
     * (unless we're very timed out) */
    uint8_t LAN_ipp = LAN_ip(ipp->ip) == 0;
    uint8_t LAN_entry = LAN_ip(heard->ip) == 0;

    if (LAN_ipp && !LAN_entry && !is_timeout(entry->heard_at, CANDIDATES_HEARD_TIMEOUT))
        return 0;

    *heard = *ipp;
    entry->heard_at = ippts->timestamp;
    entry->heard_family = ipp->ip.family;

    return 1;
}