#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct ifreq {char* ifr_name; int /*<<< orphan*/  ifr_addr; } ;
struct TYPE_3__ {size_t len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  SIOCGIFADDR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_tfs_get_local_ip(ngx_str_t device, struct sockaddr_in *addr)
{
    int           sock;
    struct ifreq  ifr;

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return NGX_ERROR;
    }

    ngx_memcpy(ifr.ifr_name, device.data, device.len);
    ifr.ifr_name[device.len] ='\0';

    if(ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
        close(sock);
        return NGX_ERROR;
    }

    *addr = *((struct sockaddr_in *) &ifr.ifr_addr);

    close(sock);
    return NGX_OK;
}