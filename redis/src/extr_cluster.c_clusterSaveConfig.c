#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ sds ;
typedef  scalar_t__ off_t ;
struct TYPE_4__ {TYPE_1__* cluster; int /*<<< orphan*/  cluster_configfile; } ;
struct TYPE_3__ {int /*<<< orphan*/  todo_before_sleep; scalar_t__ lastVoteEpoch; scalar_t__ currentEpoch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NODE_HANDSHAKE ; 
 int /*<<< orphan*/  CLUSTER_TODO_FSYNC_CONFIG ; 
 int /*<<< orphan*/  CLUSTER_TODO_SAVE_CONFIG ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ clusterGenNodesDescription (int /*<<< orphan*/ ) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  fsync (int) ; 
 int ftruncate (int,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,char,scalar_t__) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ sdscatprintf (scalar_t__,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 scalar_t__ sdsgrowzero (scalar_t__,scalar_t__) ; 
 size_t sdslen (scalar_t__) ; 
 TYPE_2__ server ; 
 scalar_t__ write (int,scalar_t__,size_t) ; 

int clusterSaveConfig(int do_fsync) {
    sds ci;
    size_t content_size;
    struct stat sb;
    int fd;

    server.cluster->todo_before_sleep &= ~CLUSTER_TODO_SAVE_CONFIG;

    /* Get the nodes description and concatenate our "vars" directive to
     * save currentEpoch and lastVoteEpoch. */
    ci = clusterGenNodesDescription(CLUSTER_NODE_HANDSHAKE);
    ci = sdscatprintf(ci,"vars currentEpoch %llu lastVoteEpoch %llu\n",
        (unsigned long long) server.cluster->currentEpoch,
        (unsigned long long) server.cluster->lastVoteEpoch);
    content_size = sdslen(ci);

    if ((fd = open(server.cluster_configfile,O_WRONLY|O_CREAT,0644))
        == -1) goto err;

    /* Pad the new payload if the existing file length is greater. */
    if (fstat(fd,&sb) != -1) {
        if (sb.st_size > (off_t)content_size) {
            ci = sdsgrowzero(ci,sb.st_size);
            memset(ci+content_size,'\n',sb.st_size-content_size);
        }
    }
    if (write(fd,ci,sdslen(ci)) != (ssize_t)sdslen(ci)) goto err;
    if (do_fsync) {
        server.cluster->todo_before_sleep &= ~CLUSTER_TODO_FSYNC_CONFIG;
        fsync(fd);
    }

    /* Truncate the file if needed to remove the final \n padding that
     * is just garbage. */
    if (content_size != sdslen(ci) && ftruncate(fd,content_size) == -1) {
        /* ftruncate() failing is not a critical error. */
    }
    close(fd);
    sdsfree(ci);
    return 0;

err:
    if (fd != -1) close(fd);
    sdsfree(ci);
    return -1;
}