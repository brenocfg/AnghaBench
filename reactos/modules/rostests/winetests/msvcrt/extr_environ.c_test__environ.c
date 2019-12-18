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

/* Variables and functions */
 int /*<<< orphan*/  __getmainargs (int*,char***,char***,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char*** p__p__environ () ; 
 char*** p_environ ; 
 int /*<<< orphan*/  p_get_environ (char***) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__environ(void)
{
    int argc;
    char **argv, **envp = NULL;
    int i, mode = 0;

    ok( p_environ != NULL, "Expected the pointer to _environ to be non-NULL\n" );
    if (p_environ)
        ok( *p_environ != NULL, "Expected _environ to be initialized on startup\n" );

    if (!p_environ || !*p_environ)
    {
        skip( "_environ pointers are not valid\n" );
        return;
    }

    /* Examine the returned pointer from __p__environ(), if available. */
    if (p__p__environ)
    {
        ok( *p__p__environ() == *p_environ,
            "Expected _environ pointers to be identical\n" );
    }
    else
        skip( "__p__environ() is not available\n" );

    if (p_get_environ)
    {
        char **retptr;
        p_get_environ(&retptr);
        ok( retptr == *p_environ,
            "Expected _environ pointers to be identical\n" );
    }
    else
        win_skip( "_get_environ() is not available\n" );

    /* Note that msvcrt from Windows versions older than Vista
     * expects the mode pointer parameter to be valid.*/
    __getmainargs(&argc, &argv, &envp, 0, &mode);

    ok( envp != NULL, "Expected initial environment block pointer to be non-NULL\n" );
    if (!envp)
    {
        skip( "Initial environment block pointer is not valid\n" );
        return;
    }

    for (i = 0; ; i++)
    {
        if ((*p_environ)[i])
        {
            ok( envp[i] != NULL, "Expected environment block pointer element to be non-NULL\n" );
            ok( !strcmp((*p_environ)[i], envp[i]),
                "Expected _environ and environment block pointer strings (%s vs. %s) to match\n",
                (*p_environ)[i], envp[i] );
        }
        else
        {
            ok( !envp[i], "Expected environment block pointer element to be NULL, got %p\n", envp[i] );
            break;
        }
    }
}