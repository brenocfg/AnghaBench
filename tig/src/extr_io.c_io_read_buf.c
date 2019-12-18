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
struct buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ io_done (struct io*) ; 
 scalar_t__ io_get (struct io*,struct buffer*,char,int) ; 
 int /*<<< orphan*/  string_ncopy_do (char*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ string_trim (scalar_t__) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

bool
io_read_buf(struct io *io, char buf[], size_t bufsize, bool allow_empty)
{
	struct buffer result = {0};

	if (io_get(io, &result, '\n', true)) {
		result.data = string_trim(result.data);
		string_ncopy_do(buf, bufsize, result.data, strlen(result.data));
	}

	return io_done(io) && (result.data || allow_empty);
}