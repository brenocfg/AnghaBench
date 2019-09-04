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
typedef  int /*<<< orphan*/  quit ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  disableRawMode (int /*<<< orphan*/ ) ; 
 int enableRawMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ isprint (char) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stdout ; 

void linenoisePrintKeyCodes(void) {
    char quit[4];

    printf("Linenoise key codes debugging mode.\n"
            "Press keys to see scan codes. Type 'quit' at any time to exit.\n");
    if (enableRawMode(STDIN_FILENO) == -1) return;
    memset(quit,' ',4);
    while(1) {
        char c;
        int nread;

        nread = read(STDIN_FILENO,&c,1);
        if (nread <= 0) continue;
        memmove(quit,quit+1,sizeof(quit)-1); /* shift string to left. */
        quit[sizeof(quit)-1] = c; /* Insert current char on the right. */
        if (memcmp(quit,"quit",sizeof(quit)) == 0) break;

        printf("'%c' %02x (%d) (type quit to exit)\n",
            isprint(c) ? c : '?', (int)c, (int)c);
        printf("\r"); /* Go left edge manually, we are in raw mode. */
        fflush(stdout);
    }
    disableRawMode(STDIN_FILENO);
}