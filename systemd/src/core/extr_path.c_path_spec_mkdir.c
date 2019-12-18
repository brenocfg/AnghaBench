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
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_3__ {int /*<<< orphan*/  path; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ PathSpec ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH_EXISTS ; 
 int /*<<< orphan*/  PATH_EXISTS_GLOB ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,int /*<<< orphan*/ ) ; 
 int mkdir_p_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void path_spec_mkdir(PathSpec *s, mode_t mode) {
        int r;

        if (IN_SET(s->type, PATH_EXISTS, PATH_EXISTS_GLOB))
                return;

        r = mkdir_p_label(s->path, mode);
        if (r < 0)
                log_warning_errno(r, "mkdir(%s) failed: %m", s->path);
}