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
typedef  struct spwd const FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  assert (struct spwd const*) ; 
 scalar_t__ errno ; 
 int errno_or_else (int /*<<< orphan*/ ) ; 
 scalar_t__ putspent (struct spwd const*,struct spwd const*) ; 

int putspent_sane(const struct spwd *sp, FILE *stream) {
        assert(sp);
        assert(stream);

        errno = 0;
        if (putspent(sp, stream) != 0)
                return errno_or_else(EIO);

        return 0;
}