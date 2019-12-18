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
struct chmLzxcResetTable {int version; int block_count; int unknown; int table_offset; scalar_t__ uncompressed_len; scalar_t__ compressed_len; scalar_t__ block_len; } ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 unsigned int _CHM_LZXC_RESETTABLE_V1_LEN ; 
 int /*<<< orphan*/  _unmarshal_uint32 (unsigned char**,unsigned int*,int*) ; 
 int /*<<< orphan*/  _unmarshal_uint64 (unsigned char**,unsigned int*,scalar_t__*) ; 

__attribute__((used)) static int _unmarshal_lzxc_reset_table(unsigned char **pData,
                                       unsigned int *pDataLen,
                                       struct chmLzxcResetTable *dest)
{
    /* we only know how to deal with a 0x28 byte structures */
    if (*pDataLen != _CHM_LZXC_RESETTABLE_V1_LEN)
        return 0;

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
        return 0;
    /* SumatraPDF: sanity check (huge values are usually due to broken files) */
    if (dest->uncompressed_len > UINT_MAX || dest->compressed_len > UINT_MAX)
        return 0;
    if (dest->block_len == 0 || dest->block_len > UINT_MAX)
        return 0;

    return 1;
}