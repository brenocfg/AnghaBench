#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sync_time; int /*<<< orphan*/  sync_date; int /*<<< orphan*/  modification_time; int /*<<< orphan*/  hit_rate; int /*<<< orphan*/  expire_time; int /*<<< orphan*/  expire_date; int /*<<< orphan*/  exempt_delta; int /*<<< orphan*/  cache_entry_type; int /*<<< orphan*/  access_time; } ;
typedef  TYPE_2__ entry_url ;
struct TYPE_6__ {int /*<<< orphan*/  dwExemptDelta; } ;
struct TYPE_8__ {int /*<<< orphan*/  LastAccessTime; int /*<<< orphan*/  LastModifiedTime; int /*<<< orphan*/  dwHitRate; int /*<<< orphan*/  ExpireTime; TYPE_1__ u; int /*<<< orphan*/  CacheEntryType; } ;
typedef  TYPE_3__ INTERNET_CACHE_ENTRY_INFOA ;
typedef  int DWORD ;

/* Variables and functions */
 int CACHE_ENTRY_ACCTIME_FC ; 
 int CACHE_ENTRY_ATTRIBUTE_FC ; 
 int CACHE_ENTRY_EXEMPT_DELTA_FC ; 
 int CACHE_ENTRY_EXPTIME_FC ; 
 int CACHE_ENTRY_HEADERINFO_FC ; 
 int CACHE_ENTRY_HITRATE_FC ; 
 int CACHE_ENTRY_MODTIME_FC ; 
 int CACHE_ENTRY_SYNCTIME_FC ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  file_time_to_dos_date_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD urlcache_set_entry_info(entry_url *url_entry, const INTERNET_CACHE_ENTRY_INFOA *entry_info, DWORD field_control)
{
    if (field_control & CACHE_ENTRY_ACCTIME_FC)
        url_entry->access_time = entry_info->LastAccessTime;
    if (field_control & CACHE_ENTRY_ATTRIBUTE_FC)
        url_entry->cache_entry_type = entry_info->CacheEntryType;
    if (field_control & CACHE_ENTRY_EXEMPT_DELTA_FC)
        url_entry->exempt_delta = entry_info->u.dwExemptDelta;
    if (field_control & CACHE_ENTRY_EXPTIME_FC)
        file_time_to_dos_date_time(&entry_info->ExpireTime, &url_entry->expire_date, &url_entry->expire_time);
    if (field_control & CACHE_ENTRY_HEADERINFO_FC)
        FIXME("CACHE_ENTRY_HEADERINFO_FC unimplemented\n");
    if (field_control & CACHE_ENTRY_HITRATE_FC)
        url_entry->hit_rate = entry_info->dwHitRate;
    if (field_control & CACHE_ENTRY_MODTIME_FC)
        url_entry->modification_time = entry_info->LastModifiedTime;
    if (field_control & CACHE_ENTRY_SYNCTIME_FC)
        file_time_to_dos_date_time(&entry_info->LastAccessTime, &url_entry->sync_date, &url_entry->sync_time);

    return ERROR_SUCCESS;
}