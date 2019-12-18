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
struct extract_context {char* base_path; } ;
struct chmFile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHM_ENUMERATE_ALL ; 
 int /*<<< orphan*/  _extract_callback ; 
 int /*<<< orphan*/  chm_close (struct chmFile*) ; 
 int /*<<< orphan*/  chm_enumerate (struct chmFile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct chmFile* chm_open (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(int c, char **v)
{
    struct chmFile *h;
    struct extract_context ec;

    if (c < 3)
    {
        fprintf(stderr, "usage: %s <chmfile> <outdir>\n", v[0]);
        exit(1);
    }

    h = chm_open(v[1]);
    if (h == NULL)
    {
        fprintf(stderr, "failed to open %s\n", v[1]);
        exit(1);
    }

    printf("%s:\n", v[1]);
    ec.base_path = v[2];
    if (! chm_enumerate(h,
                        CHM_ENUMERATE_ALL,
                        _extract_callback,
                        (void *)&ec))
        printf("   *** ERROR ***\n");

    chm_close(h);

    return 0;
}