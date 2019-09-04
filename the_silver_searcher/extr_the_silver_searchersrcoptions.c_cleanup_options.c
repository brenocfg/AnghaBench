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
struct TYPE_2__ {scalar_t__ file_search_regex_extra; scalar_t__ file_search_regex; scalar_t__ ackmate_dir_filter_extra; scalar_t__ ackmate_dir_filter; scalar_t__ re_extra; scalar_t__ re; scalar_t__ query; scalar_t__ color_line_number; scalar_t__ color_match; scalar_t__ color_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 TYPE_1__ opts ; 
 int /*<<< orphan*/  pcre_free (scalar_t__) ; 

void cleanup_options(void) {
    free(opts.color_path);
    free(opts.color_match);
    free(opts.color_line_number);

    if (opts.query) {
        free(opts.query);
    }

    pcre_free(opts.re);
    if (opts.re_extra) {
        /* Using pcre_free_study on pcre_extra* can segfault on some versions of PCRE */
        pcre_free(opts.re_extra);
    }

    if (opts.ackmate_dir_filter) {
        pcre_free(opts.ackmate_dir_filter);
    }
    if (opts.ackmate_dir_filter_extra) {
        pcre_free(opts.ackmate_dir_filter_extra);
    }

    if (opts.file_search_regex) {
        pcre_free(opts.file_search_regex);
    }
    if (opts.file_search_regex_extra) {
        pcre_free(opts.file_search_regex_extra);
    }
}