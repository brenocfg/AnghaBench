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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int
kstat_seq_show_raw(struct seq_file *f, unsigned char *p, int l)
{
	int i, j;

	for (i = 0; ; i++) {
		seq_printf(f, "%03x:", i);

		for (j = 0; j < 16; j++) {
			if (i * 16 + j >= l) {
				seq_printf(f, "\n");
				goto out;
			}

			seq_printf(f, " %02x", (unsigned char)p[i * 16 + j]);
		}
		seq_printf(f, "\n");
	}
out:
	return (0);
}