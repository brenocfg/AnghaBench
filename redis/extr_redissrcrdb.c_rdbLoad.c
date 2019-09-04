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
typedef  int /*<<< orphan*/  rio ;
typedef  int /*<<< orphan*/  rdbSaveInfo ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int C_ERR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int rdbLoadRio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rioInitWithFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  startLoading (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stopLoading () ; 

int rdbLoad(char *filename, rdbSaveInfo *rsi) {
    FILE *fp;
    rio rdb;
    int retval;

    if ((fp = fopen(filename,"r")) == NULL) return C_ERR;
    startLoading(fp);
    rioInitWithFile(&rdb,fp);
    retval = rdbLoadRio(&rdb,rsi,0);
    fclose(fp);
    stopLoading();
    return retval;
}