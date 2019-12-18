#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  total; int /*<<< orphan*/  skipped; int /*<<< orphan*/  translated; int /*<<< orphan*/  undo; int /*<<< orphan*/  redo; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LINESIZE ; 
 int NAMESIZE ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ *,char*,char*,char*,...) ; 
 int /*<<< orphan*/  memset (char*,char,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_Mark ; 
 scalar_t__ opt_mark ; 
 scalar_t__ opt_redo ; 
 scalar_t__ opt_undo ; 
 char* remove_mark (char*) ; 
 int sscanf (char*,char*,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 TYPE_1__ summ ; 
 int translate_file (char*,unsigned int,char*) ; 

__attribute__((used)) static void
translate_line(FILE *outFile, char *Line, char *path, char *LineOut)
{
    unsigned int offset;
    int cnt, res;
    char *sep, *tail, *mark, *s;
    unsigned char ch;

    if (!*Line)
        return;

    res = 1;
    mark = "";
    s = remove_mark(Line);
    if (opt_undo)
    {
        /* Strip all lines added by this tool: */
        char buf[NAMESIZE];
        if (sscanf(s, "| %s", buf) == 1)
            if (buf[0] == '0' || strcmp(buf, "----") == 0 || strcmp(buf, "L2L-") == 0 || strcmp(buf, "S---") == 0 || strcmp(buf, "R---") == 0 || atoi(buf))
                res = 0;
    }

    sep = strchr(s, ':');
    if (sep)
    {
        *sep = ' ';
        cnt = sscanf(s, "<%s %x%c", path, &offset, &ch);
        if (opt_undo)
        {
            if (cnt == 3 && ch == ' ')
            {
                tail = strchr(s, '>');
                tail = tail ? tail - 1 : tail;
                if (tail && tail[0] == ')' && tail[1] == '>')
                {
                    res = 0;
                    tail += 2;
                    mark = opt_mark ? "* " : "";
                    if (opt_redo && !(res = translate_file(path, offset, LineOut)))
                    {
                        log(outFile, "%s<%s:%x (%s)>%s", mark, path, offset, LineOut, tail);
                        summ.redo++;
                    }
                    else
                    {
                        log(outFile, "%s<%s:%x>%s", mark, path, offset, tail);
                        summ.undo++;
                    }
                }
                else
                {
                    mark = opt_Mark ? "? " : "";
                    summ.skipped++;
                }
                summ.total++;
            }
        }

        if (!opt_undo || opt_redo)
        {
            if (cnt == 3 && ch == '>')
            {
                tail = strchr(s, '>') + 1;
                if (!(res = translate_file(path, offset, LineOut)))
                {
                    mark = opt_mark ? "* " : "";
                    log(outFile, "%s<%s:%x (%s)>%s", mark, path, offset, LineOut, tail);
                    summ.translated++;
                }
                else
                {
                    mark = opt_Mark ? "? " : "";
                    summ.skipped++;
                }
                summ.total++;
            }
        }
    }
    if (res)
    {
        if (sep)
            *sep = ':';  // restore because not translated
        log(outFile, "%s%s", mark, s);
    }
    memset(Line, '\0', LINESIZE);  // flushed
}