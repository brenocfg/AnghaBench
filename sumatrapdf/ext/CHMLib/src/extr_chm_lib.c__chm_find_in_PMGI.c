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
struct chmPmgiHeader {int /*<<< orphan*/ * free_space; } ;
typedef  int UInt64 ;
typedef  int UInt32 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int Int32 ;

/* Variables and functions */
 int CHM_MAX_PATHLEN ; 
 unsigned int _CHM_PMGI_LEN ; 
 int /*<<< orphan*/  _chm_parse_UTF8 (int /*<<< orphan*/ **,int,char*) ; 
 int _chm_parse_cword (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _unmarshal_pmgi_header (int /*<<< orphan*/ **,unsigned int*,int,struct chmPmgiHeader*) ; 
 scalar_t__ strcasecmp (char*,char const*) ; 

__attribute__((used)) static Int32 _chm_find_in_PMGI(UChar *page_buf,
                        UInt32 block_len,
                        const char *objPath)
{
    /* XXX: modify this to do a binary search using the nice index structure
     *      that is provided for us
     */
    struct chmPmgiHeader header;
    unsigned int hremain;
    int page=-1;
    UChar *end;
    UChar *cur;
    UInt64 strLen;
    char buffer[CHM_MAX_PATHLEN+1];

    /* figure out where to start and end */
    cur = page_buf;
    hremain = _CHM_PMGI_LEN;
    if (! _unmarshal_pmgi_header(&cur, &hremain, block_len, &header))
        return -1;
    end = page_buf + block_len - (header.free_space);

    /* now, scan progressively */
    while (cur < end)
    {
        /* grab the name */
        strLen = _chm_parse_cword(&cur);
        if (strLen > CHM_MAX_PATHLEN)
            return -1;
        if (! _chm_parse_UTF8(&cur, strLen, buffer))
            return -1;

        /* check if it is the right name */
        if (strcasecmp(buffer, objPath) > 0)
            return page;

        /* load next value for path */
        page = (int)_chm_parse_cword(&cur);
    }

    return page;
}