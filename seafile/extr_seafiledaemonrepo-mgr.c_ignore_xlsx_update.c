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
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GPatternSpec ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ g_pattern_match_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  g_pattern_spec_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_pattern_spec_new (char*) ; 

__attribute__((used)) static gboolean
ignore_xlsx_update (const char *src_path, const char *dst_path)
{
    GPatternSpec *pattern = g_pattern_spec_new ("*.xlsx");
    int ret = FALSE;

    if (!g_pattern_match_string(pattern, src_path) &&
        g_pattern_match_string(pattern, dst_path))
        ret = TRUE;

    g_pattern_spec_free (pattern);
    return ret;
}