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
struct TYPE_4__ {int /*<<< orphan*/  output_filename; } ;
typedef  TYPE_1__ jbig2dec_params_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hash_print (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
write_document_hash(jbig2dec_params_t *params)
{
    FILE *out;

    if (!strncmp(params->output_filename, "-", 2)) {
        out = stderr;
    } else {
        out = stdout;
    }

    fprintf(out, "Hash of decoded document: ");
    hash_print(params, out);
    fprintf(out, "\n");

    return 0;
}