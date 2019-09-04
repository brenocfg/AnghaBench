#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
struct TYPE_2__ {char* (* get_temp_buffer ) (int) ;int /*<<< orphan*/  (* release_temp_buffer ) (char*,int) ;} ;

/* Variables and functions */
 int LOWORD (char const*) ; 
 TYPE_1__ funcs ; 
 int min (int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char const*) ; 
 char* stub1 (int) ; 
 char* stub2 (size_t) ; 
 int /*<<< orphan*/  stub3 (char*,int) ; 

__attribute__((used)) static const char *default_dbgstr_an( const char *str, int n )
{
    static const char hex[16] = "0123456789abcdef";
    char *dst, *res;
    size_t size;

    if (!((ULONG_PTR)str >> 16))
    {
        if (!str) return "(null)";
        res = funcs.get_temp_buffer( 6 );
        sprintf( res, "#%04x", LOWORD(str) );
        return res;
    }
    if (n == -1) n = strlen(str);
    if (n < 0) n = 0;
    size = 10 + min( 300, n * 4 );
    dst = res = funcs.get_temp_buffer( size );
    *dst++ = '"';
    while (n-- > 0 && dst <= res + size - 9)
    {
        unsigned char c = *str++;
        switch (c)
        {
        case '\n': *dst++ = '\\'; *dst++ = 'n'; break;
        case '\r': *dst++ = '\\'; *dst++ = 'r'; break;
        case '\t': *dst++ = '\\'; *dst++ = 't'; break;
        case '"':  *dst++ = '\\'; *dst++ = '"'; break;
        case '\\': *dst++ = '\\'; *dst++ = '\\'; break;
        default:
            if (c >= ' ' && c <= 126)
                *dst++ = c;
            else
            {
                *dst++ = '\\';
                *dst++ = 'x';
                *dst++ = hex[(c >> 4) & 0x0f];
                *dst++ = hex[c & 0x0f];
            }
        }
    }
    *dst++ = '"';
    if (n > 0)
    {
        *dst++ = '.';
        *dst++ = '.';
        *dst++ = '.';
    }
    *dst++ = 0;
    funcs.release_temp_buffer( res, dst - res );
    return res;
}