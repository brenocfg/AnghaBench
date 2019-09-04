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
struct io {int dummy; } ;
typedef  int /*<<< orphan*/  io_read_fn ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int io_load_file (struct io*,char const*,size_t*,int /*<<< orphan*/ ,void*) ; 

enum status_code
io_load_span(struct io *io, const char *separators, size_t *lineno,
	     io_read_fn read_property, void *data)
{
	return io_load_file(io, separators, lineno, read_property, data);
}