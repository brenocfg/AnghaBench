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
 int /*<<< orphan*/  B_FALSE ; 
 int taskq_seq_show_impl (struct seq_file*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
taskq_seq_show(struct seq_file *f, void *p)
{
	return (taskq_seq_show_impl(f, p, B_FALSE));
}