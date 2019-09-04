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
typedef  int /*<<< orphan*/  pcre_extra ;
typedef  int /*<<< orphan*/  pcre ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int,char const*) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int /*<<< orphan*/ * pcre_compile (char*,int const,char const**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcre_study (int /*<<< orphan*/ *,int const,char const**) ; 

void compile_study(pcre **re, pcre_extra **re_extra, char *q, const int pcre_opts, const int study_opts) {
    const char *pcre_err = NULL;
    int pcre_err_offset = 0;

    *re = pcre_compile(q, pcre_opts, &pcre_err, &pcre_err_offset, NULL);
    if (*re == NULL) {
        die("Bad regex! pcre_compile() failed at position %i: %s\nIf you meant to search for a literal string, run ag with -Q",
            pcre_err_offset,
            pcre_err);
    }
    *re_extra = pcre_study(*re, study_opts, &pcre_err);
    if (*re_extra == NULL) {
        log_debug("pcre_study returned nothing useful. Error: %s", pcre_err);
    }
}