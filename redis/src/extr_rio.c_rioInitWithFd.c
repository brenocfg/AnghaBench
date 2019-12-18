#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fd; int /*<<< orphan*/  buf; scalar_t__ pos; } ;
struct TYPE_7__ {TYPE_1__ fd; } ;
struct TYPE_8__ {TYPE_2__ io; } ;
typedef  TYPE_3__ rio ;

/* Variables and functions */
 TYPE_3__ rioFdIO ; 
 int /*<<< orphan*/  sdsempty () ; 

void rioInitWithFd(rio *r, int fd) {
    *r = rioFdIO;
    r->io.fd.fd = fd;
    r->io.fd.pos = 0;
    r->io.fd.buf = sdsempty();
}