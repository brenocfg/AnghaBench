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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char*,char*,int) ; 

FILE * open_jp2file(const char filename[])
{
    FILE *fp;
    char *data;

    if (!(fp = fopen(filename, "a+b"))) {
        fprintf(stderr, "Original JP2 %s not found\n", filename);
        return NULL;
    }
    /* Check resource is a JP family file. */
    if (fseek(fp, 0, SEEK_SET) == -1) {
        fclose(fp);
        fprintf(stderr, "Original JP2 %s broken (fseek error)\n", filename);
        return NULL;
    }

    data = (char *)malloc(12);  /* size of header */
    if (fread(data, 12, 1, fp) != 1) {
        free(data);
        fclose(fp);
        fprintf(stderr, "Original JP2 %s broken (read error)\n", filename);
        return NULL;
    }

    if (*data || *(data + 1) || *(data + 2) ||
            *(data + 3) != 12 || strncmp(data + 4, "jP  \r\n\x87\n", 8)) {
        free(data);
        fclose(fp);
        fprintf(stderr, "No JPEG 2000 Signature box in target %s\n", filename);
        return NULL;
    }
    free(data);
    return fp;
}