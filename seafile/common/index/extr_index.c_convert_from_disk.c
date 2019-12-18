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
struct TYPE_8__ {int /*<<< orphan*/  sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  sec; } ;
struct ondisk_cache_entry {char* name; int /*<<< orphan*/  sha1; int /*<<< orphan*/  size; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; TYPE_4__ mtime; TYPE_2__ ctime; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {void* sec; } ;
struct TYPE_5__ {void* sec; } ;
struct cache_entry {unsigned int ce_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  sha1; int /*<<< orphan*/  ce_size; void* ce_gid; void* ce_uid; void* ce_mode; void* ce_ino; void* ce_dev; TYPE_3__ ce_mtime; TYPE_1__ ce_ctime; } ;

/* Variables and functions */
 unsigned int CE_NAMEMASK ; 
 int /*<<< orphan*/  cache_entry_size (size_t) ; 
 struct cache_entry* calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ntoh64 (int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int convert_from_disk(struct ondisk_cache_entry *ondisk, struct cache_entry **ce)
{
    size_t len;
    const char *name;
    unsigned int flags = 0;
    struct cache_entry *ret;

    flags = ntohs(ondisk->flags);

    len = flags & CE_NAMEMASK;

    /* if (flags & CE_EXTENDED) { */
    /*     struct ondisk_cache_entry_extended *ondisk2; */
    /*     int extended_flags; */
    /*     ondisk2 = (struct ondisk_cache_entry_extended *)ondisk; */
    /*     extended_flags = ntohs(ondisk2->flags2) << 16; */
    /*     /\* We do not yet understand any bit out of CE_EXTENDED_FLAGS *\/ */
    /*     if (extended_flags & ~CE_EXTENDED_FLAGS) { */
    /*         g_critical("Unknown index entry format %08x\n", extended_flags); */
    /*         return -1; */
    /*     } */
    /*     flags |= extended_flags; */
    /*     name = ondisk2->name; */
    /* } */
    /* else */
    name = ondisk->name;

    if (len == CE_NAMEMASK)
        len = strlen(name);

    ret = calloc(1, cache_entry_size(len));

    ret->ce_ctime.sec = ntohl(ondisk->ctime.sec);
    ret->ce_mtime.sec = ntohl(ondisk->mtime.sec);
    ret->ce_dev   = ntohl(ondisk->dev);
    ret->ce_ino   = ntohl(ondisk->ino);
    ret->ce_mode  = ntohl(ondisk->mode);
    ret->ce_uid   = ntohl(ondisk->uid);
    ret->ce_gid   = ntohl(ondisk->gid);
    ret->ce_size  = ntoh64(ondisk->size);
    /* On-disk flags are just 16 bits */
    ret->ce_flags = flags;

    hashcpy(ret->sha1, ondisk->sha1);

    /*
     * NEEDSWORK: If the original index is crafted, this copy could
     * go unchecked.
     */
    memcpy(ret->name, name, len + 1);

    *ce = ret;

    return 0;
}