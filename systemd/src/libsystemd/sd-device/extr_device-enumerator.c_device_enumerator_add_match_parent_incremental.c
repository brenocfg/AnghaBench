#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int scan_uptodate; int /*<<< orphan*/  match_parent; } ;
typedef  TYPE_1__ sd_device_enumerator ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sd_device_get_syspath (TYPE_1__*,char const**) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put_strdup (int /*<<< orphan*/ ,char const*) ; 

int device_enumerator_add_match_parent_incremental(sd_device_enumerator *enumerator, sd_device *parent) {
        const char *path;
        int r;

        assert_return(enumerator, -EINVAL);
        assert_return(parent, -EINVAL);

        r = sd_device_get_syspath(parent, &path);
        if (r < 0)
                return r;

        r = set_ensure_allocated(&enumerator->match_parent, NULL);
        if (r < 0)
                return r;

        r = set_put_strdup(enumerator->match_parent, path);
        if (r < 0)
                return r;

        enumerator->scan_uptodate = false;

        return 0;
}