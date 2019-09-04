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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  REGKEY_HKCU ; 
 int /*<<< orphan*/  WriteIniKey32 (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteRegistryKey32 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ini_file ; 

__attribute__((used)) static __inline BOOL WriteSetting32(const char* key, int32_t val) {
	return (ini_file != NULL)?WriteIniKey32(key, val):WriteRegistryKey32(REGKEY_HKCU, key, val);
}