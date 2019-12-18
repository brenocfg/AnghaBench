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
 char* ansi_highlight_red () ; 
 int /*<<< orphan*/  ansi_normal () ; 
 int boot_entry_file_check (char const*,char const*) ; 
 int errno ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 char* strempty (char const*) ; 

__attribute__((used)) static void boot_entry_file_list(const char *field, const char *root, const char *p, int *ret_status) {
        int status = boot_entry_file_check(root, p);

        printf("%13s%s ", strempty(field), field ? ":" : " ");
        if (status < 0) {
                errno = -status;
                printf("%s%s%s (%m)\n", ansi_highlight_red(), p, ansi_normal());
        } else
                printf("%s\n", p);

        if (*ret_status == 0 && status < 0)
                *ret_status = status;
}