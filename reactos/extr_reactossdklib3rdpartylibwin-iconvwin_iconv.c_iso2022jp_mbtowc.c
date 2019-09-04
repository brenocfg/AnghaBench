#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int const ushort ;
typedef  int uchar ;
struct TYPE_5__ {int const* esc; int esc_len; int cs; int len; } ;
typedef  TYPE_1__ iso2022_esc_t ;
struct TYPE_6__ {scalar_t__ mode; int codepage; } ;
typedef  TYPE_2__ csconv_t ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ConvertINetMultiByteToUnicode (int /*<<< orphan*/ *,int,char const*,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int ISO2022JP_CS_ASCII ; 
 size_t ISO2022JP_CS_JISX0201_KANA ; 
 scalar_t__ ISO2022_MODE (int,int) ; 
 int ISO2022_MODE_CS (scalar_t__) ; 
 int ISO2022_MODE_SHIFT (scalar_t__) ; 
 int ISO2022_SI ; 
 int ISO2022_SO ; 
 int MB_CHAR_MAX ; 
 scalar_t__ S_OK ; 
 int const* iso2022_SI_seq ; 
 int const* iso2022_SO_seq ; 
 TYPE_1__* iso2022jp_esc ; 
 int /*<<< orphan*/  memcpy (char*,int const*,int) ; 
 int seterror (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int const*,int) ; 

__attribute__((used)) static int
iso2022jp_mbtowc(csconv_t *cv, const uchar *buf, int bufsize, ushort *wbuf, int *wbufsize)
{
    iso2022_esc_t *iesc = iso2022jp_esc;
    char tmp[MB_CHAR_MAX];
    int insize;
    HRESULT hr;
    DWORD dummy = 0;
    int len;
    int esc_len;
    int cs;
    int shift;
    int i;

    if (buf[0] == 0x1B)
    {
        for (i = 0; iesc[i].esc != NULL; ++i)
        {
            esc_len = iesc[i].esc_len;
            if (bufsize < esc_len)
            {
                if (strncmp((char *)buf, iesc[i].esc, bufsize) == 0)
                    return seterror(EINVAL);
            }
            else
            {
                if (strncmp((char *)buf, iesc[i].esc, esc_len) == 0)
                {
                    cv->mode = ISO2022_MODE(iesc[i].cs, ISO2022_SI);
                    *wbufsize = 0;
                    return esc_len;
                }
            }
        }
        /* not supported escape sequence */
        return seterror(EILSEQ);
    }
    else if (buf[0] == iso2022_SO_seq[0])
    {
        cv->mode = ISO2022_MODE(ISO2022_MODE_CS(cv->mode), ISO2022_SO);
        *wbufsize = 0;
        return 1;
    }
    else if (buf[0] == iso2022_SI_seq[0])
    {
        cv->mode = ISO2022_MODE(ISO2022_MODE_CS(cv->mode), ISO2022_SI);
        *wbufsize = 0;
        return 1;
    }

    cs = ISO2022_MODE_CS(cv->mode);
    shift = ISO2022_MODE_SHIFT(cv->mode);

    /* reset the mode for informal sequence */
    if (buf[0] < 0x20)
    {
        cs = ISO2022JP_CS_ASCII;
        shift = ISO2022_SI;
    }

    len = iesc[cs].len;
    if (bufsize < len)
        return seterror(EINVAL);
    for (i = 0; i < len; ++i)
        if (!(buf[i] < 0x80))
            return seterror(EILSEQ);
    esc_len = iesc[cs].esc_len;
    memcpy(tmp, iesc[cs].esc, esc_len);
    if (shift == ISO2022_SO)
    {
        memcpy(tmp + esc_len, iso2022_SO_seq, 1);
        esc_len += 1;
    }
    memcpy(tmp + esc_len, buf, len);

    if ((cv->codepage == 50220 || cv->codepage == 50221
                || cv->codepage == 50222) && shift == ISO2022_SO)
    {
        /* XXX: shift-out cannot be used for mbtowc (both kernel and
         * mlang) */
        esc_len = iesc[ISO2022JP_CS_JISX0201_KANA].esc_len;
        memcpy(tmp, iesc[ISO2022JP_CS_JISX0201_KANA].esc, esc_len);
        memcpy(tmp + esc_len, buf, len);
    }

    insize = len + esc_len;
    hr = ConvertINetMultiByteToUnicode(&dummy, cv->codepage,
            (const char *)tmp, &insize, (wchar_t *)wbuf, wbufsize);
    if (hr != S_OK || insize != len + esc_len)
        return seterror(EILSEQ);

    /* Check for conversion error.  Assuming defaultChar is 0x3F. */
    /* ascii should be converted from ascii */
    if (wbuf[0] == buf[0]
            && cv->mode != ISO2022_MODE(ISO2022JP_CS_ASCII, ISO2022_SI))
        return seterror(EILSEQ);

    /* reset the mode for informal sequence */
    if (cv->mode != ISO2022_MODE(cs, shift))
        cv->mode = ISO2022_MODE(cs, shift);

    return len;
}