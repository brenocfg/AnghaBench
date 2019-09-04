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
 int /*<<< orphan*/  EPM_PROTOCOL_HTTP ; 
 size_t rpcrt4_ip_tcp_get_top_of_tower (unsigned char*,char const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static size_t rpcrt4_ncacn_http_get_top_of_tower(unsigned char *tower_data,
                                                 const char *networkaddr,
                                                 const char *endpoint)
{
    return rpcrt4_ip_tcp_get_top_of_tower(tower_data, networkaddr,
                                          EPM_PROTOCOL_HTTP, endpoint);
}