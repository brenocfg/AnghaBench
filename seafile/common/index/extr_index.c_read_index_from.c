#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ondisk_cache_entry2 {int dummy; } ;
struct ondisk_cache_entry {int dummy; } ;
struct TYPE_4__ {scalar_t__ nsec; scalar_t__ sec; } ;
struct index_state {int cache_nr; int version; int has_modifier; TYPE_1__ timestamp; scalar_t__ initialized; } ;
struct cache_header {int /*<<< orphan*/  hdr_entries; int /*<<< orphan*/  hdr_version; } ;
struct cache_ext_hdr {int /*<<< orphan*/  ext_size; int /*<<< orphan*/  ext_name; } ;
struct cache_entry {int dummy; } ;
struct TYPE_5__ {scalar_t__ st_mtime; scalar_t__ st_size; } ;
typedef  TYPE_2__ SeafStat ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  alloc_index (struct index_state*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ convert_from_disk (struct ondisk_cache_entry*,struct cache_entry**) ; 
 scalar_t__ convert_from_disk2 (struct ondisk_cache_entry2*,struct cache_entry**) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  g_critical (char*) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ondisk_ce_size (struct cache_entry*) ; 
 scalar_t__ ondisk_ce_size2 (struct cache_entry*) ; 
 scalar_t__ read_index_extension (struct index_state*,unsigned int,char*,unsigned int) ; 
 scalar_t__ seaf_fstat (int,TYPE_2__*) ; 
 int seaf_util_open (char const*,int) ; 
 int /*<<< orphan*/  set_index_entry (struct index_state*,int,struct cache_entry*) ; 
 scalar_t__ verify_hdr (struct cache_header*,size_t) ; 

int read_index_from(struct index_state *istate, const char *path, int repo_version)
{
    int fd, i;
    SeafStat st;
    unsigned long src_offset;
    struct cache_header *hdr;
    void *mm;
    size_t mmap_size;

    if (istate->initialized)
        return istate->cache_nr;

    /* All newly created index files are version 4. */
    istate->version = 4;
    /* Index file stores modifier info if repo version > 0 */
    if (repo_version > 0)
        istate->has_modifier = 1;
    istate->timestamp.sec = 0;
    istate->timestamp.nsec = 0;
    fd = seaf_util_open (path, O_RDONLY | O_BINARY);
    if (fd < 0) {
        if (errno == ENOENT) {
            alloc_index (istate);
            return 0;
        }
        g_critical("index file open failed\n");
        return -1;
    }

    if (seaf_fstat(fd, &st)) {
        g_critical("cannot stat the open index\n");
        close(fd);
        return -1;
    }

    mmap_size = (size_t)st.st_size;
    if (mmap_size < sizeof(struct cache_header) + 20) {
        g_critical("index file smaller than expected\n");
        close(fd);
        return -1;
    }

    mm = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);
    if (mm == MAP_FAILED) {
        g_critical("unable to map index file\n");
        return -1;
    }

    hdr = mm;
    if (verify_hdr(hdr, mmap_size) < 0)
        goto unmap;

    /* Index version will be set to on-disk value here.
     * If the index is from an old repo, it will be set to 2.
     * But when we write the index, it'll be updated to version 4.
     */
    istate->version = ntohl(hdr->hdr_version);
    istate->cache_nr = ntohl(hdr->hdr_entries);
    alloc_index (istate);

    /*
     * The disk format is actually larger than the in-memory format,
     * due to space for nsec etc, so even though the in-memory one
     * has room for a few  more flags, we can allocate using the same
     * index size
     */

    src_offset = sizeof(*hdr);
    for (i = 0; i < istate->cache_nr; i++) {
        struct ondisk_cache_entry *disk_ce;
        struct ondisk_cache_entry2 *disk_ce2;
        struct cache_entry *ce;

        if (istate->version < 4) {
            disk_ce = (struct ondisk_cache_entry *)((char *)mm + src_offset);

            /* allocate each ce separately so that we can free new
             * entries added by add_index_entry() later.
             */
            if (convert_from_disk(disk_ce, &ce) < 0)
                return -1;

            src_offset += ondisk_ce_size(ce);
        } else {
            disk_ce2 = (struct ondisk_cache_entry2 *)((char *)mm + src_offset);

            /* allocate each ce separately so that we can free new
             * entries added by add_index_entry() later.
             */
            if (convert_from_disk2(disk_ce2, &ce) < 0)
                return -1;

            src_offset += ondisk_ce_size2(ce);
        }
        set_index_entry(istate, i, ce);
    }
    istate->timestamp.sec = st.st_mtime;
    istate->timestamp.nsec = 0;

    while (src_offset <= mmap_size - 20 - sizeof(struct cache_ext_hdr)) {
        /* After an array of active_nr index entries,
         * there can be arbitrary number of extended
         * sections, each of which is prefixed with
         * extension name (4-byte) and section length
         * in 4-byte network byte order.
         */
        struct cache_ext_hdr *exthdr;
        exthdr = (struct cache_ext_hdr *) ((char *)mm + src_offset);
        unsigned int name = ntohl(exthdr->ext_name);
        unsigned int size = ntohl(exthdr->ext_size);
        if (read_index_extension(istate,
                                 name,
                                 (char *) mm + src_offset + sizeof(struct cache_ext_hdr),
                                 size) < 0)
            goto unmap;
        src_offset += sizeof(struct cache_ext_hdr);
        src_offset += size;
    }

    munmap(mm, mmap_size);
    return istate->cache_nr;

unmap:
    munmap(mm, mmap_size);
    g_critical("index file corrupt\n");
    return -1;
}