#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_3__ {scalar_t__ st_size; } ;
typedef  TYPE_1__ SeafStat ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ SMALL_FILE_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int index_mem (unsigned char*,void*,scalar_t__,int,char const*) ; 
 char* malloc (scalar_t__) ; 
 void* mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,scalar_t__) ; 
 scalar_t__ readn (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int index_fd(unsigned char *sha1, int fd, SeafStat *st,
             enum object_type type, const char *path)
{
    int ret;
    uint64_t size = st->st_size;

    if (!size) {
        ret = index_mem(sha1, NULL, size, type, path);
    } else if (size <= SMALL_FILE_SIZE) {
        char *buf = malloc(size);
        if (size == readn(fd, buf, size)) {
            ret = index_mem(sha1, buf, size, type, path);
        } else {
            seaf_warning("short read %s\n", strerror(errno));
            ret = -1;
        }
        free(buf);
    } else {
        void *buf = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
        ret = index_mem(sha1, buf, size, type, path);
        munmap(buf, size);
    }
    close(fd);
    return ret;
}