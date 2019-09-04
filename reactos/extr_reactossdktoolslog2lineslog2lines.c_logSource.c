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
struct TYPE_2__ {scalar_t__ nr2; int /*<<< orphan*/  file2; scalar_t__ nr1; int /*<<< orphan*/  file1; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ lastLine ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  log_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
logSource(FILE *outFile)
{
    log_file(outFile, lastLine.file1, lastLine.nr1);
    if (lastLine.nr2)
    {
        log(outFile, "| ---- [%u] ----\n", lastLine.nr2);
        log_file(outFile, lastLine.file2, lastLine.nr2);
    }
}