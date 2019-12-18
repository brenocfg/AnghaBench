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
struct TYPE_4__ {int (* mblen ) (TYPE_1__*,int /*<<< orphan*/  const*,int) ;int /*<<< orphan*/  codepage; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ csconv_t ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ ConvertINetMultiByteToUnicode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  EILSEQ ; 
 scalar_t__ S_OK ; 
 int seterror (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
mlang_mbtowc(csconv_t *cv, const uchar *buf, int bufsize, ushort *wbuf, int *wbufsize)
{
    int len;
    int insize;
    HRESULT hr;

    len = cv->mblen(cv, buf, bufsize);
    if (len == -1)
        return -1;
    insize = len;
    hr = ConvertINetMultiByteToUnicode(&cv->mode, cv->codepage,
            (const char *)buf, &insize, (wchar_t *)wbuf, wbufsize);
    if (hr != S_OK || insize != len)
        return seterror(EILSEQ);
    return len;
}