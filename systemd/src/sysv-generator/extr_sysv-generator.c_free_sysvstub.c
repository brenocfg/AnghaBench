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
struct TYPE_4__ {int /*<<< orphan*/  wanted_by; int /*<<< orphan*/  wants; int /*<<< orphan*/  after; int /*<<< orphan*/  before; struct TYPE_4__* pid_file; struct TYPE_4__* description; struct TYPE_4__* path; struct TYPE_4__* name; } ;
typedef  TYPE_1__ SysvStub ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_sysvstub(SysvStub *s) {
        if (!s)
                return;

        free(s->name);
        free(s->path);
        free(s->description);
        free(s->pid_file);
        strv_free(s->before);
        strv_free(s->after);
        strv_free(s->wants);
        strv_free(s->wanted_by);
        free(s);
}