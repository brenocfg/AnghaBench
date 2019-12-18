#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  verstr ;
struct TYPE_8__ {int argc; TYPE_7__** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 char* REDIS_VERSION ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_1__*,TYPE_7__*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lolwut5Command (TYPE_1__*) ; 
 int /*<<< orphan*/  lolwut6Command (TYPE_1__*) ; 
 int /*<<< orphan*/  lolwutUnstableCommand (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

void lolwutCommand(client *c) {
    char *v = REDIS_VERSION;
    char verstr[64];

    if (c->argc >= 3 && !strcasecmp(c->argv[1]->ptr,"version")) {
        long ver;
        if (getLongFromObjectOrReply(c,c->argv[2],&ver,NULL) != C_OK) return;
        snprintf(verstr,sizeof(verstr),"%u.0.0",(unsigned int)ver);
        v = verstr;

        /* Adjust argv/argc to filter the "VERSION ..." option, since the
         * specific LOLWUT version implementations don't know about it
         * and expect their arguments. */
        c->argv += 2;
        c->argc -= 2;
    }

    if ((v[0] == '5' && v[1] == '.' && v[2] != '9') ||
        (v[0] == '4' && v[1] == '.' && v[2] == '9'))
        lolwut5Command(c);
    else if ((v[0] == '6' && v[1] == '.' && v[2] != '9') ||
             (v[0] == '5' && v[1] == '.' && v[2] == '9'))
        lolwut6Command(c);
    else
        lolwutUnstableCommand(c);

    /* Fix back argc/argv in case of VERSION argument. */
    if (v == verstr) {
        c->argv -= 2;
        c->argc += 2;
    }
}