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
struct attr {scalar_t__* value; scalar_t__* name; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  free_attr (struct attr*) ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (struct attr*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 

__attribute__((used)) static struct attr *parse_attr( const WCHAR *str, int *used )
{
    const WCHAR *p = str, *q;
    struct attr *attr;
    int len;

    while (*p == ' ') p++;
    q = p;
    while (*q && *q != ' ' && *q != '=' && *q != ';') q++;
    len = q - p;
    if (!len) return NULL;

    if (!(attr = heap_alloc( sizeof(struct attr) ))) return NULL;
    if (!(attr->name = heap_alloc( (len + 1) * sizeof(WCHAR) )))
    {
        heap_free( attr );
        return NULL;
    }
    memcpy( attr->name, p, len * sizeof(WCHAR) );
    attr->name[len] = 0;
    attr->value = NULL;

    p = q;
    while (*p == ' ') p++;
    if (*p++ == '=')
    {
        while (*p == ' ') p++;
        q = p;
        while (*q && *q != ';') q++;
        len = q - p;
        while (len && p[len - 1] == ' ') len--;

        if (!(attr->value = heap_alloc( (len + 1) * sizeof(WCHAR) )))
        {
            free_attr( attr );
            return NULL;
        }
        memcpy( attr->value, p, len * sizeof(WCHAR) );
        attr->value[len] = 0;
    }

    while (*q == ' ') q++;
    if (*q == ';') q++;
    *used = q - str;

    return attr;
}