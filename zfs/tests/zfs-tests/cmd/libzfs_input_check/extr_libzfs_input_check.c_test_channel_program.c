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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_IOC_CHANNEL_PROGRAM ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_string_array (int /*<<< orphan*/ *,char*,char* const*,int) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_channel_program(const char *pool)
{
	const char *program =
	    "arg = ...\n"
	    "argv = arg[\"argv\"]\n"
	    "return argv[1]";
	char *const argv[1] = { "Hello World!" };
	nvlist_t *required = fnvlist_alloc();
	nvlist_t *optional = fnvlist_alloc();
	nvlist_t *args = fnvlist_alloc();

	fnvlist_add_string(required, "program", program);
	fnvlist_add_string_array(args, "argv", argv, 1);
	fnvlist_add_nvlist(required, "arg", args);

	fnvlist_add_boolean_value(optional, "sync", B_TRUE);
	fnvlist_add_uint64(optional, "instrlimit", 1000 * 1000);
	fnvlist_add_uint64(optional, "memlimit", 8192 * 1024);

	IOC_INPUT_TEST(ZFS_IOC_CHANNEL_PROGRAM, pool, required, optional, 0);

	nvlist_free(args);
	nvlist_free(optional);
	nvlist_free(required);
}