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
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  clipLength (char const*) ; 
 int /*<<< orphan*/  logMessage (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void sqlTraceCallback(void *NotUsed1, const char *zSql){
  UNUSED_PARAMETER(NotUsed1);
  logMessage("[%.*s]", clipLength(zSql), zSql);
}