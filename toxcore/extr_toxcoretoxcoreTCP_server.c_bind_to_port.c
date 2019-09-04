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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_storage {int /*<<< orphan*/  member_0; } ;
struct sockaddr_in6 {int sin6_family; void* sin6_port; } ;
struct sockaddr_in {int sin_family; void* sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sock_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 scalar_t__ bind (int /*<<< orphan*/ ,struct sockaddr*,size_t) ; 
 void* htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bind_to_port(sock_t sock, int family, uint16_t port)
{
    struct sockaddr_storage addr = {0};
    size_t addrsize;

    if (family == AF_INET) {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)&addr;

        addrsize = sizeof(struct sockaddr_in);
        addr4->sin_family = AF_INET;
        addr4->sin_port = htons(port);
    } else if (family == AF_INET6) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)&addr;

        addrsize = sizeof(struct sockaddr_in6);
        addr6->sin6_family = AF_INET6;
        addr6->sin6_port = htons(port);
    } else {
        return 0;
    }

    return (bind(sock, (struct sockaddr *)&addr, addrsize) == 0);
}