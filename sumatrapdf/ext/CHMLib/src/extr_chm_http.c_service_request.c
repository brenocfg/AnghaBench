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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CONTENT_500 ; 
 int /*<<< orphan*/  INTERNAL_ERROR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  deliver_content (int /*<<< orphan*/ *,char*,struct chmFile*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_request(int fd, struct chmFile *file)
{
    char buffer[4096];
    char buffer2[4096];
    char *end;
    FILE *fout = fdopen(fd, "w+b");
    if (fout == NULL)
    {
        perror("chm_http: failed to fdopen client stream");
        write(fd, INTERNAL_ERROR, strlen(INTERNAL_ERROR));
        close(fd);
        return;
    }

    fgets(buffer, 4096, fout);
    while (1)
    {
        if (fgets(buffer2, 4096, fout) == NULL)
            break;
        if (buffer2[0] == '\r' || buffer2[0] == '\n'  ||  buffer2[0] == '\0')
            break;
    }
    end = strrchr(buffer, ' ');
    if (strncmp(end+1, "HTTP", 4) == 0)
        *end = '\0';
    if (strncmp(buffer, "GET ", 4) == 0)
        deliver_content(fout, buffer+4, file);
    else
    {
        fprintf(fout, CONTENT_500);
        fclose(fout);
        return;
    }
}