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
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  __getmainargs (int*,char***,char***,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  __wgetmainargs (int*,char***,char***,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ _putenv (char*) ; 
 scalar_t__ _wputenv (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char*** p__p__wenviron () ; 
 int /*<<< orphan*/  p_get_wenviron (char***) ; 
 char*** p_wenviron ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 
 int /*<<< orphan*/  winetest_strcmpW (char*,char*) ; 

__attribute__((used)) static void test__wenviron(void)
{
    static const WCHAR cat_eq_dogW[] = {'c','a','t','=','d','o','g',0};
    static const WCHAR cat_eqW[] = {'c','a','t','=',0};

    int argc;
    char **argv, **envp = NULL;
    WCHAR **wargv, **wenvp = NULL;
    int i, mode = 0;

    ok( p_wenviron != NULL, "Expected the pointer to _wenviron to be non-NULL\n" );
    if (p_wenviron)
        ok( *p_wenviron == NULL, "Expected _wenviron to be NULL, got %p\n", *p_wenviron );
    else
    {
        win_skip( "Pointer to _wenviron is not valid\n" );
        return;
    }

    /* Examine the returned pointer from __p__wenviron(), if available. */
    if (p__p__wenviron)
    {
        ok( *p__p__wenviron() == NULL,
            "Expected _wenviron pointers to be NULL\n" );
    }
    else
        skip( "__p__wenviron() is not available\n" );

    if (p_get_wenviron)
    {
        WCHAR **retptr;
        p_get_wenviron(&retptr);
        ok( retptr == NULL,
            "Expected _wenviron pointers to be NULL\n" );
    }
    else
        win_skip( "_get_wenviron() is not available\n" );

    /* __getmainargs doesn't initialize _wenviron. */
    __getmainargs(&argc, &argv, &envp, 0, &mode);

    ok( *p_wenviron == NULL, "Expected _wenviron to be NULL, got %p\n", *p_wenviron);
    ok( envp != NULL, "Expected initial environment block pointer to be non-NULL\n" );
    if (!envp)
    {
        skip( "Initial environment block pointer is not valid\n" );
        return;
    }

    /* Neither does calling the non-Unicode environment manipulation functions. */
    ok( _putenv("cat=dog") == 0, "failed setting cat=dog\n" );
    ok( *p_wenviron == NULL, "Expected _wenviron to be NULL, got %p\n", *p_wenviron);
    ok( _putenv("cat=") == 0, "failed deleting cat\n" );

    /* _wenviron isn't initialized until __wgetmainargs is called or
     * one of the Unicode environment manipulation functions is called. */
    ok( _wputenv(cat_eq_dogW) == 0, "failed setting cat=dog\n" );
    ok( *p_wenviron != NULL, "Expected _wenviron to be non-NULL\n" );
    ok( _wputenv(cat_eqW) == 0, "failed deleting cat\n" );

    __wgetmainargs(&argc, &wargv, &wenvp, 0, &mode);

    ok( *p_wenviron != NULL, "Expected _wenviron to be non-NULL\n" );
    ok( wenvp != NULL, "Expected initial environment block pointer to be non-NULL\n" );
    if (!wenvp)
    {
        skip( "Initial environment block pointer is not valid\n" );
        return;
    }

    /* Examine the returned pointer from __p__wenviron(),
     * if available, after _wenviron is initialized. */
    if (p__p__wenviron)
    {
        ok( *p__p__wenviron() == *p_wenviron,
            "Expected _wenviron pointers to be identical\n" );
    }

    if (p_get_wenviron)
    {
        WCHAR **retptr;
        p_get_wenviron(&retptr);
        ok( retptr == *p_wenviron,
            "Expected _wenviron pointers to be identical\n" );
    }

    for (i = 0; ; i++)
    {
        if ((*p_wenviron)[i])
        {
            ok( wenvp[i] != NULL, "Expected environment block pointer element to be non-NULL\n" );
            ok( !winetest_strcmpW((*p_wenviron)[i], wenvp[i]),
                "Expected _wenviron and environment block pointer strings (%s vs. %s) to match\n",
                wine_dbgstr_w((*p_wenviron)[i]), wine_dbgstr_w(wenvp[i]) );
        }
        else
        {
            ok( !wenvp[i], "Expected environment block pointer element to be NULL, got %p\n", wenvp[i] );
            break;
        }
    }
}