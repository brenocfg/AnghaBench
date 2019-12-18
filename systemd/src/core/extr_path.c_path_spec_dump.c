#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ PathSpec ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char*,int /*<<< orphan*/ ) ; 
 char* path_type_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void path_spec_dump(PathSpec *s, FILE *f, const char *prefix) {
        fprintf(f,
                "%s%s: %s\n",
                prefix,
                path_type_to_string(s->type),
                s->path);
}