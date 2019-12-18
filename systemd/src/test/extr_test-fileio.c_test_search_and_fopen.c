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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int mkostemp_safe (char*) ; 
 int search_and_fopen (char*,char*,char*,char const**,int /*<<< orphan*/ **) ; 
 int unlink (char*) ; 

__attribute__((used)) static void test_search_and_fopen(void) {
        const char *dirs[] = {"/tmp/foo/bar", "/tmp", NULL};

        char name[] = "/tmp/test-search_and_fopen.XXXXXX";
        int fd, r;
        FILE *f;

        fd = mkostemp_safe(name);
        assert_se(fd >= 0);
        close(fd);

        r = search_and_fopen(basename(name), "r", NULL, dirs, &f);
        assert_se(r >= 0);
        fclose(f);

        r = search_and_fopen(name, "r", NULL, dirs, &f);
        assert_se(r >= 0);
        fclose(f);

        r = search_and_fopen(basename(name), "r", "/", dirs, &f);
        assert_se(r >= 0);
        fclose(f);

        r = search_and_fopen("/a/file/which/does/not/exist/i/guess", "r", NULL, dirs, &f);
        assert_se(r < 0);
        r = search_and_fopen("afilewhichdoesnotexistiguess", "r", NULL, dirs, &f);
        assert_se(r < 0);

        r = unlink(name);
        assert_se(r == 0);

        r = search_and_fopen(basename(name), "r", NULL, dirs, &f);
        assert_se(r < 0);
}