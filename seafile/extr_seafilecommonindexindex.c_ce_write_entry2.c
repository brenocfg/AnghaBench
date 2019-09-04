#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* sec; } ;
struct TYPE_5__ {void* sec; } ;
struct ondisk_cache_entry2 {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  sha1; void* size; void* gid; void* uid; void* mode; void* ino; void* dev; TYPE_3__ mtime; TYPE_1__ ctime; } ;
struct TYPE_8__ {int /*<<< orphan*/  sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  sec; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  sha1; int /*<<< orphan*/  ce_size; int /*<<< orphan*/  ce_gid; int /*<<< orphan*/  ce_uid; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  ce_ino; int /*<<< orphan*/  ce_dev; TYPE_4__ ce_mtime; TYPE_2__ ce_ctime; } ;
typedef  int /*<<< orphan*/  WriteIndexInfo ;

/* Variables and functions */
 struct ondisk_cache_entry2* calloc (int,int) ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry*) ; 
 int ce_write (int /*<<< orphan*/ *,int,struct ondisk_cache_entry2*,int) ; 
 int /*<<< orphan*/  free (struct ondisk_cache_entry2*) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* hton64 (int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ondisk_ce_size2 (struct cache_entry*) ; 

__attribute__((used)) static int ce_write_entry2(WriteIndexInfo *info, int fd, struct cache_entry *ce)
{
    int size = ondisk_ce_size2(ce);
    struct ondisk_cache_entry2 *ondisk = calloc(1, size);
    char *name;
    int result;

    ondisk->ctime.sec = hton64(ce->ce_ctime.sec);
    ondisk->mtime.sec = hton64(ce->ce_mtime.sec);
    ondisk->dev  = htonl(ce->ce_dev);
    ondisk->ino  = htonl(ce->ce_ino);
    ondisk->mode = htonl(ce->ce_mode);
    ondisk->uid  = htonl(ce->ce_uid);
    ondisk->gid  = htonl(ce->ce_gid);
    ondisk->size = hton64(ce->ce_size);
    hashcpy(ondisk->sha1, ce->sha1);
    ondisk->flags = htons(ce->ce_flags);
    name = ondisk->name;
    memcpy(name, ce->name, ce_namelen(ce));

    result = ce_write(info, fd, ondisk, size);
    free(ondisk);
    return result;
}