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
struct chmItsfHeader {unsigned int version; unsigned int header_len; unsigned int unknown_000c; scalar_t__ unknown_offset; scalar_t__ unknown_len; scalar_t__ dir_offset; scalar_t__ dir_len; scalar_t__ data_offset; int /*<<< orphan*/  signature; int /*<<< orphan*/  stream_uuid; int /*<<< orphan*/  dir_uuid; int /*<<< orphan*/  lang_id; int /*<<< orphan*/  last_modified; } ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 unsigned int _CHM_ITSF_V2_LEN ; 
 unsigned int _CHM_ITSF_V3_LEN ; 
 int /*<<< orphan*/  _unmarshal_char_array (unsigned char**,unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _unmarshal_int32 (unsigned char**,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  _unmarshal_uint32 (unsigned char**,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _unmarshal_uint64 (unsigned char**,unsigned int*,scalar_t__*) ; 
 int /*<<< orphan*/  _unmarshal_uuid (unsigned char**,unsigned int*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int _unmarshal_itsf_header(unsigned char **pData,
                                  unsigned int *pDataLen,
                                  struct chmItsfHeader *dest)
{
    /* we only know how to deal with the 0x58 and 0x60 byte structures */
    if (*pDataLen != _CHM_ITSF_V2_LEN  &&  *pDataLen != _CHM_ITSF_V3_LEN)
        return 0;

    /* unmarshal common fields */
    _unmarshal_char_array(pData, pDataLen,  dest->signature, 4);
    _unmarshal_int32     (pData, pDataLen, &dest->version);
    _unmarshal_int32     (pData, pDataLen, &dest->header_len);
    _unmarshal_int32     (pData, pDataLen, &dest->unknown_000c);
    _unmarshal_uint32    (pData, pDataLen, &dest->last_modified);
    _unmarshal_uint32    (pData, pDataLen, &dest->lang_id);
    _unmarshal_uuid      (pData, pDataLen,  dest->dir_uuid);
    _unmarshal_uuid      (pData, pDataLen,  dest->stream_uuid);
    _unmarshal_uint64    (pData, pDataLen, &dest->unknown_offset);
    _unmarshal_uint64    (pData, pDataLen, &dest->unknown_len);
    _unmarshal_uint64    (pData, pDataLen, &dest->dir_offset);
    _unmarshal_uint64    (pData, pDataLen, &dest->dir_len);

    /* error check the data */
    /* XXX: should also check UUIDs, probably, though with a version 3 file,
     * current MS tools do not seem to use them.
     */
    if (memcmp(dest->signature, "ITSF", 4) != 0)
        return 0;
    if (dest->version == 2)
    {
        if (dest->header_len < _CHM_ITSF_V2_LEN)
            return 0;
    }
    else if (dest->version == 3)
    {
        if (dest->header_len < _CHM_ITSF_V3_LEN)
            return 0;
    }
    else
        return 0;

    /* now, if we have a V3 structure, unmarshal the rest.
     * otherwise, compute it
     */
    if (dest->version == 3)
    {
        if (*pDataLen != 0)
            _unmarshal_uint64(pData, pDataLen, &dest->data_offset);
        else
            return 0;
    }
    else
        dest->data_offset = dest->dir_offset + dest->dir_len;

    /* SumatraPDF: sanity check (huge values are usually due to broken files) */
    if (dest->dir_offset > UINT_MAX || dest->dir_len > UINT_MAX)
        return 0;

    return 1;
}