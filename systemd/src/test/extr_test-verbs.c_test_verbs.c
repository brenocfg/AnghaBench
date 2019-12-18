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
struct TYPE_3__ {char* member_0; int const member_1; int const member_2; int /*<<< orphan*/  const member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  STRV_MAKE (char*,...) ; 
 int /*<<< orphan*/  STRV_MAKE_EMPTY ; 
#define  VERB_ANY 130 
#define  VERB_DEFAULT 129 
#define  noop_dispatcher 128 
 int /*<<< orphan*/  test_dispatch_one (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_verbs(void) {
        static const Verb verbs[] = {
                { "help",        VERB_ANY, VERB_ANY, 0,            noop_dispatcher },
                { "list-images", VERB_ANY, 1,        0,            noop_dispatcher },
                { "list",        VERB_ANY, 2,        VERB_DEFAULT, noop_dispatcher },
                { "status",      2,        VERB_ANY, 0,            noop_dispatcher },
                { "show",        VERB_ANY, VERB_ANY, 0,            noop_dispatcher },
                { "terminate",   2,        VERB_ANY, 0,            noop_dispatcher },
                { "login",       2,        2,        0,            noop_dispatcher },
                { "copy-to",     3,        4,        0,            noop_dispatcher },
                {}
        };

        /* not found */
        test_dispatch_one(STRV_MAKE("command-not-found"), verbs, -EINVAL);

        /* found */
        test_dispatch_one(STRV_MAKE("show"), verbs, 0);

        /* found, too few args */
        test_dispatch_one(STRV_MAKE("copy-to", "foo"), verbs, -EINVAL);

        /* found, meets min args */
        test_dispatch_one(STRV_MAKE("status", "foo", "bar"), verbs, 0);

        /* found, too many args */
        test_dispatch_one(STRV_MAKE("copy-to", "foo", "bar", "baz", "quux", "qaax"), verbs, -EINVAL);

        /* no verb, but a default is set */
        test_dispatch_one(STRV_MAKE_EMPTY, verbs, 0);
}