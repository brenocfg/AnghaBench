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
 int /*<<< orphan*/  log_err (char*,char const*) ; 

__attribute__((used)) static void *decompress_zip(const void *buf, const int buf_len,
                            const char *dir_full_path, int *new_buf_len) {
    (void)buf;
    (void)buf_len;
    log_err("Zip files not yet supported: %s", dir_full_path);
    *new_buf_len = 0;
    return NULL;
}