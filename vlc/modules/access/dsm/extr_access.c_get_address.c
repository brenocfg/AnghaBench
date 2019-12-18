#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_addr; } ;
struct TYPE_10__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_9__ {char const* psz_host; } ;
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {char* netbios_name; TYPE_2__ url; TYPE_6__ addr; int /*<<< orphan*/  p_ns; } ;
typedef  TYPE_4__ access_sys_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  NETBIOS_FILESERVER ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int /*<<< orphan*/  inet_pton (scalar_t__,char const*,TYPE_6__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*,char const*) ; 
 char* netbios_ns_inverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netbios_ns_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static int get_address( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;

    if( p_sys->url.psz_host != NULL &&
        !inet_pton( AF_INET, p_sys->url.psz_host, &p_sys->addr ) )
    {
        /* This is not an ip address, let's try netbios/dns resolve */
        struct addrinfo *p_info = NULL;

        /* Is this a netbios name on this LAN ? */
        if( netbios_ns_resolve( p_sys->p_ns, p_sys->url.psz_host,
                                NETBIOS_FILESERVER,
                                &p_sys->addr.s_addr) == 0 )
        {
            strlcpy( p_sys->netbios_name, p_sys->url.psz_host, 16);
            return VLC_SUCCESS;
        }
        /* or is it an existing dns name ? */
        else if( getaddrinfo( p_sys->url.psz_host, NULL, NULL, &p_info ) == 0 )
        {
            if( p_info->ai_family == AF_INET )
            {
                struct sockaddr_in *in = (struct sockaddr_in *)p_info->ai_addr;
                p_sys->addr.s_addr = in->sin_addr.s_addr;
            }
            if( p_info->ai_family != AF_INET )
            {
                freeaddrinfo( p_info );
                return VLC_EGENERIC;
            }
            freeaddrinfo( p_info );
        }
        else
            return VLC_EGENERIC;
    }

    /* We have an IP address, let's find the NETBIOS name */
    const char *psz_nbt = netbios_ns_inverse( p_sys->p_ns, p_sys->addr.s_addr );
    if( psz_nbt != NULL )
        strlcpy( p_sys->netbios_name, psz_nbt, 16 );
    else
    {
        msg_Warn( p_access, "Unable to get netbios name of %s",
            p_sys->url.psz_host );
        p_sys->netbios_name[0] = '\0';
    }

    return VLC_SUCCESS;
}