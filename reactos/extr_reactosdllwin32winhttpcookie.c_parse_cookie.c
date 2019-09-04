#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* value; scalar_t__* name; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ cookie_t ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  free_cookie (TYPE_1__*) ; 
 void* heap_alloc (int) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 
 char* strchrW (char const*,char) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static cookie_t *parse_cookie( const WCHAR *string )
{
    cookie_t *cookie;
    const WCHAR *p;
    int len;

    if (!(p = strchrW( string, '=' ))) p = string + strlenW( string );
    len = p - string;
    while (len && string[len - 1] == ' ') len--;
    if (!len) return NULL;

    if (!(cookie = heap_alloc_zero( sizeof(cookie_t) ))) return NULL;
    list_init( &cookie->entry );

    if (!(cookie->name = heap_alloc( (len + 1) * sizeof(WCHAR) )))
    {
        heap_free( cookie );
        return NULL;
    }
    memcpy( cookie->name, string, len * sizeof(WCHAR) );
    cookie->name[len] = 0;

    if (*p++ == '=')
    {
        while (*p == ' ') p++;
        len = strlenW( p );
        while (len && p[len - 1] == ' ') len--;

        if (!(cookie->value = heap_alloc( (len + 1) * sizeof(WCHAR) )))
        {
            free_cookie( cookie );
            return NULL;
        }
        memcpy( cookie->value, p, len * sizeof(WCHAR) );
        cookie->value[len] = 0;
    }
    return cookie;
}