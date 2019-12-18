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
struct passwd {int dummy; } ;
typedef  struct passwd* FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (struct passwd**) ; 
 scalar_t__ errno ; 
 int errno_or_else (int /*<<< orphan*/ ) ; 
 struct passwd* fgetpwent (struct passwd**) ; 

int fgetpwent_sane(FILE *stream, struct passwd **pw) {
        struct passwd *p;

        assert(pw);
        assert(stream);

        errno = 0;
        p = fgetpwent(stream);
        if (!p && errno != ENOENT)
                return errno_or_else(EIO);

        *pw = p;
        return !!p;
}