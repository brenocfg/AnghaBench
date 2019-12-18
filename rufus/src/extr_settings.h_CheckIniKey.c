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
 char* get_token_data_file (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ini_file ; 
 int /*<<< orphan*/  safe_free (char*) ; 

__attribute__((used)) static __inline BOOL CheckIniKey(const char* key) {
	char* str = get_token_data_file(key, ini_file);
	BOOL ret = (str != NULL);
	safe_free(str);
	return ret;
}