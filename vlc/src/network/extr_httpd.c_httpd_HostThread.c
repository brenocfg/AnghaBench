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
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ httpd_host_t ;

/* Variables and functions */
 scalar_t__ atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpdLoop (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

__attribute__((used)) static void* httpd_HostThread(void *data)
{
    httpd_host_t *host = data;

    while (atomic_load_explicit(&host->ref, memory_order_relaxed) > 0)
        httpdLoop(host);
    return NULL;
}