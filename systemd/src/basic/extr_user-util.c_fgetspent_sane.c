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
struct spwd {int dummy; } ;
typedef  struct spwd* FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (struct spwd**) ; 
 scalar_t__ errno ; 
 int errno_or_else (int /*<<< orphan*/ ) ; 
 struct spwd* fgetspent (struct spwd**) ; 

int fgetspent_sane(FILE *stream, struct spwd **sp) {
        struct spwd *s;

        assert(sp);
        assert(stream);

        errno = 0;
        s = fgetspent(stream);
        if (!s && errno != ENOENT)
                return errno_or_else(EIO);

        *sp = s;
        return !!s;
}