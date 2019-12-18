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
typedef  int wchar_t ;
struct TYPE_4__ {int _flag; int /*<<< orphan*/ * _base; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 int _IOSTRG ; 
 scalar_t__ streamout_char (TYPE_1__*,int) ; 
 int wctomb (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int
streamout_wstring(FILE *stream, const wchar_t *string, size_t count)
{
    wchar_t chr;
    int written = 0;

#if defined(_UNICODE) && !defined(_USER32_WSPRINTF)
     if ((stream->_flag & _IOSTRG) && (stream->_base == NULL))
        return count;
#endif

    while (count--)
    {
#ifndef _UNICODE
        char mbchar[MB_CUR_MAX], *ptr = mbchar;
        int mblen;

        mblen = wctomb(mbchar, *string++);
        if (mblen <= 0) return written;

        while (chr = *ptr++, mblen--)
#else
        chr = *string++;
#endif
        {
            if (streamout_char(stream, chr) == 0) return -1;
            written++;
        }
    }

    return written;
}