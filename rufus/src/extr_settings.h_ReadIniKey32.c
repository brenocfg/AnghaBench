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
 int /*<<< orphan*/  free (char*) ; 
 char* get_token_data_file (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ini_file ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int32_t ReadIniKey32(const char* key) {
	int32_t val = 0;
	char* str = get_token_data_file(key, ini_file);
	if (str != NULL) {
		val = strtol(str, NULL, 0);
		free(str);
	}
	return val;
}