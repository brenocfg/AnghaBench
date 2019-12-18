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

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char) ; 
 unsigned long long progress_full ; 
 size_t progress_printed ; 
 int /*<<< orphan*/  stdout ; 

void memtest_progress_step(size_t curr, size_t size, char c) {
    size_t chars = ((unsigned long long)curr*progress_full)/size, j;

    for (j = 0; j < chars-progress_printed; j++) printf("%c",c);
    progress_printed = chars;
    fflush(stdout);
}