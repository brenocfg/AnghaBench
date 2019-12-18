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
struct TYPE_2__ {int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 TYPE_1__ g ; 
 int /*<<< orphan*/  testPrintError (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void testPrintUsage(const char *zArgs){
  testPrintError("Usage: %s %s %s\n", g.argv[0], g.argv[1], zArgs);
}