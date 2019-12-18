#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct Image {scalar_t__ path; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct Image const*) ; 
 scalar_t__ path_equal (scalar_t__,char*) ; 
 scalar_t__ streq (scalar_t__,char*) ; 

__attribute__((used)) static inline bool IMAGE_IS_HOST(const struct Image *i) {
        assert(i);

        if (i->name && streq(i->name, ".host"))
                return true;

        if (i->path && path_equal(i->path, "/"))
                return true;

        return false;
}