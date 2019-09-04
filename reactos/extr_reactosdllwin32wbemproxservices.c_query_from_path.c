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
struct path {int class_len; int filter_len; int /*<<< orphan*/  class; int /*<<< orphan*/  filter; } ;
typedef  char WCHAR ;
typedef  int UINT ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcatW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 

__attribute__((used)) static WCHAR *query_from_path( const struct path *path )
{
    static const WCHAR selectW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','%','s',' ',
         'W','H','E','R','E',' ','%','s',0};
    static const WCHAR select_allW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',0};
    WCHAR *query;
    UINT len;

    if (path->filter)
    {
        len = path->class_len + path->filter_len + ARRAY_SIZE(selectW);
        if (!(query = heap_alloc( len * sizeof(WCHAR) ))) return NULL;
        sprintfW( query, selectW, path->class, path->filter );
    }
    else
    {
        len = path->class_len + ARRAY_SIZE(select_allW);
        if (!(query = heap_alloc( len * sizeof(WCHAR) ))) return NULL;
        strcpyW( query, select_allW );
        strcatW( query, path->class );
    }
    return query;
}