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
typedef  int /*<<< orphan*/ * SC_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateServiceA (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 scalar_t__ GetFileAttributesA (char*) ; 
 scalar_t__ GetLastError () ; 
 int GetModuleFileNameA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  SERVICE_DEMAND_START ; 
 int /*<<< orphan*/  SERVICE_ERROR_IGNORE ; 
 int /*<<< orphan*/  SERVICE_WIN32_OWN_PROCESS ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  scm_handle ; 
 char* service_name ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static SC_HANDLE register_service(const char *test_name)
{
    char service_cmd[MAX_PATH+150], *ptr;
    SC_HANDLE service;

    ptr = service_cmd + GetModuleFileNameA(NULL, service_cmd, MAX_PATH);

    /* If the file doesn't exist, assume we're using built-in exe and append .so to the path */
    if(GetFileAttributesA(service_cmd) == INVALID_FILE_ATTRIBUTES) {
        strcpy(ptr, ".so");
        ptr += 3;
    }

    strcpy(ptr, " service ");
    ptr += strlen(ptr);
    sprintf(ptr, "%s ", test_name);
    ptr += strlen(ptr);
    strcpy(ptr, service_name);

    trace("service_cmd \"%s\"\n", service_cmd);

    service = CreateServiceA(scm_handle, service_name, service_name, GENERIC_ALL,
                             SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
                             service_cmd, NULL, NULL, NULL, NULL, NULL);
    if(!service && GetLastError() == ERROR_ACCESS_DENIED) {
        skip("Not enough access right to create service\n");
        return NULL;
    }

    ok(service != NULL, "CreateService failed: %u\n", GetLastError());
    return service;
}