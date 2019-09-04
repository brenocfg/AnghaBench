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
struct TYPE_4__ {int (* mblen ) (TYPE_1__*,int /*<<< orphan*/  const*,int) ;int /*<<< orphan*/  codepage; } ;
typedef  TYPE_1__ csconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbtowc_flags (int /*<<< orphan*/ ) ; 
 int seterror (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
kernel_mbtowc(csconv_t *cv, const uchar *buf, int bufsize, ushort *wbuf, int *wbufsize)
{
    int len;

    len = cv->mblen(cv, buf, bufsize);
    if (len == -1)
        return -1;
    *wbufsize = MultiByteToWideChar(cv->codepage, mbtowc_flags (cv->codepage),
            (const char *)buf, len, (wchar_t *)wbuf, *wbufsize);
    if (*wbufsize == 0)
        return seterror(EILSEQ);
    return len;
}