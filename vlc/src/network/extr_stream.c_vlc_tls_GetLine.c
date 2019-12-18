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
typedef  int /*<<< orphan*/  vlc_tls_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tls_Read (int /*<<< orphan*/ *,char*,int,int) ; 

char *vlc_tls_GetLine(vlc_tls_t *session)
{
    char *line = NULL;
    size_t linelen = 0, linesize = 0;

    do
    {
        if (linelen == linesize)
        {
            linesize += 1024;

            char *newline = realloc(line, linesize);
            if (unlikely(newline == NULL))
                goto error;
            line = newline;
        }

        if (vlc_tls_Read(session, line + linelen, 1, false) <= 0)
            goto error;
    }
    while (line[linelen++] != '\n');

    if (linelen >= 2 && line[linelen - 2] == '\r')
        line[linelen - 2] = '\0';
    return line;

error:
    free(line);
    return NULL;
}