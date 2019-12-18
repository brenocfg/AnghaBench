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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char const*) ; 
 char* g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_printf (int /*<<< orphan*/ *,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

char *
gen_conflict_path (const char *origin_path,
                   const char *modifier,
                   gint64 mtime)
{
    char time_buf[64];
    time_t t = (time_t)mtime;
    char *copy = g_strdup (origin_path);
    GString *conflict_path = g_string_new (NULL);
    char *dot, *ext;

    strftime(time_buf, 64, "%Y-%m-%d-%H-%M-%S", localtime(&t));

    dot = strrchr (copy, '.');

    if (dot != NULL) {
        *dot = '\0';
        ext = dot + 1;
        if (modifier)
            g_string_printf (conflict_path, "%s (SFConflict %s %s).%s",
                             copy, modifier, time_buf, ext);
        else
            g_string_printf (conflict_path, "%s (SFConflict %s).%s",
                             copy, time_buf, ext);
    } else {
        if (modifier)
            g_string_printf (conflict_path, "%s (SFConflict %s %s)",
                             copy, modifier, time_buf);
        else
            g_string_printf (conflict_path, "%s (SFConflict %s)",
                             copy, time_buf);
    }

    g_free (copy);
    return g_string_free (conflict_path, FALSE);
}