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
typedef  int /*<<< orphan*/  sqliterk_loglevel ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* sqliterkGetResultCodeDescription (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
sqliterkDefaultLog(sqliterk_loglevel level, int result, const char *msg)
{
    fprintf(stderr, "[%s] %s\n", sqliterkGetResultCodeDescription(result), msg);
}