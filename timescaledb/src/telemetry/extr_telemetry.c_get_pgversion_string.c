#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* GetConfigOptionByName (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int,int,...) ; 
 TYPE_1__* makeStringInfo () ; 
 long strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
get_pgversion_string()
{
	StringInfo buf = makeStringInfo();
	int major, minor, patch;

	/*
	 * We have to read the server version from GUC and not use any of
	 * the macros. By using any of the macros we would get the version
	 * the extension is compiled against instead of the version actually
	 * running.
	 */
	char *server_version_num_guc = GetConfigOptionByName("server_version_num", NULL, false);
	long server_version_num = strtol(server_version_num_guc, NULL, 10);

	major = server_version_num / 10000;
	minor = (server_version_num / 100) % 100;
	patch = server_version_num % 100;

	if (server_version_num < 100000)
	{
		Assert(major == 9 && minor == 6);
		appendStringInfo(buf, "%d.%d.%d", major, minor, patch);
	}
	else
	{
		Assert(major >= 10 && minor == 0);
		appendStringInfo(buf, "%d.%d", major, patch);
	}

	return buf->data;
}