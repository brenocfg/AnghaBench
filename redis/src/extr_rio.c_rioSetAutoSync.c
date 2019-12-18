#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  autosync; } ;
struct TYPE_7__ {TYPE_1__ file; } ;
struct TYPE_8__ {scalar_t__ write; TYPE_2__ io; } ;
typedef  TYPE_3__ rio ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_9__ {scalar_t__ write; } ;

/* Variables and functions */
 TYPE_5__ rioFileIO ; 

void rioSetAutoSync(rio *r, off_t bytes) {
    if(r->write != rioFileIO.write) return;
    r->io.file.autosync = bytes;
}