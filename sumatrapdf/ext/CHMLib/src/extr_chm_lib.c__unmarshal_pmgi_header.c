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
struct chmPmgiHeader {unsigned int free_space; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 unsigned int _CHM_PMGI_LEN ; 
 int /*<<< orphan*/  _chm_pmgi_marker ; 
 int /*<<< orphan*/  _unmarshal_char_array (unsigned char**,unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _unmarshal_uint32 (unsigned char**,unsigned int*,unsigned int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _unmarshal_pmgi_header(unsigned char **pData,
                                  unsigned int *pDataLen,
                                  unsigned int blockLen,
                                  struct chmPmgiHeader *dest)
{
    /* we only know how to deal with a 0x8 byte structures */
    if (*pDataLen != _CHM_PMGI_LEN)
        return 0;
    /* SumatraPDF: sanity check */
    if (blockLen < _CHM_PMGI_LEN)
        return 0;

    /* unmarshal fields */
    _unmarshal_char_array(pData, pDataLen,  dest->signature, 4);
    _unmarshal_uint32    (pData, pDataLen, &dest->free_space);

    /* check structure */
    if (memcmp(dest->signature, _chm_pmgi_marker, 4) != 0)
        return 0;
    /* SumatraPDF: sanity check */
    if (dest->free_space > blockLen - _CHM_PMGI_LEN)
        return 0;

    return 1;
}