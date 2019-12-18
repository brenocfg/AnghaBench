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
struct chmFile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHM_ENUMERATE_ALL ; 
 int /*<<< orphan*/  _print_ui ; 
 int /*<<< orphan*/  chm_close (struct chmFile*) ; 
 int /*<<< orphan*/  chm_enumerate_dir (struct chmFile*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct chmFile* chm_open (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(int c, char **v)
{
    struct chmFile *h;
    int i;

    if (c < 2)
    {
        fprintf(stderr, "%s <chmfile> [dir] [dir] ...\n", v[0]);
        exit(1);
    }

    h = chm_open(v[1]);
    if (h == NULL)
    {
        fprintf(stderr, "failed to open %s\n", v[1]);
        exit(1);
    }

    if (c < 3)
    {
        printf("/:\n");
        printf(" spc    start   length   type\t\t\tname\n");
        printf(" ===    =====   ======   ====\t\t\t====\n");
		
        if (! chm_enumerate_dir(h,
                                "/",
                                CHM_ENUMERATE_ALL,
                                _print_ui,
                                NULL))
            printf("   *** ERROR ***\n");
    }
    else
    {
        for (i=2; i<c; i++)
        {
            printf("%s:\n", v[i]);
            printf(" spc    start   length   name\n");
            printf(" ===    =====   ======   ====\n");

            if (! chm_enumerate_dir(h,
                                    v[i],
                                    CHM_ENUMERATE_ALL,
                                    _print_ui,
                                    NULL))
            printf("   *** ERROR ***\n");
        }
    }

    chm_close(h);

    return 0;
}