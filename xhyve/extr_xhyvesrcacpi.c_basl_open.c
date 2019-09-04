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
struct basl_fio {scalar_t__ fd; int /*<<< orphan*/  f_name; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHYVE_ASL_SUFFIX ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  basl_stemplate ; 
 int /*<<< orphan*/  basl_template ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/ * fdopen (scalar_t__,char*) ; 
 scalar_t__ mkstemp (int /*<<< orphan*/ ) ; 
 scalar_t__ mkstemps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
basl_open(struct basl_fio *bf, int suffix)
{
	int err;

	err = 0;

	if (suffix) {
		strlcpy(bf->f_name, basl_stemplate, MAXPATHLEN);
		bf->fd = mkstemps(bf->f_name, strlen(BHYVE_ASL_SUFFIX));
	} else {
		strlcpy(bf->f_name, basl_template, MAXPATHLEN);
		bf->fd = mkstemp(bf->f_name);
	}

	if (bf->fd > 0) {
		bf->fp = fdopen(bf->fd, "w+");
		if (bf->fp == NULL) {
			unlink(bf->f_name);
			close(bf->fd);
		}
	} else {
		err = 1;
	}

	return (err);
}