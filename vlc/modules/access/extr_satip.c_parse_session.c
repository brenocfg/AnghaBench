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

/* Variables and functions */
 scalar_t__ KEEPALIVE_MARGIN ; 
 int /*<<< orphan*/  __MIN (int /*<<< orphan*/ ,unsigned int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static void parse_session(char *request_line, char *session, unsigned max, int *timeout) {
    char *state;
    char *tok;

    tok = strtok_r(request_line, ";", &state);
    if (tok == NULL)
        return;
    memcpy(session, tok, __MIN(strlen(tok), max - 1));

    while ((tok = strtok_r(NULL, ";", &state)) != NULL) {
        if (strncmp(tok, "timeout=", 8) == 0) {
            *timeout = atoi(tok + 8);
            if (*timeout > 5)
                *timeout -= KEEPALIVE_MARGIN;
            else if (*timeout > 0)
                *timeout = 1;
        }
    }
}