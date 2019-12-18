#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort ;
typedef  int uint ;
typedef  int uchar ;
struct TYPE_3__ {int codepage; int mode; int flags; } ;
typedef  TYPE_1__ csconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int FLAG_USE_BOM ; 
 int UNICODE_MODE_BOM_DONE ; 
 int UNICODE_MODE_SWAPPED ; 
 int seterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucs4_to_utf16 (int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
utf32_mbtowc(csconv_t *cv, const uchar *buf, int bufsize, ushort *wbuf, int *wbufsize)
{
    int codepage = cv->codepage;
    uint wc;

    /* swap endian: 12000 <-> 12001 */
    if (cv->mode & UNICODE_MODE_SWAPPED)
        codepage ^= 1;

    if (bufsize < 4)
        return seterror(EINVAL);
    if (codepage == 12000) /* little endian */
        wc = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];
    else if (codepage == 12001) /* big endian */
        wc = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];

    if ((cv->flags & FLAG_USE_BOM) && !(cv->mode & UNICODE_MODE_BOM_DONE))
    {
        cv->mode |= UNICODE_MODE_BOM_DONE;
        if (wc == 0xFFFE0000)
        {
            cv->mode |= UNICODE_MODE_SWAPPED;
            *wbufsize = 0;
            return 4;
        }
        else if (wc == 0x0000FEFF)
        {
            *wbufsize = 0;
            return 4;
        }
    }

    if ((0xD800 <= wc && wc <= 0xDFFF) || 0x10FFFF < wc)
        return seterror(EILSEQ);
    ucs4_to_utf16(wc, wbuf, wbufsize);
    return 4;
}