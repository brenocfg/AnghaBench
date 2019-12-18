#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  in6_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  in_addr; } ;
struct TYPE_16__ {TYPE_3__ aaaa; TYPE_2__* key; TYPE_1__ a; } ;
typedef  TYPE_4__ sd_bus_message ;
struct TYPE_14__ {scalar_t__ type; } ;
typedef  TYPE_4__ DnsResourceRecord ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 scalar_t__ DNS_TYPE_A ; 
 scalar_t__ DNS_TYPE_AAAA ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int sd_bus_message_append (TYPE_4__*,char*,int) ; 
 int sd_bus_message_append_array (TYPE_4__*,char,int /*<<< orphan*/ *,int) ; 
 int sd_bus_message_close_container (TYPE_4__*) ; 
 int sd_bus_message_open_container (TYPE_4__*,char,char*) ; 

__attribute__((used)) static int append_address(sd_bus_message *reply, DnsResourceRecord *rr, int ifindex) {
        int r;

        assert(reply);
        assert(rr);

        r = sd_bus_message_open_container(reply, 'r', "iiay");
        if (r < 0)
                return r;

        r = sd_bus_message_append(reply, "i", ifindex);
        if (r < 0)
                return r;

        if (rr->key->type == DNS_TYPE_A) {
                r = sd_bus_message_append(reply, "i", AF_INET);
                if (r < 0)
                        return r;

                r = sd_bus_message_append_array(reply, 'y', &rr->a.in_addr, sizeof(struct in_addr));

        } else if (rr->key->type == DNS_TYPE_AAAA) {
                r = sd_bus_message_append(reply, "i", AF_INET6);
                if (r < 0)
                        return r;

                r = sd_bus_message_append_array(reply, 'y', &rr->aaaa.in6_addr, sizeof(struct in6_addr));
        } else
                return -EAFNOSUPPORT;

        if (r < 0)
                return r;

        r = sd_bus_message_close_container(reply);
        if (r < 0)
                return r;

        return 0;
}