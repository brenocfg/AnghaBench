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
typedef  TYPE_1__* synctex_updater_t ;
typedef  int /*<<< orphan*/  gzFile ;
struct TYPE_4__ {scalar_t__ length; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ SYNCTEX_FILE ; 
 scalar_t__ SYNCTEX_NO_GZ ; 
 int /*<<< orphan*/  SYNCTEX_fprintf (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

void synctex_updater_free(synctex_updater_t updater){
	if (NULL==updater) {
		return;
	}
	if (updater->length>0) {
		SYNCTEX_fprintf(SYNCTEX_FILE,"!%i\n",updater->length);
	}
	if (SYNCTEX_NO_GZ) {
		fclose((FILE *)SYNCTEX_FILE);
	} else {
		gzclose((gzFile)SYNCTEX_FILE);
	}
	free(updater);
	printf("... done.\n");
	return;
}