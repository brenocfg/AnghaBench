#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  IPPROTO_UDPLITE ; 
 int parse_ip_protocol (char const*) ; 

__attribute__((used)) static int parse_socket_protocol(const char *s) {
        int r;

        r = parse_ip_protocol(s);
        if (r < 0)
                return r;
        if (!IN_SET(r, IPPROTO_UDPLITE, IPPROTO_SCTP))
                return -EPROTONOSUPPORT;

        return r;
}