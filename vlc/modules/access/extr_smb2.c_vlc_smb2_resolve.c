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
typedef  int /*<<< orphan*/  uint32_t ;
struct in_addr {int dummy; } ;
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  netbios_ns ;
typedef  int /*<<< orphan*/  ip ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  NETBIOS_FILESERVER ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,struct in_addr*) ; 
 int /*<<< orphan*/  netbios_ns_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * netbios_ns_new () ; 
 scalar_t__ netbios_ns_resolve (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 
 scalar_t__ vlc_getaddrinfo_i11e (char const*,unsigned int,int /*<<< orphan*/ *,struct addrinfo**) ; 

__attribute__((used)) static char *
vlc_smb2_resolve(stream_t *access, const char *host, unsigned port)
{
    (void) access;
    if (!host)
        return NULL;

#ifdef HAVE_DSM
    /* Test if the host is an IP */
    struct in_addr addr;
    if (inet_pton(AF_INET, host, &addr) == 1)
        return NULL;

    /* Test if the host can be resolved */
    struct addrinfo *info = NULL;
    if (vlc_getaddrinfo_i11e(host, port, NULL, &info) == 0)
    {
        freeaddrinfo(info);
        /* Let smb2 resolve it */
        return NULL;
    }

    /* Test if the host is a netbios name */
    char *out_host = NULL;
    netbios_ns *ns = netbios_ns_new();
    if (!ns)
        return NULL;
    uint32_t ip4_addr;
    if (netbios_ns_resolve(ns, host, NETBIOS_FILESERVER, &ip4_addr) == 0)
    {
        char ip[] = "xxx.xxx.xxx.xxx";
        if (inet_ntop(AF_INET, &ip4_addr, ip, sizeof(ip)))
            out_host = strdup(ip);
    }
    netbios_ns_destroy(ns);
    return out_host;
#else
    (void) port;
    return NULL;
#endif
}