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
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_SEVERITY_ERROR ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 int LastWinError ; 

DWORD ext2_last_winerror(DWORD default_error)
{
	return ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | (LastWinError ? LastWinError : default_error);
}