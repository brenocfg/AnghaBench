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
struct TYPE_3__ {char* member_0; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  STRV_MAKE (int /*<<< orphan*/ *) ; 
#define  VERB_ANY 129 
#define  noop_dispatcher 128 
 int /*<<< orphan*/  test_dispatch_one (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_verbs_no_default(void) {
        static const Verb verbs[] = {
                { "help", VERB_ANY, VERB_ANY, 0, noop_dispatcher },
                {},
        };

        test_dispatch_one(STRV_MAKE(NULL), verbs, -EINVAL);
}