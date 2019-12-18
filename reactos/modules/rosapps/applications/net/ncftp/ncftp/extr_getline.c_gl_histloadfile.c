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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 int /*<<< orphan*/  gl_histadd (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void
gl_histloadfile(const char *const path)
{
	FILE *fp;
	char line[256];

	fp = fopen(path,
#if defined(__windows__) || defined(MSDOS)
		"rt"
#else
		"r"
#endif
	);
	if (fp != NULL) {
		memset(line, 0, sizeof(line));
		while (fgets(line, sizeof(line) - 2, fp) != NULL) {
			gl_histadd(line);
		}
		fclose(fp);
	}
}