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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int min (int,size_t) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static size_t format_string( WCHAR *buffer, size_t len, const char *format, const WCHAR *str, int str_len )
{
    size_t count = 0;
    int i, left_align = 0, width = 0, max = 0;

    assert( *format == '%' );
    format++; /* skip '%' */

    while (*format == '0' || *format == '+' || *format == '-' || *format == ' ' || *format == '#')
    {
        if (*format == '-') left_align = 1;
        format++;
    }

    while (isdigit(*format)) width = width * 10 + *format++ - '0';

    if (str_len == -1) str_len = strlenW( str );
    if (*format == '.')
    {
        format++;
        while (isdigit(*format)) max = max * 10 + *format++ - '0';
        if (max > str_len) max = str_len;
    }
    else max = str_len;

    if (*format == 'h' || *format == 'l') format++;

    assert( *format == 's' );

    if (!left_align && width > max)
    {
        for (i = 0; i < width - max; i++)
        {
            if (count++ < len)
                *buffer++ = ' ';
        }
    }

    if (count < len)
        memcpy( buffer, str, min( max, len - count ) * sizeof(WCHAR) );
    count += max;
    buffer += max;

    if (left_align && width > max)
    {
        for (i = 0; i < width - max; i++)
        {
            if (count++ < len)
                *buffer++ = ' ';
        }
    }
    return count;
}