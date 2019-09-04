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
struct string {char* data; int len; } ;
struct parser {int dummy; } ;
typedef  char WCHAR ;

/* Variables and functions */
 char* alloc_mem (struct parser*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static WCHAR *get_string( struct parser *parser, const struct string *str )
{
    const WCHAR *p = str->data;
    int len = str->len;
    WCHAR *ret;

    if ((p[0] == '\"' && p[len - 1] != '\"') ||
        (p[0] == '\'' && p[len - 1] != '\'')) return NULL;
    if ((p[0] == '\"' && p[len - 1] == '\"') ||
        (p[0] == '\'' && p[len - 1] == '\''))
    {
        p++;
        len -= 2;
    }
    if (!(ret = alloc_mem( parser, (len + 1) * sizeof(WCHAR) ))) return NULL;
    memcpy( ret, p, len * sizeof(WCHAR) );
    ret[len] = 0;
    return ret;
}