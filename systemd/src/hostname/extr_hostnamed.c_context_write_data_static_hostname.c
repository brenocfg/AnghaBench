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
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int ENOENT ; 
 size_t PROP_STATIC_HOSTNAME ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int errno ; 
 scalar_t__ isempty (int /*<<< orphan*/ ) ; 
 scalar_t__ unlink (char*) ; 
 int write_string_file_atomic_label (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int context_write_data_static_hostname(Context *c) {

        assert(c);

        if (isempty(c->data[PROP_STATIC_HOSTNAME])) {

                if (unlink("/etc/hostname") < 0)
                        return errno == ENOENT ? 0 : -errno;

                return 0;
        }
        return write_string_file_atomic_label("/etc/hostname", c->data[PROP_STATIC_HOSTNAME]);
}