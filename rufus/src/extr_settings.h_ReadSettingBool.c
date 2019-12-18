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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  REGKEY_HKCU ; 
 int /*<<< orphan*/  ReadIniKeyBool (char const*) ; 
 int /*<<< orphan*/  ReadRegistryKeyBool (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * ini_file ; 

__attribute__((used)) static __inline BOOL ReadSettingBool(const char* key) {
	return (ini_file != NULL)?ReadIniKeyBool(key):ReadRegistryKeyBool(REGKEY_HKCU, key);
}