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
struct basl_fio {int /*<<< orphan*/  fp; int /*<<< orphan*/  f_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  basl_keep_temps ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
basl_close(struct basl_fio *bf)
{

	if (!basl_keep_temps)
		unlink(bf->f_name);
	fclose(bf->fp);
}