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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EBADF ; 
 int _pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _popen (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ p_set_errno ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test__popen(const char *name)
{
    FILE *pipe;
    char buf[1024];
    int ret;

    sprintf(buf, "\"%s\" misc popen", name);
    pipe = _popen(buf, "r");
    ok(pipe != NULL, "_popen failed with error: %d\n", errno);

    fgets(buf, sizeof(buf), pipe);
    ok(!strcmp(buf, "child output\n"), "buf = %s\n", buf);

    ret = _pclose(pipe);
    ok(ret == 0x37, "_pclose returned %x, expected 0x37\n", ret);

    errno = 0xdeadbeef;
    ret = _pclose((FILE*)0xdeadbeef);
    ok(ret == -1, "_pclose returned %x, expected -1\n", ret);
    if(p_set_errno)
        ok(errno == EBADF, "errno = %d\n", errno);
}