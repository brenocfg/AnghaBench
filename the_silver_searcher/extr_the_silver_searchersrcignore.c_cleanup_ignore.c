#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* abs_path; int /*<<< orphan*/  slash_regexes_len; int /*<<< orphan*/  slash_regexes; int /*<<< orphan*/  invert_regexes_len; int /*<<< orphan*/  invert_regexes; int /*<<< orphan*/  regexes_len; int /*<<< orphan*/  regexes; int /*<<< orphan*/  slash_names_len; int /*<<< orphan*/  slash_names; int /*<<< orphan*/  names_len; int /*<<< orphan*/  names; int /*<<< orphan*/  extensions_len; int /*<<< orphan*/  extensions; } ;
typedef  TYPE_1__ ignores ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cleanup_ignore(ignores *ig) {
    if (ig == NULL) {
        return;
    }
    free_strings(ig->extensions, ig->extensions_len);
    free_strings(ig->names, ig->names_len);
    free_strings(ig->slash_names, ig->slash_names_len);
    free_strings(ig->regexes, ig->regexes_len);
    free_strings(ig->invert_regexes, ig->invert_regexes_len);
    free_strings(ig->slash_regexes, ig->slash_regexes_len);
    if (ig->abs_path) {
        free(ig->abs_path);
    }
    free(ig);
}