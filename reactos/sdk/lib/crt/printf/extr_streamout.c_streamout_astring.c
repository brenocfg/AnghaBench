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
struct TYPE_4__ {int _flag; int /*<<< orphan*/ * _base; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int _IOSTRG ; 
 int mbtowc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ streamout_char (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int
streamout_astring(FILE *stream, const char *string, size_t count)
{
    TCHAR chr;
    int written = 0;

#if !defined(_USER32_WSPRINTF)
     if ((stream->_flag & _IOSTRG) && (stream->_base == NULL))
        return count;
#endif

    while (count--)
    {
#ifdef _UNICODE
        int len;
        if ((len = mbtowc(&chr, string, MB_CUR_MAX)) < 1) break;
        string += len;
#else
        chr = *string++;
#endif
        if (streamout_char(stream, chr) == 0) return -1;
        written++;
    }

    return written;
}