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
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

void get_file_nameA(CHAR **command_line, CHAR *file_name, int max_filename)
{
    CHAR *s = *command_line;
    int pos = 0;                /* position of pointer "s" in *command_line */
    file_name[0] = 0;

    if (!s[0]) {
        return;
    }
    if (s[0] == '"') {
        s++;
        (*command_line)++;
        while (s[0] != '"') {
            if (!s[0]) {
                _tprintf(_T("Unexpected end of file name!\n"));
                assert(0);
                //exit(1);
            }
            s++;
            pos++;
        }
    } else {
        while (s[0] && !isspace(s[0])) {
            s++;
            pos++;
        }
    }
    memcpy(file_name, *command_line, pos * sizeof((*command_line)[0]));
    /* remove the last backslash */
    if (file_name[pos - 1] == '\\') {
        file_name[pos - 1] = '\0';
    } else {
        file_name[pos] = '\0';
    }
    if (s[0]) {
        s++;
        pos++;
    }
    while (s[0] && isspace(s[0])) {
        s++;
        pos++;
    }
    (*command_line) += pos;
}