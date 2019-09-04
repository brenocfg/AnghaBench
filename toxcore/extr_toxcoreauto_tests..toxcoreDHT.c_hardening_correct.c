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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int send_nodes_ok; int testing_requests; scalar_t__ routes_requests_ok; } ;
typedef  TYPE_1__ Hardening ;

/* Variables and functions */

__attribute__((used)) static uint8_t hardening_correct(const Hardening *h)
{
    return h->routes_requests_ok + (h->send_nodes_ok << 1) + (h->testing_requests << 2);
}