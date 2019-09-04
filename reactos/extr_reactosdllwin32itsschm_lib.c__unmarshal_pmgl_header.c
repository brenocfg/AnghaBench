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
struct chmPmglHeader {int /*<<< orphan*/  signature; int /*<<< orphan*/  block_next; int /*<<< orphan*/  block_prev; int /*<<< orphan*/  unknown_0008; int /*<<< orphan*/  free_space; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int _CHM_PMGL_LEN ; 
 int /*<<< orphan*/  _chm_pmgl_marker ; 
 int /*<<< orphan*/  _unmarshal_char_array (unsigned char**,unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _unmarshal_int32 (unsigned char**,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _unmarshal_uint32 (unsigned char**,unsigned int*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL _unmarshal_pmgl_header(unsigned char **pData,
                                   unsigned int *pDataLen,
                                   struct chmPmglHeader *dest)
{
    /* we only know how to deal with a 0x14 byte structures */
    if (*pDataLen != _CHM_PMGL_LEN)
        return FALSE;

    /* unmarshal fields */
    _unmarshal_char_array(pData, pDataLen,  dest->signature, 4);
    _unmarshal_uint32    (pData, pDataLen, &dest->free_space);
    _unmarshal_uint32    (pData, pDataLen, &dest->unknown_0008);
    _unmarshal_int32     (pData, pDataLen, &dest->block_prev);
    _unmarshal_int32     (pData, pDataLen, &dest->block_next);

    /* check structure */
    if (memcmp(dest->signature, _chm_pmgl_marker, 4) != 0)
        return FALSE;

    return TRUE;
}