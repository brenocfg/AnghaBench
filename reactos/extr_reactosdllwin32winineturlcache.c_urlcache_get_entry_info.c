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
typedef  int /*<<< orphan*/  urlcache_header ;
struct hash_entry {scalar_t__ offset; } ;
struct TYPE_4__ {scalar_t__ signature; } ;
struct TYPE_5__ {char const* url_off; int header_info_off; int header_info_size; int cache_entry_type; char const* local_name_off; TYPE_1__ header; } ;
typedef  TYPE_2__ entry_url ;
typedef  int /*<<< orphan*/  cache_container ;
typedef  int LPCSTR ;
typedef  scalar_t__ LPBYTE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int GET_INSTALLED_ENTRY ; 
 int INSTALLED_CACHE_ENTRY ; 
 int /*<<< orphan*/  MIN_BLOCK_NO ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ URL_SIGNATURE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/ * cache_container_lock_index (int /*<<< orphan*/ *) ; 
 int cache_container_open_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_container_unlock_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cache_containers_find (char const*,int /*<<< orphan*/ **) ; 
 int debugstr_a (char const*) ; 
 int debugstr_an (int,int) ; 
 int urlcache_copy_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urlcache_find_hash_entry (int /*<<< orphan*/ *,char const*,struct hash_entry**) ; 

__attribute__((used)) static BOOL urlcache_get_entry_info(const char *url, void *entry_info,
        DWORD *size, DWORD flags, BOOL unicode)
{
    urlcache_header *header;
    struct hash_entry *hash_entry;
    const entry_url *url_entry;
    cache_container *container;
    DWORD error;

    TRACE("(%s, %p, %p, %x, %x)\n", debugstr_a(url), entry_info, size, flags, unicode);

    if(flags & ~GET_INSTALLED_ENTRY)
        FIXME("ignoring unsupported flags: %x\n", flags);

    error = cache_containers_find(url, &container);
    if(error != ERROR_SUCCESS) {
        SetLastError(error);
        return FALSE;
    }

    error = cache_container_open_index(container, MIN_BLOCK_NO);
    if(error != ERROR_SUCCESS) {
        SetLastError(error);
        return FALSE;
    }

    if(!(header = cache_container_lock_index(container)))
        return FALSE;

    if(!urlcache_find_hash_entry(header, url, &hash_entry)) {
        cache_container_unlock_index(container, header);
        WARN("entry %s not found!\n", debugstr_a(url));
        SetLastError(ERROR_FILE_NOT_FOUND);
        return FALSE;
    }

    url_entry = (const entry_url*)((LPBYTE)header + hash_entry->offset);
    if(url_entry->header.signature != URL_SIGNATURE) {
        cache_container_unlock_index(container, header);
        FIXME("Trying to retrieve entry of unknown format %s\n",
                debugstr_an((LPCSTR)&url_entry->header.signature, sizeof(DWORD)));
        SetLastError(ERROR_FILE_NOT_FOUND);
        return FALSE;
    }

    TRACE("Found URL: %s\n", debugstr_a((LPCSTR)url_entry + url_entry->url_off));
    TRACE("Header info: %s\n", debugstr_an((LPCSTR)url_entry +
                url_entry->header_info_off, url_entry->header_info_size));

    if((flags & GET_INSTALLED_ENTRY) && !(url_entry->cache_entry_type & INSTALLED_CACHE_ENTRY)) {
        cache_container_unlock_index(container, header);
        SetLastError(ERROR_FILE_NOT_FOUND);
        return FALSE;
    }

    if(size) {
        if(!entry_info)
            *size = 0;

        error = urlcache_copy_entry(container, header, entry_info, size, url_entry, unicode);
        if(error != ERROR_SUCCESS) {
            cache_container_unlock_index(container, header);
            SetLastError(error);
            return FALSE;
        }
        if(url_entry->local_name_off)
            TRACE("Local File Name: %s\n", debugstr_a((LPCSTR)url_entry + url_entry->local_name_off));
    }

    cache_container_unlock_index(container, header);
    return TRUE;
}