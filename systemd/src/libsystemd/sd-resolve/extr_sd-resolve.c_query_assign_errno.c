#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ret; int _h_errno; int /*<<< orphan*/  _errno; } ;
typedef  TYPE_1__ sd_resolve_query ;

/* Variables and functions */
 int /*<<< orphan*/  abs (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void query_assign_errno(sd_resolve_query *q, int ret, int error, int h_error) {
        assert(q);

        q->ret = ret;
        q->_errno = abs(error);
        q->_h_errno = h_error;
}