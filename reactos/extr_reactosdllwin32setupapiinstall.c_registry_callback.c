#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct registry_callback_info {scalar_t__ delete; int /*<<< orphan*/  default_root; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_NULL ;
struct TYPE_3__ {int nLength; int /*<<< orphan*/ * lpSecurityDescriptor; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  int /*<<< orphan*/ * PSECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/ * PCWSTR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ConvertStringSecurityDescriptorToSecurityDescriptorW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DotSecurity ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ FALSE ; 
 int FLG_ADDREG_DELREG_BIT ; 
 int FLG_ADDREG_OVERWRITEONLY ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int MAX_INF_STRING_LENGTH ; 
 int /*<<< orphan*/  MyFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MyMalloc (int) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDDL_REVISION_1 ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetIntField (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  SetupGetLineTextW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int /*<<< orphan*/  do_reg_operation (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_root_key (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL registry_callback( HINF hinf, PCWSTR field, void *arg )
{
    struct registry_callback_info *info = arg;
    LPWSTR security_key, security_descriptor;
    INFCONTEXT context, security_context;
    PSECURITY_DESCRIPTOR sd = NULL;
    SECURITY_ATTRIBUTES security_attributes = { 0, };
    HKEY root_key, hkey;
    DWORD required;

    BOOL ok = SetupFindFirstLineW( hinf, field, NULL, &context );
    if (!ok)
        return TRUE;

    /* Check for .Security section */
    security_key = MyMalloc( (strlenW( field ) + strlenW( DotSecurity )) * sizeof(WCHAR) + sizeof(UNICODE_NULL) );
    if (!security_key)
    {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FALSE;
    }
    strcpyW( security_key, field );
    strcatW( security_key, DotSecurity );
    ok = SetupFindFirstLineW( hinf, security_key, NULL, &security_context );
    MyFree(security_key);
    if (ok)
    {
        if (!SetupGetLineTextW( &security_context, NULL, NULL, NULL, NULL, 0, &required ))
            return FALSE;
        security_descriptor = MyMalloc( required * sizeof(WCHAR) );
        if (!security_descriptor)
        {
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return FALSE;
        }
        if (!SetupGetLineTextW( &security_context, NULL, NULL, NULL, security_descriptor, required, NULL ))
            return FALSE;
        ok = ConvertStringSecurityDescriptorToSecurityDescriptorW( security_descriptor, SDDL_REVISION_1, &sd, NULL );
        MyFree( security_descriptor );
        if (!ok)
            return FALSE;
        security_attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
        security_attributes.lpSecurityDescriptor = sd;
    }

    for (ok = TRUE; ok; ok = SetupFindNextLine( &context, &context ))
    {
        WCHAR buffer[MAX_INF_STRING_LENGTH];
        INT flags;

        /* get root */
        if (!SetupGetStringFieldW( &context, 1, buffer, sizeof(buffer)/sizeof(WCHAR), NULL ))
            continue;
        if (!(root_key = get_root_key( buffer, info->default_root )))
            continue;

        /* get key */
        if (!SetupGetStringFieldW( &context, 2, buffer, sizeof(buffer)/sizeof(WCHAR), NULL ))
            *buffer = 0;

        /* get flags */
        if (!SetupGetIntField( &context, 4, &flags )) flags = 0;

        if (!info->delete)
        {
            if (flags & FLG_ADDREG_DELREG_BIT) continue;  /* ignore this entry */
        }
        else
        {
            if (!flags) flags = FLG_ADDREG_DELREG_BIT;
            else if (!(flags & FLG_ADDREG_DELREG_BIT)) continue;  /* ignore this entry */
        }

        if (info->delete || (flags & FLG_ADDREG_OVERWRITEONLY))
        {
            if (RegOpenKeyW( root_key, buffer, &hkey )) continue;  /* ignore if it doesn't exist */
        }
        else if (RegCreateKeyExW( root_key, buffer, 0, NULL, 0, MAXIMUM_ALLOWED,
            sd ? &security_attributes : NULL, &hkey, NULL ))
        {
            ERR( "could not create key %p %s\n", root_key, debugstr_w(buffer) );
            continue;
        }
        TRACE( "key %p %s\n", root_key, debugstr_w(buffer) );

        /* get value name */
        if (!SetupGetStringFieldW( &context, 3, buffer, sizeof(buffer)/sizeof(WCHAR), NULL ))
            *buffer = 0;

        /* and now do it */
        if (!do_reg_operation( hkey, buffer, &context, flags ))
        {
            if (hkey != root_key) RegCloseKey( hkey );
            if (sd) LocalFree( sd );
            return FALSE;
        }
        if (hkey != root_key) RegCloseKey( hkey );
    }
    if (sd) LocalFree( sd );
    return TRUE;
}