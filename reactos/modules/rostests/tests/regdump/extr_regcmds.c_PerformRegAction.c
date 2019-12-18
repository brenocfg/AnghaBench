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
typedef  char TCHAR ;
typedef  int REGEDIT_ACTION ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  ACTION_ADD 130 
#define  ACTION_DELETE 129 
#define  ACTION_EXPORT 128 
 int /*<<< orphan*/  FALSE ; 
 int KEY_MAX_LEN ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  delete_registry_key (char*) ; 
 int /*<<< orphan*/  export_registry_key (char*,char*) ; 
 int /*<<< orphan*/  get_file_name (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  import_registry_file (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* usage ; 

BOOL PerformRegAction(REGEDIT_ACTION action, LPSTR s)
{
    TCHAR filename[MAX_PATH];
    TCHAR reg_key_name[KEY_MAX_LEN];

    switch (action) {
    case ACTION_ADD:
        get_file_name(&s, filename, MAX_PATH);
        if (!filename[0]) {
            printf("No file name is specified\n%s", usage);
            return FALSE;
            //exit(1);
        }
        while (filename[0]) {
            if (!import_registry_file(filename)) {
                perror("");
                printf("Can't open file \"%s\"\n", filename);
                return FALSE;
                //exit(1);
            }
            get_file_name(&s, filename, MAX_PATH);
        }
        break;
    case ACTION_DELETE:
        get_file_name(&s, reg_key_name, KEY_MAX_LEN);
        if (!reg_key_name[0]) {
            printf("No registry key is specified for removal\n%s", usage);
            return FALSE;
            //exit(1);
        }
        delete_registry_key(reg_key_name);
        break;
    case ACTION_EXPORT:
        filename[0] = '\0';
        get_file_name(&s, filename, MAX_PATH);
        if (!filename[0]) {
            printf("No file name is specified\n%s", usage);
            return FALSE;
            //exit(1);
        }
        if (s[0]) {
            get_file_name(&s, reg_key_name, KEY_MAX_LEN);
            export_registry_key(filename, reg_key_name);
        } else {
            export_registry_key(filename, NULL);
        }
        break;
    default:
        printf("Unhandled action!\n");
        return FALSE;
    }
    return TRUE;
}