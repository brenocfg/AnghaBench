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
struct group {int dummy; } ;
typedef  struct group* FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (struct group**) ; 
 scalar_t__ errno ; 
 int errno_or_else (int /*<<< orphan*/ ) ; 
 struct group* fgetgrent (struct group**) ; 

int fgetgrent_sane(FILE *stream, struct group **gr) {
        struct group *g;

        assert(gr);
        assert(stream);

        errno = 0;
        g = fgetgrent(stream);
        if (!g && errno != ENOENT)
                return errno_or_else(EIO);

        *gr = g;
        return !!g;
}