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
typedef  int /*<<< orphan*/  sqliterk_values ;

/* Variables and functions */
 int sqliterkValuesAddNoTerminatorText (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 

int sqliterkValuesAddText(sqliterk_values *values, const char *t)
{
    return sqliterkValuesAddNoTerminatorText(values, t, (int) strlen(t));
}