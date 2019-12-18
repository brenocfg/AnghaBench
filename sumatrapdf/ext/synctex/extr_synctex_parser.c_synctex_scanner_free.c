#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* synctex_scanner_t ;
struct TYPE_5__ {struct TYPE_5__* lists_of_friends; struct TYPE_5__* synctex; struct TYPE_5__* output; struct TYPE_5__* output_fmt; int /*<<< orphan*/  input; int /*<<< orphan*/  sheet; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SYNCTEX_FILE ; 
 int /*<<< orphan*/  SYNCTEX_FREE (int /*<<< orphan*/ ) ; 
 TYPE_1__* SYNCTEX_START ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ *) ; 

void synctex_scanner_free(synctex_scanner_t scanner) {
	if (NULL == scanner) {
		return;
	}
	if (SYNCTEX_FILE) {
		gzclose(SYNCTEX_FILE);
		SYNCTEX_FILE = NULL;
	}
	SYNCTEX_FREE(scanner->sheet);
	SYNCTEX_FREE(scanner->input);
	free(SYNCTEX_START);
	free(scanner->output_fmt);
	free(scanner->output);
	free(scanner->synctex);
	free(scanner->lists_of_friends);
	free(scanner);
}