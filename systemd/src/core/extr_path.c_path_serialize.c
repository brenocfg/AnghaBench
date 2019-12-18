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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_3__ {int /*<<< orphan*/  result; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  FDSet ;

/* Variables and functions */
 TYPE_1__* PATH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_result_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_state_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_item (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int path_serialize(Unit *u, FILE *f, FDSet *fds) {
        Path *p = PATH(u);

        assert(u);
        assert(f);
        assert(fds);

        (void) serialize_item(f, "state", path_state_to_string(p->state));
        (void) serialize_item(f, "result", path_result_to_string(p->result));

        return 0;
}