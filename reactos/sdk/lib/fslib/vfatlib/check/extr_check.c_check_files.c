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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  int /*<<< orphan*/  DOS_FS ;
typedef  TYPE_1__ DOS_FILE ;

/* Variables and functions */
 scalar_t__ check_file (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int check_files(DOS_FS * fs, DOS_FILE * start)
{
    while (start) {
	if (check_file(fs, start))
	    return 1;
	start = start->next;
    }
    return 0;
}