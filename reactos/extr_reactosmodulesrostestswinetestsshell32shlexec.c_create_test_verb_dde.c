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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int KEY_CREATE_SUB_KEY ; 
 int KEY_SET_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCreateKeyExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 char* argv0 ; 
 int /*<<< orphan*/  assoc_desc ; 
 char* child_file ; 
 char* heap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcat_param (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void create_test_verb_dde(const char* classname, const char* verb,
                                 int rawcmd, const char* cmdtail, const char *ddeexec,
                                 const char *application, const char *topic,
                                 const char *ifexec)
{
    HKEY hkey_shell, hkey_verb, hkey_cmd;
    char shell[MAX_PATH];
    char* cmd;
    LONG rc;

    strcpy(assoc_desc, " Assoc ");
    strcat_param(assoc_desc, "class", classname);
    strcat_param(assoc_desc, "verb", verb);
    sprintf(shell, "%d", rawcmd);
    strcat_param(assoc_desc, "rawcmd", shell);
    strcat_param(assoc_desc, "cmdtail", cmdtail);
    strcat_param(assoc_desc, "ddeexec", ddeexec);
    strcat_param(assoc_desc, "app", application);
    strcat_param(assoc_desc, "topic", topic);
    strcat_param(assoc_desc, "ifexec", ifexec);

    sprintf(shell, "%s\\shell", classname);
    rc=RegOpenKeyExA(HKEY_CLASSES_ROOT, shell, 0,
                     KEY_CREATE_SUB_KEY, &hkey_shell);
    ok(rc == ERROR_SUCCESS, "%s key creation failed with %d\n", shell, rc);

    rc=RegCreateKeyExA(hkey_shell, verb, 0, NULL, 0, KEY_CREATE_SUB_KEY,
                       NULL, &hkey_verb, NULL);
    ok(rc == ERROR_SUCCESS, "%s verb key creation failed with %d\n", verb, rc);

    rc=RegCreateKeyExA(hkey_verb, "command", 0, NULL, 0, KEY_SET_VALUE,
                       NULL, &hkey_cmd, NULL);
    ok(rc == ERROR_SUCCESS, "\'command\' key creation failed with %d\n", rc);

    if (rawcmd)
    {
        rc=RegSetValueExA(hkey_cmd, NULL, 0, REG_SZ, (LPBYTE)cmdtail, strlen(cmdtail)+1);
    }
    else
    {
        cmd = heap_alloc(strlen(argv0) + 10 + strlen(child_file) + 2 + strlen(cmdtail) + 1);
        sprintf(cmd,"%s shlexec \"%s\" %s", argv0, child_file, cmdtail);
        rc=RegSetValueExA(hkey_cmd, NULL, 0, REG_SZ, (LPBYTE)cmd, strlen(cmd)+1);
        ok(rc == ERROR_SUCCESS, "setting command failed with %d\n", rc);
        heap_free(cmd);
    }

    if (ddeexec)
    {
        HKEY hkey_ddeexec, hkey_application, hkey_topic, hkey_ifexec;

        rc=RegCreateKeyExA(hkey_verb, "ddeexec", 0, NULL, 0, KEY_SET_VALUE |
                           KEY_CREATE_SUB_KEY, NULL, &hkey_ddeexec, NULL);
        ok(rc == ERROR_SUCCESS, "\'ddeexec\' key creation failed with %d\n", rc);
        rc=RegSetValueExA(hkey_ddeexec, NULL, 0, REG_SZ, (LPBYTE)ddeexec,
                          strlen(ddeexec)+1);
        ok(rc == ERROR_SUCCESS, "set value failed with %d\n", rc);

        if (application)
        {
            rc=RegCreateKeyExA(hkey_ddeexec, "application", 0, NULL, 0, KEY_SET_VALUE,
                               NULL, &hkey_application, NULL);
            ok(rc == ERROR_SUCCESS, "\'application\' key creation failed with %d\n", rc);

            rc=RegSetValueExA(hkey_application, NULL, 0, REG_SZ, (LPBYTE)application,
                              strlen(application)+1);
            ok(rc == ERROR_SUCCESS, "set value failed with %d\n", rc);
            CloseHandle(hkey_application);
        }
        if (topic)
        {
            rc=RegCreateKeyExA(hkey_ddeexec, "topic", 0, NULL, 0, KEY_SET_VALUE,
                               NULL, &hkey_topic, NULL);
            ok(rc == ERROR_SUCCESS, "\'topic\' key creation failed with %d\n", rc);
            rc=RegSetValueExA(hkey_topic, NULL, 0, REG_SZ, (LPBYTE)topic,
                              strlen(topic)+1);
            ok(rc == ERROR_SUCCESS, "set value failed with %d\n", rc);
            CloseHandle(hkey_topic);
        }
        if (ifexec)
        {
            rc=RegCreateKeyExA(hkey_ddeexec, "ifexec", 0, NULL, 0, KEY_SET_VALUE,
                               NULL, &hkey_ifexec, NULL);
            ok(rc == ERROR_SUCCESS, "\'ifexec\' key creation failed with %d\n", rc);
            rc=RegSetValueExA(hkey_ifexec, NULL, 0, REG_SZ, (LPBYTE)ifexec,
                              strlen(ifexec)+1);
            ok(rc == ERROR_SUCCESS, "set value failed with %d\n", rc);
            CloseHandle(hkey_ifexec);
        }
        CloseHandle(hkey_ddeexec);
    }

    CloseHandle(hkey_shell);
    CloseHandle(hkey_verb);
    CloseHandle(hkey_cmd);
}