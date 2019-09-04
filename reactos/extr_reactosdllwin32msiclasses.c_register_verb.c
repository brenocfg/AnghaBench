#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_12__ {int /*<<< orphan*/  FullKeypath; } ;
struct TYPE_11__ {TYPE_1__* Feature; } ;
struct TYPE_10__ {scalar_t__ Sequence; scalar_t__ Verb; scalar_t__ Command; int /*<<< orphan*/  Argument; } ;
struct TYPE_9__ {int /*<<< orphan*/  Feature; } ;
typedef  TYPE_2__ MSIVERB ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_3__ MSIEXTENSION ;
typedef  TYPE_4__ MSICOMPONENT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 scalar_t__ MSI_NULL_INTEGER ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_alloc (int) ; 
 int /*<<< orphan*/  msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_build_directory_name (int,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  msi_create_component_advertise_string (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_reg_set_subkey_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msi_reg_set_val_multi_str (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_reg_set_val_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strcatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szSpace ; 

__attribute__((used)) static UINT register_verb(MSIPACKAGE *package, LPCWSTR progid, 
                MSICOMPONENT* component, const MSIEXTENSION* extension,
                MSIVERB* verb, INT* Sequence )
{
    LPWSTR keyname;
    HKEY key;
    static const WCHAR szShell[] = {'s','h','e','l','l',0};
    static const WCHAR szCommand[] = {'c','o','m','m','a','n','d',0};
    static const WCHAR fmt[] = {'\"','%','s','\"',' ','%','s',0};
    static const WCHAR fmt2[] = {'\"','%','s','\"',0};
    LPWSTR command;
    DWORD size;
    LPWSTR advertise;

    keyname = msi_build_directory_name(4, progid, szShell, verb->Verb, szCommand);

    TRACE("Making Key %s\n",debugstr_w(keyname));
    RegCreateKeyW(HKEY_CLASSES_ROOT, keyname, &key);
    size = strlenW(component->FullKeypath);
    if (verb->Argument)
        size += strlenW(verb->Argument);
     size += 4;

     command = msi_alloc(size * sizeof (WCHAR));
     if (verb->Argument)
        sprintfW(command, fmt, component->FullKeypath, verb->Argument);
     else
        sprintfW(command, fmt2, component->FullKeypath);

     msi_reg_set_val_str( key, NULL, command );
     msi_free(command);

     advertise = msi_create_component_advertise_string(package, component,
                                                       extension->Feature->Feature);
     size = strlenW(advertise);

     if (verb->Argument)
         size += strlenW(verb->Argument);
     size += 4;

     command = msi_alloc_zero(size * sizeof (WCHAR));

     strcpyW(command,advertise);
     if (verb->Argument)
     {
         strcatW(command,szSpace);
         strcatW(command,verb->Argument);
     }

     msi_reg_set_val_multi_str( key, szCommand, command );
     
     RegCloseKey(key);
     msi_free(keyname);
     msi_free(advertise);
     msi_free(command);

     if (verb->Command)
     {
        keyname = msi_build_directory_name( 3, progid, szShell, verb->Verb );
        msi_reg_set_subkey_val( HKEY_CLASSES_ROOT, keyname, NULL, verb->Command );
        msi_free(keyname);
     }

     if (verb->Sequence != MSI_NULL_INTEGER)
     {
        if (*Sequence == MSI_NULL_INTEGER || verb->Sequence < *Sequence)
        {
            *Sequence = verb->Sequence;
            keyname = msi_build_directory_name( 2, progid, szShell );
            msi_reg_set_subkey_val( HKEY_CLASSES_ROOT, keyname, NULL, verb->Verb );
            msi_free(keyname);
        }
    }
    return ERROR_SUCCESS;
}