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
struct TYPE_4__ {int routes_requests_ok; int send_nodes_ok; int testing_requests; } ;
struct TYPE_5__ {TYPE_1__ hardening; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_2__ IPPTsPng ;

/* Variables and functions */
 int HARDENING_ALL_OK ; 
 int /*<<< orphan*/  unix_time () ; 

void mark_good(IPPTsPng *ipptp)
{
    ipptp->timestamp = unix_time();
    ipptp->hardening.routes_requests_ok = (HARDENING_ALL_OK >> 0) & 1;
    ipptp->hardening.send_nodes_ok = (HARDENING_ALL_OK >> 1) & 1;
    ipptp->hardening.testing_requests = (HARDENING_ALL_OK >> 2) & 1;
}