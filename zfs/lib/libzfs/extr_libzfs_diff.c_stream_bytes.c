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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
stream_bytes(FILE *fp, const char *string)
{
	char c;

	while ((c = *string++) != '\0') {
		if (c > ' ' && c != '\\' && c < '\177') {
			(void) fprintf(fp, "%c", c);
		} else {
			(void) fprintf(fp, "\\%04o", (uint8_t)c);
		}
	}
}