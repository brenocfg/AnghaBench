#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  file2; int /*<<< orphan*/  file1; scalar_t__ nr2; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ lastLine ; 
 int /*<<< orphan*/  log_rev_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
logRevCheck(FILE *outFile)
{
    int twice = 0;

    twice = (lastLine.nr2 && strcmp(lastLine.file1, lastLine.file2) != 0);
    log_rev_check(outFile, lastLine.file1, twice);
    if (twice)
    {
        log_rev_check(outFile, lastLine.file2, twice);
    }
}