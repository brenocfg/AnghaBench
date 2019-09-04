#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ user ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/ * sds ;
struct TYPE_9__ {TYPE_1__* data; } ;
typedef  TYPE_2__ raxIterator ;

/* Variables and functions */
 int /*<<< orphan*/ * ACLDescribeUser (TYPE_1__*) ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  Users ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getpid () ; 
 scalar_t__ mstime () ; 
 int open (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ raxNext (TYPE_2__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStart (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStop (TYPE_2__*) ; 
 int rename (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * sdscatfmt (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/ * sdscatlen (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * sdscatsds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdsnew (char const*) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 scalar_t__ write (int,int /*<<< orphan*/ *,scalar_t__) ; 

int ACLSaveToFile(const char *filename) {
    sds acl = sdsempty();
    int fd = -1;
    sds tmpfilename = NULL;
    int retval = C_ERR;

    /* Let's generate an SDS string containing the new version of the
     * ACL file. */
    raxIterator ri;
    raxStart(&ri,Users);
    raxSeek(&ri,"^",NULL,0);
    while(raxNext(&ri)) {
        user *u = ri.data;
        /* Return information in the configuration file format. */
        sds user = sdsnew("user ");
        user = sdscatsds(user,u->name);
        user = sdscatlen(user," ",1);
        sds descr = ACLDescribeUser(u);
        user = sdscatsds(user,descr);
        sdsfree(descr);
        acl = sdscatsds(acl,user);
        acl = sdscatlen(acl,"\n",1);
        sdsfree(user);
    }
    raxStop(&ri);

    /* Create a temp file with the new content. */
    tmpfilename = sdsnew(filename);
    tmpfilename = sdscatfmt(tmpfilename,".tmp-%i-%I",
        (int)getpid(),(int)mstime());
    if ((fd = open(tmpfilename,O_WRONLY|O_CREAT,0644)) == -1) {
        serverLog(LL_WARNING,"Opening temp ACL file for ACL SAVE: %s",
            strerror(errno));
        goto cleanup;
    }

    /* Write it. */
    if (write(fd,acl,sdslen(acl)) != (ssize_t)sdslen(acl)) {
        serverLog(LL_WARNING,"Writing ACL file for ACL SAVE: %s",
            strerror(errno));
        goto cleanup;
    }
    close(fd); fd = -1;

    /* Let's replace the new file with the old one. */
    if (rename(tmpfilename,filename) == -1) {
        serverLog(LL_WARNING,"Renaming ACL file for ACL SAVE: %s",
            strerror(errno));
        goto cleanup;
    }
    sdsfree(tmpfilename); tmpfilename = NULL;
    retval = C_OK; /* If we reached this point, everything is fine. */

cleanup:
    if (fd != -1) close(fd);
    if (tmpfilename) unlink(tmpfilename);
    sdsfree(tmpfilename);
    sdsfree(acl);
    return retval;
}