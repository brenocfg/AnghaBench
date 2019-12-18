#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char* sds ;
struct TYPE_6__ {int type; TYPE_1__* org; int /*<<< orphan*/  full; } ;
struct TYPE_5__ {int /*<<< orphan*/  hints; } ;
struct TYPE_4__ {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int CLI_HELP_COMMAND ; 
 TYPE_3__* helpEntries ; 
 int helpEntriesLen ; 
 scalar_t__ isspace (char const) ; 
 TYPE_2__ pref ; 
 char* sdscatsds (char*,char*) ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int /*<<< orphan*/  sdsfreesplitres (char**,int) ; 
 scalar_t__ sdslen (char*) ; 
 char* sdsnew (int /*<<< orphan*/ ) ; 
 char* sdsnewlen (char*,int) ; 
 int /*<<< orphan*/  sdsrange (char*,int,int) ; 
 char** sdssplitargs (char const*,int*) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *hintsCallback(const char *buf, int *color, int *bold) {
    if (!pref.hints) return NULL;

    int i, argc, buflen = strlen(buf);
    sds *argv = sdssplitargs(buf,&argc);
    int endspace = buflen && isspace(buf[buflen-1]);

    /* Check if the argument list is empty and return ASAP. */
    if (argc == 0) {
        sdsfreesplitres(argv,argc);
        return NULL;
    }

    for (i = 0; i < helpEntriesLen; i++) {
        if (!(helpEntries[i].type & CLI_HELP_COMMAND)) continue;

        if (strcasecmp(argv[0],helpEntries[i].full) == 0)
        {
            *color = 90;
            *bold = 0;
            sds hint = sdsnew(helpEntries[i].org->params);

            /* Remove arguments from the returned hint to show only the
             * ones the user did not yet typed. */
            int toremove = argc-1;
            while(toremove > 0 && sdslen(hint)) {
                if (hint[0] == '[') break;
                if (hint[0] == ' ') toremove--;
                sdsrange(hint,1,-1);
            }

            /* Add an initial space if needed. */
            if (!endspace) {
                sds newhint = sdsnewlen(" ",1);
                newhint = sdscatsds(newhint,hint);
                sdsfree(hint);
                hint = newhint;
            }

            sdsfreesplitres(argv,argc);
            return hint;
        }
    }
    sdsfreesplitres(argv,argc);
    return NULL;
}