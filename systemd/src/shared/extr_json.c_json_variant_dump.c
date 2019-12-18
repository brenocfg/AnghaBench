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
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int JsonFormatFlags ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int JSON_FORMAT_COLOR ; 
 int JSON_FORMAT_COLOR_AUTO ; 
 int JSON_FORMAT_NEWLINE ; 
 int JSON_FORMAT_PRETTY ; 
 int JSON_FORMAT_SEQ ; 
 int JSON_FORMAT_SSE ; 
 scalar_t__ colors_enabled () ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  print_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * stdout ; 

void json_variant_dump(JsonVariant *v, JsonFormatFlags flags, FILE *f, const char *prefix) {
        if (!v)
                return;

        if (!f)
                f = stdout;

        print_source(f, v, flags, false);

        if (((flags & (JSON_FORMAT_COLOR_AUTO|JSON_FORMAT_COLOR)) == JSON_FORMAT_COLOR_AUTO) && colors_enabled())
                flags |= JSON_FORMAT_COLOR;

        if (flags & JSON_FORMAT_SSE)
                fputs("data: ", f);
        if (flags & JSON_FORMAT_SEQ)
                fputc('\x1e', f); /* ASCII Record Separator */

        json_format(f, v, flags, prefix);

        if (flags & (JSON_FORMAT_PRETTY|JSON_FORMAT_SEQ|JSON_FORMAT_SSE|JSON_FORMAT_NEWLINE))
                fputc('\n', f);
        if (flags & JSON_FORMAT_SSE)
                fputc('\n', f); /* In case of SSE add a second newline */
}