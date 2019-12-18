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
typedef  int ushort ;
typedef  char uchar ;
struct TYPE_5__ {char* esc; int esc_len; int cs; int len; } ;
typedef  TYPE_1__ iso2022_esc_t ;
struct TYPE_6__ {scalar_t__ mode; int /*<<< orphan*/  codepage; } ;
typedef  TYPE_2__ csconv_t ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ConvertINetUnicodeToMultiByte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int*,char*,int*) ; 
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  EILSEQ ; 
 int ISO2022JP_CS_ASCII ; 
 scalar_t__ ISO2022_MODE (int,int) ; 
 int ISO2022_MODE_SHIFT (scalar_t__) ; 
 int ISO2022_SI ; 
 int ISO2022_SO ; 
 int MB_CHAR_MAX ; 
 scalar_t__ S_OK ; 
 char* iso2022_SI_seq ; 
 char* iso2022_SO_seq ; 
 TYPE_1__* iso2022jp_esc ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int seterror (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
iso2022jp_wctomb(csconv_t *cv, ushort *wbuf, int wbufsize, uchar *buf, int bufsize)
{
    iso2022_esc_t *iesc = iso2022jp_esc;
    char tmp[MB_CHAR_MAX];
    int tmpsize = MB_CHAR_MAX;
    int insize = wbufsize;
    HRESULT hr;
    DWORD dummy = 0;
    int len;
    int esc_len;
    int cs;
    int shift;
    int i;

    /*
     * MultiByte = [escape sequence] + character + [escape sequence]
     *
     * Whether trailing escape sequence is added depends on which API is
     * used (kernel or MLang, and its version).
     */
    hr = ConvertINetUnicodeToMultiByte(&dummy, cv->codepage,
            (const wchar_t *)wbuf, &wbufsize, tmp, &tmpsize);
    if (hr != S_OK || insize != wbufsize)
        return seterror(EILSEQ);
    else if (bufsize < tmpsize)
        return seterror(E2BIG);

    if (tmpsize == 1)
    {
        cs = ISO2022JP_CS_ASCII;
        esc_len = 0;
    }
    else
    {
        for (i = 1; iesc[i].esc != NULL; ++i)
        {
            esc_len = iesc[i].esc_len;
            if (strncmp(tmp, iesc[i].esc, esc_len) == 0)
            {
                cs = iesc[i].cs;
                break;
            }
        }
        if (iesc[i].esc == NULL)
            /* not supported escape sequence */
            return seterror(EILSEQ);
    }

    shift = ISO2022_SI;
    if (tmp[esc_len] == iso2022_SO_seq[0])
    {
        shift = ISO2022_SO;
        esc_len += 1;
    }

    len = iesc[cs].len;

    /* Check for converting error.  Assuming defaultChar is 0x3F. */
    /* ascii should be converted from ascii */
    if (cs == ISO2022JP_CS_ASCII && !(wbuf[0] < 0x80))
        return seterror(EILSEQ);
    else if (tmpsize < esc_len + len)
        return seterror(EILSEQ);

    if (cv->mode == ISO2022_MODE(cs, shift))
    {
        /* remove escape sequence */
        if (esc_len != 0)
            memmove(tmp, tmp + esc_len, len);
        esc_len = 0;
    }
    else
    {
        if (cs == ISO2022JP_CS_ASCII)
        {
            esc_len = iesc[ISO2022JP_CS_ASCII].esc_len;
            memmove(tmp + esc_len, tmp, len);
            memcpy(tmp, iesc[ISO2022JP_CS_ASCII].esc, esc_len);
        }
        if (ISO2022_MODE_SHIFT(cv->mode) == ISO2022_SO)
        {
            /* shift-in before changing to other mode */
            memmove(tmp + 1, tmp, len + esc_len);
            memcpy(tmp, iso2022_SI_seq, 1);
            esc_len += 1;
        }
    }

    if (bufsize < len + esc_len)
        return seterror(E2BIG);
    memcpy(buf, tmp, len + esc_len);
    cv->mode = ISO2022_MODE(cs, shift);
    return len + esc_len;
}