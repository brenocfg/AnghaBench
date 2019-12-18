#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  void sd_bus ;
struct TYPE_8__ {scalar_t__ sa_family; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_9__ {TYPE_3__ sa; TYPE_2__ in6; TYPE_1__ in; } ;
struct TYPE_10__ {TYPE_4__ sockaddr; } ;
typedef  TYPE_5__ ServerAddress ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  FAMILY_ADDRESS_SIZE (scalar_t__) ; 
 void* IN_SET (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (void*) ; 
 int sd_bus_message_append (void*,char*,scalar_t__,...) ; 
 int sd_bus_message_append_array (void*,char,void*,int /*<<< orphan*/ ) ; 
 int sd_bus_message_close_container (void*) ; 
 int sd_bus_message_open_container (void*,char,char*) ; 

__attribute__((used)) static int property_get_current_server_address(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        ServerAddress *a;
        int r;

        assert(bus);
        assert(reply);
        assert(userdata);

        a = *(ServerAddress **) userdata;

        if (!a)
                return sd_bus_message_append(reply, "(iay)", AF_UNSPEC, 0);

        assert(IN_SET(a->sockaddr.sa.sa_family, AF_INET, AF_INET6));

        r = sd_bus_message_open_container(reply, 'r', "iay");
        if (r < 0)
                return r;

        r = sd_bus_message_append(reply, "i", a->sockaddr.sa.sa_family);
        if (r < 0)
                return r;

        r = sd_bus_message_append_array(reply, 'y',
                                        a->sockaddr.sa.sa_family == AF_INET ? (void*) &a->sockaddr.in.sin_addr : (void*) &a->sockaddr.in6.sin6_addr,
                                        FAMILY_ADDRESS_SIZE(a->sockaddr.sa.sa_family));
        if (r < 0)
                return r;

        return sd_bus_message_close_container(reply);
}