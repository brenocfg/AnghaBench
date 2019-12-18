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
struct chmUnitInfo {int length; } ;
struct chmFile {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CHM_RESOLVE_SUCCESS ; 
 char* CONTENT_404 ; 
 scalar_t__ chm_resolve_object (struct chmFile*,char const*,struct chmUnitInfo*) ; 
 scalar_t__ chm_retrieve_object (struct chmFile*,struct chmUnitInfo*,unsigned char*,int,int) ; 
 int /*<<< orphan*/  deliver_index (int /*<<< orphan*/ *,struct chmFile*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 char* lookup_mime (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void deliver_content(FILE *fout, const char *filename, struct chmFile *file)
{
    struct chmUnitInfo ui;
    const char *ext;
    unsigned char buffer[65536];
    int swath, offset;

    if (strcmp(filename,"/") == 0)
    {
        deliver_index(fout,file);
        fclose(fout);
        return;
    }
    /* try to find the file */
    if (chm_resolve_object(file, filename, &ui) != CHM_RESOLVE_SUCCESS)
    {
        fprintf(fout, CONTENT_404);
        fclose(fout);
        return;
    }

    /* send the file back */
    ext = strrchr(filename, '.');
    fprintf(fout, "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n",
            (int)ui.length,
            lookup_mime(ext));

    /* pump the data out */
    swath = 65536;
    offset = 0;
    while (offset < ui.length)
    {
        if ((ui.length - offset) < 65536)
            swath = ui.length - offset;
        else
            swath = 65536;
        swath = (int)chm_retrieve_object(file, &ui, buffer, offset, swath);
        offset += swath;
        fwrite(buffer, 1, swath, fout);
    }
    fclose(fout);
}