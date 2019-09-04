#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  ushort ;
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_4__ {int (* mblen ) (TYPE_1__*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  codepage; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ csconv_t ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ ConvertINetUnicodeToMultiByte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int*,char*,int*) ; 
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  EILSEQ ; 
 int MB_CHAR_MAX ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int seterror (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mlang_wctomb(csconv_t *cv, ushort *wbuf, int wbufsize, uchar *buf, int bufsize)
{
    char tmpbuf[MB_CHAR_MAX]; /* enough room for one character */
    int tmpsize = MB_CHAR_MAX;
    int insize = wbufsize;
    HRESULT hr;

    hr = ConvertINetUnicodeToMultiByte(&cv->mode, cv->codepage,
            (const wchar_t *)wbuf, &wbufsize, tmpbuf, &tmpsize);
    if (hr != S_OK || insize != wbufsize)
        return seterror(EILSEQ);
    else if (bufsize < tmpsize)
        return seterror(E2BIG);
    else if (cv->mblen(cv, (uchar *)tmpbuf, tmpsize) != tmpsize)
        return seterror(EILSEQ);
    memcpy(buf, tmpbuf, tmpsize);
    return tmpsize;
}