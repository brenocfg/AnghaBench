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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SetDefaults () ; 
 int /*<<< orphan*/  _T (char*) ; 
 int dRotate ; 
 int /*<<< orphan*/  registryPath ; 

void ReadRegistry(){
	LONG result;
	HKEY skey;
	DWORD valtype, valsize, val;

	SetDefaults();

	result = RegOpenKeyEx(HKEY_CURRENT_USER, registryPath, 0, KEY_READ, &skey);
	if(result != ERROR_SUCCESS)
		return;

	valsize=sizeof(val);

	result = RegQueryValueEx(skey, _T("Rotate"), 0, &valtype, (LPBYTE)&val, &valsize);
	if(result == ERROR_SUCCESS)
		dRotate = val;
	RegCloseKey(skey);
}