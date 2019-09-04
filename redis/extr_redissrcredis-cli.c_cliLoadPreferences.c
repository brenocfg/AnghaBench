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
typedef  int /*<<< orphan*/ * sds ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_CLI_RCFILE_DEFAULT ; 
 int /*<<< orphan*/  REDIS_CLI_RCFILE_ENV ; 
 int /*<<< orphan*/  cliSetPreferences (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * getDotfilePath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsfreesplitres (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** sdssplitargs (char*,int*) ; 

void cliLoadPreferences(void) {
    sds rcfile = getDotfilePath(REDIS_CLI_RCFILE_ENV,REDIS_CLI_RCFILE_DEFAULT);
    if (rcfile == NULL) return;
    FILE *fp = fopen(rcfile,"r");
    char buf[1024];

    if (fp) {
        while(fgets(buf,sizeof(buf),fp) != NULL) {
            sds *argv;
            int argc;

            argv = sdssplitargs(buf,&argc);
            if (argc > 0) cliSetPreferences(argv,argc,0);
            sdsfreesplitres(argv,argc);
        }
        fclose(fp);
    }
    sdsfree(rcfile);
}