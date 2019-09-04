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
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  seamless_process_line (int /*<<< orphan*/ *,char const*,void*) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

__attribute__((used)) static BOOL
seamless_line_handler(RDPCLIENT * This, const char *line, void *data)
{
	if (!seamless_process_line(This, line, data))
	{
		warning("SeamlessRDP: Invalid request:%s\n", line);
	}
	return True;
}