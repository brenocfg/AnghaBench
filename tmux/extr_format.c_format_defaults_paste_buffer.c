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
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct paste_buffer {int dummy; } ;
struct format_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_add (struct format_tree*,char*,char*,...) ; 
 int /*<<< orphan*/  format_add_tv (struct format_tree*,char*,struct timeval*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  paste_buffer_created (struct paste_buffer*) ; 
 int /*<<< orphan*/  paste_buffer_data (struct paste_buffer*,size_t*) ; 
 char* paste_buffer_name (struct paste_buffer*) ; 
 char* paste_make_sample (struct paste_buffer*) ; 
 int /*<<< orphan*/  timerclear (struct timeval*) ; 

void
format_defaults_paste_buffer(struct format_tree *ft, struct paste_buffer *pb)
{
	struct timeval	 tv;
	size_t		 size;
	char		*s;

	timerclear(&tv);
	tv.tv_sec = paste_buffer_created(pb);
	paste_buffer_data(pb, &size);

	format_add(ft, "buffer_size", "%zu", size);
	format_add(ft, "buffer_name", "%s", paste_buffer_name(pb));
	format_add_tv(ft, "buffer_created", &tv);

	s = paste_make_sample(pb);
	format_add(ft, "buffer_sample", "%s", s);
	free(s);
}