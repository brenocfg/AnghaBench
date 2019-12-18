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
struct Image {scalar_t__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct Image const*) ; 
 scalar_t__ path_startswith (scalar_t__,char*) ; 

__attribute__((used)) static inline bool IMAGE_IS_VENDOR(const struct Image *i) {
        assert(i);

        return i->path && path_startswith(i->path, "/usr");
}