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
struct TYPE_2__ {scalar_t__ valid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ lastLine ; 
 int /*<<< orphan*/  logSource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opt_Source ; 

__attribute__((used)) static void
reportSource(FILE *outFile)
{
    if (!opt_Source)
        return;
    if (lastLine.valid)
        logSource(outFile);
}