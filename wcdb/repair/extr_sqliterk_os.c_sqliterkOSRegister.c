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
typedef  int /*<<< orphan*/  sqliterk_os ;

/* Variables and functions */
 int SQLITERK_OK ; 
 int /*<<< orphan*/  s_os ; 

int sqliterkOSRegister(sqliterk_os os)
{
    s_os = os;
    return SQLITERK_OK;
}