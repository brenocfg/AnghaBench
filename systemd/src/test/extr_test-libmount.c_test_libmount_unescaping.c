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
 int /*<<< orphan*/  test_libmount_unescaping_one (char*,char*,int,char*,char*) ; 

__attribute__((used)) static void test_libmount_unescaping(void) {
        test_libmount_unescaping_one(
                        "escaped space + utf8",
                        "729 38 0:59 / /tmp/„zupa\\040zębowa” rw,relatime shared:395 - tmpfs die\\040Brühe rw,seclabel",
                        false,
                        "die Brühe",
                        "/tmp/„zupa zębowa”"
        );

        test_libmount_unescaping_one(
                        "escaped newline",
                        "729 38 0:59 / /tmp/x\\012y rw,relatime shared:395 - tmpfs newline rw,seclabel",
                        false,
                        "newline",
                        "/tmp/x\ny"
        );

        /* The result of "mount -t tmpfs '' /tmp/emptysource".
         * This will fail with libmount <= v2.33.
         * See https://github.com/karelzak/util-linux/commit/18a52a5094.
         */
        test_libmount_unescaping_one(
                        "empty source",
                        "760 38 0:60 / /tmp/emptysource rw,relatime shared:410 - tmpfs  rw,seclabel",
                        true,
                        "",
                        "/tmp/emptysource"
        );

        /* The kernel leaves \r as is.
         * Also see https://github.com/karelzak/util-linux/issues/780.
         */
        test_libmount_unescaping_one(
                        "foo\\rbar",
                        "790 38 0:61 / /tmp/foo\rbar rw,relatime shared:425 - tmpfs tmpfs rw,seclabel",
                        true,
                        "tmpfs",
                        "/tmp/foo\rbar"
        );
}