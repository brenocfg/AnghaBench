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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  IPPROTO_UDPLITE ; 
 char const* ip_protocol_to_name (scalar_t__) ; 

__attribute__((used)) static const char* socket_protocol_to_string(int32_t i) {
        if (i == IPPROTO_IP)
                return "";

        if (!IN_SET(i, IPPROTO_UDPLITE, IPPROTO_SCTP))
                return NULL;

        return ip_protocol_to_name(i);
}