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
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int fread (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  stderr ; 

char * read_xmlfile(const char filename[], long *fsize)
{
    FILE *fp;
    char *data;

    /*  fprintf( stderr, "open %s\n", filename);*/
    if (!(fp = fopen(filename, "r"))) {
        fprintf(stderr, "XML file %s not found\n", filename);
        return NULL;
    }

    if (fseek(fp, 0, SEEK_END) == -1) {
        fprintf(stderr, "XML file %s broken (seek error)\n", filename);
        fclose(fp);
        return NULL;
    }

    if ((*fsize = ftell(fp)) == -1) {
        fprintf(stderr, "XML file %s broken (seek error)\n", filename);
        fclose(fp);
        return NULL;
    }
    assert(*fsize >= 0);

    if (fseek(fp, 0, SEEK_SET) == -1) {
        fprintf(stderr, "XML file %s broken (seek error)\n", filename);
        fclose(fp);
        return NULL;
    }

    data = (char *)malloc((size_t) * fsize);

    if (fread(data, (size_t)*fsize, 1, fp) != 1) {
        fprintf(stderr, "XML file %s broken (read error)\n", filename);
        free(data);
        fclose(fp);
        return NULL;
    }

    fclose(fp);

    return data;
}