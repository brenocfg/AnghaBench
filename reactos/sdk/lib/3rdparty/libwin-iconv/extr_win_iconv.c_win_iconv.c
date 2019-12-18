#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort ;
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_8__ {int (* flush ) (TYPE_3__*,int /*<<< orphan*/ *,size_t) ;int flags; int (* wctomb ) (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ;void* mode; TYPE_2__* compat; } ;
struct TYPE_9__ {int (* mbtowc ) (TYPE_4__*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int*) ;void* mode; TYPE_2__* compat; } ;
struct TYPE_6__ {TYPE_3__ to; TYPE_4__ from; } ;
typedef  TYPE_1__ rec_iconv_t ;
typedef  scalar_t__ iconv_t ;
struct TYPE_7__ {scalar_t__ in; int flag; scalar_t__ out; } ;
typedef  TYPE_2__ compat_t ;
typedef  void* DWORD ;

/* Variables and functions */
 int COMPAT_IN ; 
 int COMPAT_OUT ; 
 scalar_t__ E2BIG ; 
 int FLAG_IGNORE ; 
 int MB_CHAR_MAX ; 
 scalar_t__ errno ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ *,size_t) ; 
 int stub2 (TYPE_4__*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int*) ; 
 int stub3 (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ucs4_to_utf16 (scalar_t__,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ utf16_to_ucs4 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
win_iconv(iconv_t _cd, const char **inbuf, size_t *inbytesleft, char **outbuf, size_t *outbytesleft)
{
    rec_iconv_t *cd = (rec_iconv_t *)_cd;
    ushort wbuf[MB_CHAR_MAX]; /* enough room for one character */
    int insize;
    int outsize;
    int wsize;
    DWORD frommode;
    DWORD tomode;
    uint wc;
    compat_t *cp;
    int i;

    if (inbuf == NULL || *inbuf == NULL)
    {
        if (outbuf != NULL && *outbuf != NULL && cd->to.flush != NULL)
        {
            tomode = cd->to.mode;
            outsize = cd->to.flush(&cd->to, (uchar *)*outbuf, *outbytesleft);
            if (outsize == -1)
            {
                if ((cd->to.flags & FLAG_IGNORE) && errno != E2BIG)
                {
                    outsize = 0;
                }
                else
                {
                    cd->to.mode = tomode;
                    return (size_t)(-1);
                }
            }
            *outbuf += outsize;
            *outbytesleft -= outsize;
        }
        cd->from.mode = 0;
        cd->to.mode = 0;
        return 0;
    }

    while (*inbytesleft != 0)
    {
        frommode = cd->from.mode;
        tomode = cd->to.mode;
        wsize = MB_CHAR_MAX;

        insize = cd->from.mbtowc(&cd->from, (const uchar *)*inbuf, *inbytesleft, wbuf, &wsize);
        if (insize == -1)
        {
            if (cd->to.flags & FLAG_IGNORE)
            {
                cd->from.mode = frommode;
                insize = 1;
                wsize = 0;
            }
            else
            {
                cd->from.mode = frommode;
                return (size_t)(-1);
            }
        }

        if (wsize == 0)
        {
            *inbuf += insize;
            *inbytesleft -= insize;
            continue;
        }

        if (cd->from.compat != NULL)
        {
            wc = utf16_to_ucs4(wbuf);
            cp = cd->from.compat;
            for (i = 0; cp[i].in != 0; ++i)
            {
                if ((cp[i].flag & COMPAT_IN) && cp[i].out == wc)
                {
                    ucs4_to_utf16(cp[i].in, wbuf, &wsize);
                    break;
                }
            }
        }

        if (cd->to.compat != NULL)
        {
            wc = utf16_to_ucs4(wbuf);
            cp = cd->to.compat;
            for (i = 0; cp[i].in != 0; ++i)
            {
                if ((cp[i].flag & COMPAT_OUT) && cp[i].in == wc)
                {
                    ucs4_to_utf16(cp[i].out, wbuf, &wsize);
                    break;
                }
            }
        }

        outsize = cd->to.wctomb(&cd->to, wbuf, wsize, (uchar *)*outbuf, *outbytesleft);
        if (outsize == -1)
        {
            if ((cd->to.flags & FLAG_IGNORE) && errno != E2BIG)
            {
                cd->to.mode = tomode;
                outsize = 0;
            }
            else
            {
                cd->from.mode = frommode;
                cd->to.mode = tomode;
                return (size_t)(-1);
            }
        }

        *inbuf += insize;
        *outbuf += outsize;
        *inbytesleft -= insize;
        *outbytesleft -= outsize;
    }

    return 0;
}