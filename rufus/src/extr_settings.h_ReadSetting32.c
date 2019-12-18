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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  REGKEY_HKCU ; 
 int /*<<< orphan*/  ReadIniKey32 (char const*) ; 
 int /*<<< orphan*/  ReadRegistryKey32 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * ini_file ; 

__attribute__((used)) static __inline int32_t ReadSetting32(const char* key) {
	return (ini_file != NULL)?ReadIniKey32(key):ReadRegistryKey32(REGKEY_HKCU, key);
}