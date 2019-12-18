#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int st_mode; int st_size; } ;
typedef  TYPE_1__ SeafStat ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_BLOB ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int SEAF_PATH_MAX ; 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  hash_sha1_file (char*,int,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  index_fd (unsigned char*,int,TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int readlink (char const*,char*,int) ; 
 int seaf_util_open (char const*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typename (int /*<<< orphan*/ ) ; 

int index_path(unsigned char *sha1, const char *path, SeafStat *st)
{
    int fd;
    char buf[SEAF_PATH_MAX];
    int pathlen;

    switch (st->st_mode & S_IFMT) {
    case S_IFREG:
        fd = seaf_util_open (path, O_RDONLY | O_BINARY);
        if (fd < 0) {
            seaf_warning("g_open (\"%s\"): %s\n", path, strerror(errno));
            return -1;
        }
        if (index_fd(sha1, fd, st, OBJ_BLOB, path) < 0) {
            return -1;
        }
        break;
#ifndef WIN32        
    case S_IFLNK:
        pathlen = readlink(path, buf, SEAF_PATH_MAX);
        if (pathlen != st->st_size) {
            char *errstr = strerror(errno);
            seaf_warning("readlink(\"%s\"): %s\n", path, errstr);
            return -1;
        }
        hash_sha1_file(buf, pathlen, typename(OBJ_BLOB), sha1);
        break;
#endif        
    default:
        seaf_warning("%s: unsupported file type\n", path);
        return -1;
    }
    return 0;
}