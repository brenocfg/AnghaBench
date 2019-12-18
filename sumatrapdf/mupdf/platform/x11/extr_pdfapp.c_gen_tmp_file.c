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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int gen_tmp_file(char *buf, int len)
{
	int i;
	char *name = strrchr(buf, '/');

	if (name == NULL)
		name = strrchr(buf, '\\');

	if (name != NULL)
		name++;
	else
		name = buf;

	for (i = 0; i < 10000; i++)
	{
		FILE *f;
		sprintf(name, "tmp%04d", i);
		f = fopen(buf, "r");
		if (f == NULL)
			return 1;
		fclose(f);
	}

	return 0;
}