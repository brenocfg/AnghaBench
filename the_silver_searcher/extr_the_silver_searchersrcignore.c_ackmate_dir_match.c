#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * ackmate_dir_filter; } ;

/* Variables and functions */
 TYPE_1__ opts ; 
 int pcre_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int ackmate_dir_match(const char *dir_name) {
    if (opts.ackmate_dir_filter == NULL) {
        return 0;
    }
    /* we just care about the match, not where the matches are */
    return pcre_exec(opts.ackmate_dir_filter, NULL, dir_name, strlen(dir_name), 0, 0, NULL, 0);
}