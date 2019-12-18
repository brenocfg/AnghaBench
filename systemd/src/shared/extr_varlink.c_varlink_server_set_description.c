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
struct TYPE_4__ {int /*<<< orphan*/  description; } ;
typedef  TYPE_1__ VarlinkServer ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 

int varlink_server_set_description(VarlinkServer *s, const char *description) {
        assert_return(s, -EINVAL);

        return free_and_strdup(&s->description, description);
}