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
struct chmUnitInfo {char* path; scalar_t__ length; } ;
struct chmFile {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  size_t LONGUINT64 ;
typedef  scalar_t__ LONGINT64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CHM_ENUMERATOR_CONTINUE ; 
 int CHM_ENUMERATOR_FAILURE ; 
 scalar_t__ chm_retrieve_object (struct chmFile*,struct chmUnitInfo*,unsigned char*,size_t,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rmkdir (char*) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

int _extract_callback(struct chmFile *h,
              struct chmUnitInfo *ui,
              void *context)
{
    LONGUINT64 ui_path_len;
    char buffer[32768];
    struct extract_context *ctx = (struct extract_context *)context;
    char *i;

    if (ui->path[0] != '/')
        return CHM_ENUMERATOR_CONTINUE;

    /* quick hack for security hole mentioned by Sven Tantau */
    if (strstr(ui->path, "/../") != NULL)
    {
        /* fprintf(stderr, "Not extracting %s (dangerous path)\n", ui->path); */
        return CHM_ENUMERATOR_CONTINUE;
    }

    if (snprintf(buffer, sizeof(buffer), "%s%s", ctx->base_path, ui->path) > 1024)
        return CHM_ENUMERATOR_FAILURE;

    /* Get the length of the path */
    ui_path_len = strlen(ui->path)-1;

    /* Distinguish between files and dirs */
    if (ui->path[ui_path_len] != '/' )
    {
        FILE *fout;
        LONGINT64 len, remain=ui->length;
        LONGUINT64 offset = 0;

        printf("--> %s\n", ui->path);
        if ((fout = fopen(buffer, "wb")) == NULL)
	{
	    /* make sure that it isn't just a missing directory before we abort */ 
	    char newbuf[32768];
	    strcpy(newbuf, buffer);
	    i = strrchr(newbuf, '/');
	    *i = '\0';
	    rmkdir(newbuf);
	    if ((fout = fopen(buffer, "wb")) == NULL)
              return CHM_ENUMERATOR_FAILURE;
	}

        while (remain != 0)
        {
            len = chm_retrieve_object(h, ui, (unsigned char *)buffer, offset, 32768);
            if (len > 0)
            {
                fwrite(buffer, 1, (size_t)len, fout);
                offset += len;
                remain -= len;
            }
            else
            {
                fprintf(stderr, "incomplete file: %s\n", ui->path);
                break;
            }
        }

        fclose(fout);
    }
    else
    {
        if (rmkdir(buffer) == -1)
            return CHM_ENUMERATOR_FAILURE;
    }

    return CHM_ENUMERATOR_CONTINUE;
}