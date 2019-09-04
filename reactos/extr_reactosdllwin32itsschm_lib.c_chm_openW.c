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
struct chmUnitInfo {scalar_t__ space; scalar_t__ length; } ;
struct chmLzxcControlData {int windowSize; int resetInterval; int windowsPerReset; } ;
struct chmItspHeader {int index_root; int index_head; int /*<<< orphan*/  block_len; scalar_t__ header_len; } ;
struct chmItsfHeader {int /*<<< orphan*/  dir_offset; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  dir_len; } ;
struct TYPE_4__ {TYPE_1__* DebugInfo; } ;
struct chmFile {int index_root; int index_head; int compression_enabled; int window_size; int reset_interval; int reset_blkcount; int /*<<< orphan*/  reset_table; struct chmUnitInfo rt_unit; struct chmUnitInfo cn_unit; int /*<<< orphan*/  block_len; int /*<<< orphan*/  dir_len; int /*<<< orphan*/  dir_offset; int /*<<< orphan*/  data_offset; TYPE_2__ cache_mutex; TYPE_2__ lzx_mutex; TYPE_2__ mutex; int /*<<< orphan*/  fd; scalar_t__ cache_num_blocks; int /*<<< orphan*/ * cache_block_indices; int /*<<< orphan*/ * cache_blocks; int /*<<< orphan*/ * lzx_state; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {void** Spare; } ;
typedef  void* DWORD_PTR ;

/* Variables and functions */
 scalar_t__ CHM_COMPRESSED ; 
 int /*<<< orphan*/  CHM_MAX_BLOCKS_CACHED ; 
 int /*<<< orphan*/  CHM_NULL_FD ; 
 int /*<<< orphan*/  CHM_PARAM_MAX_BLOCKS_CACHED ; 
 scalar_t__ CHM_RESOLVE_SUCCESS ; 
 int /*<<< orphan*/  CreateFileW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct chmFile* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct chmFile*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_2__*) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  _CHMU_CONTENT ; 
 int /*<<< orphan*/  _CHMU_LZXC_CONTROLDATA ; 
 int /*<<< orphan*/  _CHMU_RESET_TABLE ; 
 unsigned int _CHM_ITSF_V3_LEN ; 
 unsigned int _CHM_ITSP_V1_LEN ; 
 unsigned int _CHM_LZXC_RESETTABLE_V1_LEN ; 
 unsigned int _chm_fetch_bytes (struct chmFile*,unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  _unmarshal_itsf_header (unsigned char**,unsigned int*,struct chmItsfHeader*) ; 
 int /*<<< orphan*/  _unmarshal_itsp_header (unsigned char**,unsigned int*,struct chmItspHeader*) ; 
 int /*<<< orphan*/  _unmarshal_lzxc_control_data (unsigned char**,unsigned int*,struct chmLzxcControlData*) ; 
 int /*<<< orphan*/  _unmarshal_lzxc_reset_table (unsigned char**,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chm_close (struct chmFile*) ; 
 scalar_t__ chm_resolve_object (struct chmFile*,int /*<<< orphan*/ ,struct chmUnitInfo*) ; 
 unsigned int chm_retrieve_object (struct chmFile*,struct chmUnitInfo*,unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  chm_set_param (struct chmFile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct chmFile *chm_openW(const WCHAR *filename)
{
    unsigned char               sbuffer[256];
    unsigned int                sremain;
    unsigned char              *sbufpos;
    struct chmFile             *newHandle=NULL;
    struct chmItsfHeader        itsfHeader;
    struct chmItspHeader        itspHeader;
#if 0
    struct chmUnitInfo          uiSpan;
#endif
    struct chmUnitInfo          uiLzxc;
    struct chmLzxcControlData   ctlData;

    /* allocate handle */
    newHandle = HeapAlloc(GetProcessHeap(), 0, sizeof(struct chmFile));
    newHandle->fd = CHM_NULL_FD;
    newHandle->lzx_state = NULL;
    newHandle->cache_blocks = NULL;
    newHandle->cache_block_indices = NULL;
    newHandle->cache_num_blocks = 0;

    /* open file */
    if ((newHandle->fd=CreateFileW(filename,
                                   GENERIC_READ,
                                   FILE_SHARE_READ,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL,
                                   NULL)) == CHM_NULL_FD)
    {
        HeapFree(GetProcessHeap(), 0, newHandle);
        return NULL;
    }

    /* initialize mutexes, if needed */
    InitializeCriticalSection(&newHandle->mutex);
    newHandle->mutex.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": chmFile.mutex");
    InitializeCriticalSection(&newHandle->lzx_mutex);
    newHandle->lzx_mutex.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": chmFile.lzx_mutex");
    InitializeCriticalSection(&newHandle->cache_mutex);
    newHandle->cache_mutex.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": chmFile.cache_mutex");

    /* read and verify header */
    sremain = _CHM_ITSF_V3_LEN;
    sbufpos = sbuffer;
    if (_chm_fetch_bytes(newHandle, sbuffer, 0, sremain) != sremain    ||
        !_unmarshal_itsf_header(&sbufpos, &sremain, &itsfHeader))
    {
        chm_close(newHandle);
        return NULL;
    }

    /* stash important values from header */
    newHandle->dir_offset  = itsfHeader.dir_offset;
    newHandle->dir_len     = itsfHeader.dir_len;
    newHandle->data_offset = itsfHeader.data_offset;

    /* now, read and verify the directory header chunk */
    sremain = _CHM_ITSP_V1_LEN;
    sbufpos = sbuffer;
    if (_chm_fetch_bytes(newHandle, sbuffer,
                         itsfHeader.dir_offset, sremain) != sremain    ||
        !_unmarshal_itsp_header(&sbufpos, &sremain, &itspHeader))
    {
        chm_close(newHandle);
        return NULL;
    }

    /* grab essential information from ITSP header */
    newHandle->dir_offset += itspHeader.header_len;
    newHandle->dir_len    -= itspHeader.header_len;
    newHandle->index_root  = itspHeader.index_root;
    newHandle->index_head  = itspHeader.index_head;
    newHandle->block_len   = itspHeader.block_len;

    /* if the index root is -1, this means we don't have any PMGI blocks.
     * as a result, we must use the sole PMGL block as the index root
     */
    if (newHandle->index_root == -1)
        newHandle->index_root = newHandle->index_head;

    /* initialize cache */
    chm_set_param(newHandle, CHM_PARAM_MAX_BLOCKS_CACHED,
                  CHM_MAX_BLOCKS_CACHED);

    /* By default, compression is enabled. */
    newHandle->compression_enabled = 1;

    /* prefetch most commonly needed unit infos */
    if (CHM_RESOLVE_SUCCESS != chm_resolve_object(newHandle,
                                                  _CHMU_RESET_TABLE,
                                                  &newHandle->rt_unit)    ||
        newHandle->rt_unit.space == CHM_COMPRESSED                        ||
        CHM_RESOLVE_SUCCESS != chm_resolve_object(newHandle,
                                                  _CHMU_CONTENT,
                                                  &newHandle->cn_unit)    ||
        newHandle->cn_unit.space == CHM_COMPRESSED                        ||
        CHM_RESOLVE_SUCCESS != chm_resolve_object(newHandle,
                                                  _CHMU_LZXC_CONTROLDATA,
                                                  &uiLzxc)                ||
        uiLzxc.space == CHM_COMPRESSED)
    {
        newHandle->compression_enabled = 0;
    }

    /* read reset table info */
    if (newHandle->compression_enabled)
    {
        sremain = _CHM_LZXC_RESETTABLE_V1_LEN;
        sbufpos = sbuffer;
        if (chm_retrieve_object(newHandle, &newHandle->rt_unit, sbuffer,
                                0, sremain) != sremain                        ||
            !_unmarshal_lzxc_reset_table(&sbufpos, &sremain,
                                         &newHandle->reset_table))
        {
            newHandle->compression_enabled = 0;
        }
    }

    /* read control data */
    if (newHandle->compression_enabled)
    {
        sremain = (unsigned long)uiLzxc.length;
        sbufpos = sbuffer;
        if (chm_retrieve_object(newHandle, &uiLzxc, sbuffer,
                                0, sremain) != sremain                       ||
            !_unmarshal_lzxc_control_data(&sbufpos, &sremain,
                                          &ctlData))
        {
            newHandle->compression_enabled = 0;
        }

        newHandle->window_size = ctlData.windowSize;
        newHandle->reset_interval = ctlData.resetInterval;

/* Jed, Mon Jun 28: Experimentally, it appears that the reset block count */
/*       must be multiplied by this formerly unknown ctrl data field in   */
/*       order to decompress some files.                                  */
#if 0
        newHandle->reset_blkcount = newHandle->reset_interval /
                    (newHandle->window_size / 2);
#else
        newHandle->reset_blkcount = newHandle->reset_interval    /
                                    (newHandle->window_size / 2) *
                                    ctlData.windowsPerReset;
#endif
    }

    return newHandle;
}