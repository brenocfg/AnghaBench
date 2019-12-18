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
typedef  int /*<<< orphan*/  va_list ;
struct snprintf_buffer {char* p; size_t s; size_t n; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_format_string (int /*<<< orphan*/ *,struct snprintf_buffer*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf_emit ; 

size_t
fz_vsnprintf(char *buffer, size_t space, const char *fmt, va_list args)
{
	struct snprintf_buffer out;
	out.p = buffer;
	out.s = space > 0 ? space - 1 : 0;
	out.n = 0;

	/* Note: using a NULL context is safe here */
	fz_format_string(NULL, &out, snprintf_emit, fmt, args);
	if (space > 0)
		out.p[out.n < space ? out.n : space - 1] = '\0';

	return out.n;
}