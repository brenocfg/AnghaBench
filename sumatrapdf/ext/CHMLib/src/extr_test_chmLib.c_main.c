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
struct chmUnitInfo {int length; int space; scalar_t__ start; } ;
struct chmFile {int dummy; } ;
typedef  scalar_t__ LONGINT64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CHM_RESOLVE_SUCCESS ; 
 scalar_t__ alloca (unsigned int) ; 
 struct chmFile* chm_open (char*) ; 
 scalar_t__ chm_resolve_object (struct chmFile*,char*,struct chmUnitInfo*) ; 
 scalar_t__ chm_retrieve_object (struct chmFile*,struct chmUnitInfo*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(int c, char **v)
{
    struct chmFile *h;
    struct chmUnitInfo ui;

    if (c < 4)
    {
        fprintf(stderr, "usage: %s <chmfile> <filename> <destfile>\n", v[0]);
        exit(1);
    }

    h = chm_open(v[1]);
    if (h == NULL)
    {
        fprintf(stderr, "failed to open %s\n", v[1]);
        exit(1);
    }

    printf("resolving %s\n", v[2]);
    if (CHM_RESOLVE_SUCCESS == chm_resolve_object(h, 
                                                  v[2],
                                                  &ui))
    {
#ifdef WIN32
        unsigned char *buffer = (unsigned char *)alloca((unsigned int)ui.length);
#else
        unsigned char buffer[ui.length];
#endif
        LONGINT64 gotLen;
        FILE *fout;
        printf("    object: <%d, %lu, %lu>\n",
               ui.space,
               (unsigned long)ui.start,
               (unsigned long)ui.length);

        printf("extracting to '%s'\n", v[3]);
        gotLen = chm_retrieve_object(h, &ui, buffer, 0, ui.length);
        if (gotLen == 0)
        {
            printf("   extract failed\n");
            return 2;
        }
        else if ((fout = fopen(v[3], "wb")) == NULL)
        {
            printf("   create failed\n");
            return 3;
        }
        else
        {
            fwrite(buffer, 1, (unsigned int)ui.length, fout);
            fclose(fout);
            printf("   finished\n");
        }
    }
    else
        printf("    failed\n");

    return 0;
}