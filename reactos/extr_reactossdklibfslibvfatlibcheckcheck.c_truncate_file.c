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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  DOS_FS ;
typedef  int /*<<< orphan*/  DOS_FILE ;

/* Variables and functions */
 int FSTART (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MODIFY_START (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int next_cluster (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_fat (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void truncate_file(DOS_FS * fs, DOS_FILE * file, uint32_t clusters)
{
    int deleting;
    uint32_t walk, next;

    walk = FSTART(file, fs);
    if ((deleting = !clusters))
	MODIFY_START(file, 0, fs);
    while (walk > 0 && walk != -1) {
	next = next_cluster(fs, walk);
	if (deleting)
	    set_fat(fs, walk, 0);
	else if ((deleting = !--clusters))
	    set_fat(fs, walk, -1);
	walk = next;
    }
}