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
struct TYPE_4__ {char* state_file; scalar_t__ unit; } ;
typedef  TYPE_1__ Machine ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* strjoina (char*,scalar_t__) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void machine_unlink(Machine *m) {
        assert(m);

        if (m->unit) {
                char *sl;

                sl = strjoina("/run/systemd/machines/unit:", m->unit);
                (void) unlink(sl);
        }

        if (m->state_file)
                (void) unlink(m->state_file);
}