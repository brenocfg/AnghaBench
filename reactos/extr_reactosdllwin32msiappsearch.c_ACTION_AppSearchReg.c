#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/  db; } ;
struct TYPE_14__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_13__ {char const* Name; } ;
typedef  TYPE_1__ MSISIGNATURE ;
typedef  TYPE_2__ MSIRECORD ;
typedef  TYPE_3__ MSIPACKAGE ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  char* LPBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_ConvertRegValue (scalar_t__,char*,scalar_t__,char**) ; 
 int /*<<< orphan*/  ACTION_SearchDirectory (TYPE_3__*,TYPE_1__*,char*,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ExpandEnvironmentStringsW (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/ * HKEY_CURRENT_USER ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/ * HKEY_USERS ; 
 TYPE_2__* MSI_QueryGetRecord (int /*<<< orphan*/ ,char const*,char const*) ; 
 int MSI_RecordGetInteger (TYPE_2__*,int) ; 
 char* MSI_RecordGetString (TYPE_2__*,int) ; 
 scalar_t__ REG_EXPAND_SZ ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 char* app_search_file (char*,TYPE_1__*) ; 
 scalar_t__ debugstr_w (char const*) ; 
 int /*<<< orphan*/  deformat_string (TYPE_3__*,char const*,char**) ; 
 char* msi_alloc (scalar_t__) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
#define  msidbLocatorTypeDirectory 134 
#define  msidbLocatorTypeFileName 133 
#define  msidbLocatorTypeRawValue 132 
#define  msidbRegistryRootClassesRoot 131 
#define  msidbRegistryRootCurrentUser 130 
#define  msidbRegistryRootLocalMachine 129 
#define  msidbRegistryRootUsers 128 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 char* strchrW (char*,char) ; 

__attribute__((used)) static UINT ACTION_AppSearchReg(MSIPACKAGE *package, LPWSTR *appValue, MSISIGNATURE *sig)
{
    static const WCHAR query[] =  {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
        'R','e','g','L','o','c','a','t','o','r',' ','W','H','E','R','E',' ',
        'S','i','g','n','a','t','u','r','e','_',' ','=',' ', '\'','%','s','\'',0};
    const WCHAR *keyPath, *valueName;
    WCHAR *deformatted = NULL, *ptr = NULL, *end;
    int root, type;
    HKEY rootKey, key = NULL;
    DWORD sz = 0, regType;
    LPBYTE value = NULL;
    MSIRECORD *row;
    UINT rc;

    TRACE("%s\n", debugstr_w(sig->Name));

    *appValue = NULL;

    row = MSI_QueryGetRecord( package->db, query, sig->Name );
    if (!row)
    {
        TRACE("failed to query RegLocator for %s\n", debugstr_w(sig->Name));
        return ERROR_SUCCESS;
    }

    root = MSI_RecordGetInteger(row, 2);
    keyPath = MSI_RecordGetString(row, 3);
    valueName = MSI_RecordGetString(row, 4);
    type = MSI_RecordGetInteger(row, 5);

    deformat_string(package, keyPath, &deformatted);

    switch (root)
    {
    case msidbRegistryRootClassesRoot:
        rootKey = HKEY_CLASSES_ROOT;
        break;
    case msidbRegistryRootCurrentUser:
        rootKey = HKEY_CURRENT_USER;
        break;
    case msidbRegistryRootLocalMachine:
        rootKey = HKEY_LOCAL_MACHINE;
        break;
    case msidbRegistryRootUsers:
        rootKey = HKEY_USERS;
        break;
    default:
        WARN("Unknown root key %d\n", root);
        goto end;
    }

    rc = RegOpenKeyW(rootKey, deformatted, &key);
    if (rc)
    {
        TRACE("RegOpenKeyW returned %d\n", rc);
        goto end;
    }

    msi_free(deformatted);
    deformat_string(package, valueName, &deformatted);

    rc = RegQueryValueExW(key, deformatted, NULL, NULL, NULL, &sz);
    if (rc)
    {
        TRACE("RegQueryValueExW returned %d\n", rc);
        goto end;
    }
    /* FIXME: sanity-check sz before allocating (is there an upper-limit
     * on the value of a property?)
     */
    value = msi_alloc( sz );
    rc = RegQueryValueExW(key, deformatted, NULL, &regType, value, &sz);
    if (rc)
    {
        TRACE("RegQueryValueExW returned %d\n", rc);
        goto end;
    }

    /* bail out if the registry key is empty */
    if (sz == 0)
        goto end;

    /* expand if needed */
    if (regType == REG_EXPAND_SZ)
    {
        sz = ExpandEnvironmentStringsW((LPCWSTR)value, NULL, 0);
        if (sz)
        {
            LPWSTR buf = msi_alloc(sz * sizeof(WCHAR));
            ExpandEnvironmentStringsW((LPCWSTR)value, buf, sz);
            msi_free(value);
            value = (LPBYTE)buf;
        }
    }

    if ((regType == REG_SZ || regType == REG_EXPAND_SZ) &&
        (ptr = strchrW((LPWSTR)value, '"')) && (end = strchrW(++ptr, '"')))
        *end = '\0';
    else
        ptr = (LPWSTR)value;

    switch (type & 0x0f)
    {
    case msidbLocatorTypeDirectory:
        ACTION_SearchDirectory(package, sig, ptr, 0, appValue);
        break;
    case msidbLocatorTypeFileName:
        *appValue = app_search_file(ptr, sig);
        break;
    case msidbLocatorTypeRawValue:
        ACTION_ConvertRegValue(regType, value, sz, appValue);
        break;
    default:
        FIXME("unimplemented for type %d (key path %s, value %s)\n",
              type, debugstr_w(keyPath), debugstr_w(valueName));
    }
end:
    msi_free( value );
    RegCloseKey( key );
    msi_free( deformatted );

    msiobj_release(&row->hdr);
    return ERROR_SUCCESS;
}