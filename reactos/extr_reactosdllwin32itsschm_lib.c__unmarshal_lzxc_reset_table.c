#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct chmLzxcResetTable {int version; int block_count; int unknown; int table_offset; int /*<<< orphan*/  block_len; int /*<<< orphan*/  compressed_len; int /*<<< orphan*/  uncompressed_len; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int _CHM_LZXC_RESETTABLE_V1_LEN ; 
 int /*<<< orphan*/  _unmarshal_uint32 (unsigned char**,unsigned int*,int*) ; 
 int /*<<< orphan*/  _unmarshal_uint64 (unsigned char**,unsigned int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL _unmarshal_lzxc_reset_table(unsigned char **pData,
                                        unsigned int *pDataLen,
                                        struct chmLzxcResetTable *dest)
{
    /* we only know how to deal with a 0x28 byte structures */
    if (*pDataLen != _CHM_LZXC_RESETTABLE_V1_LEN)
        return FALSE;

    /* unmarshal fields */
    _unmarshal_uint32    (pData, pDataLen, &dest->version);
    _unmarshal_uint32    (pData, pDataLen, &dest->block_count);
    _unmarshal_uint32    (pData, pDataLen, &dest->unknown);
    _unmarshal_uint32    (pData, pDataLen, &dest->table_offset);
    _unmarshal_uint64    (pData, pDataLen, &dest->uncompressed_len);
    _unmarshal_uint64    (pData, pDataLen, &dest->compressed_len);
    _unmarshal_uint64    (pData, pDataLen, &dest->block_len);

    /* check structure */
    if (dest->version != 2)
        return FALSE;

    return TRUE;
}