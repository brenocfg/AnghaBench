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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  REGKEY_HKCU ; 
 int /*<<< orphan*/  WriteIniKey64 (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteRegistryKey64 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ini_file ; 

__attribute__((used)) static __inline BOOL WriteSetting64(const char* key, int64_t val) {
	return (ini_file != NULL)?WriteIniKey64(key, val):WriteRegistryKey64(REGKEY_HKCU, key, val);
}