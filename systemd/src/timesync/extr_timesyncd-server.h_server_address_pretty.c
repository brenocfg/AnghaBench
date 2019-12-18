#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct TYPE_5__ {int /*<<< orphan*/  socklen; TYPE_1__ sockaddr; } ;
typedef  TYPE_2__ ServerAddress ;

/* Variables and functions */
 int sockaddr_pretty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char**) ; 

__attribute__((used)) static inline int server_address_pretty(ServerAddress *a, char **pretty) {
        return sockaddr_pretty(&a->sockaddr.sa, a->socklen, true, true, pretty);
}