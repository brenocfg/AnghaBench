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
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {scalar_t__ eval_ldb; } ;

/* Variables and functions */
 TYPE_1__ config ; 
 int /*<<< orphan*/ * sds_malloc (int) ; 
 int /*<<< orphan*/  sdsnewlen (char*,int) ; 
 int /*<<< orphan*/ * sdssplitargs (char*,int*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static sds *cliSplitArgs(char *line, int *argc) {
    if (config.eval_ldb && (strstr(line,"eval ") == line ||
                            strstr(line,"e ") == line))
    {
        sds *argv = sds_malloc(sizeof(sds)*2);
        *argc = 2;
        int len = strlen(line);
        int elen = line[1] == ' ' ? 2 : 5; /* "e " or "eval "? */
        argv[0] = sdsnewlen(line,elen-1);
        argv[1] = sdsnewlen(line+elen,len-elen);
        return argv;
    } else {
        return sdssplitargs(line,argc);
    }
}