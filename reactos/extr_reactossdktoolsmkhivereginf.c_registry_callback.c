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
typedef  scalar_t__ WCHAR ;
typedef  int ULONG ;
typedef  scalar_t__* PWCHAR ;
typedef  int /*<<< orphan*/ * PINFCONTEXT ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int FLG_ADDREG_DELREG_BIT ; 
 int FLG_ADDREG_OVERWRITEONLY ; 
 scalar_t__ InfHostFindFirstLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ InfHostFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InfHostFreeContext (int /*<<< orphan*/ *) ; 
 scalar_t__ InfHostGetIntField (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ InfHostGetStringField (int /*<<< orphan*/ *,int,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int MAX_INF_STRING_LENGTH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyW (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  do_reg_operation (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_root_key (scalar_t__*) ; 
 size_t strlenW (scalar_t__*) ; 

__attribute__((used)) static BOOL
registry_callback(HINF hInf, PCWSTR Section, BOOL Delete)
{
    WCHAR Buffer[MAX_INF_STRING_LENGTH];
    PWCHAR ValuePtr;
    ULONG Flags;
    size_t Length;

    PINFCONTEXT Context = NULL;
    HKEY KeyHandle;
    BOOL Ok;

    Ok = InfHostFindFirstLine(hInf, Section, NULL, &Context) == 0;
    if (!Ok)
        return TRUE; /* Don't fail if the section isn't present */

    for (Ok = TRUE; Ok; Ok = (InfHostFindNextLine(Context, Context) == 0))
    {
        /* Get root */
        if (InfHostGetStringField(Context, 1, Buffer, sizeof(Buffer)/sizeof(WCHAR), NULL) != 0)
            continue;
        if (!get_root_key(Buffer))
            continue;

        /* Get key */
        Length = strlenW(Buffer);
        if (InfHostGetStringField(Context, 2, Buffer + Length, sizeof(Buffer)/sizeof(WCHAR) - (ULONG)Length, NULL) != 0)
            *Buffer = 0;

        DPRINT("KeyName: <%S>\n", Buffer);

        /* Get flags */
        if (InfHostGetIntField(Context, 4, (INT*)&Flags) != 0)
            Flags = 0;

        if (Delete)
        {
            if (!Flags)
                Flags = FLG_ADDREG_DELREG_BIT;
            else if (!(Flags & FLG_ADDREG_DELREG_BIT))
                continue; /* ignore this entry */
        }
        else
        {
            if (Flags & FLG_ADDREG_DELREG_BIT)
                continue; /* ignore this entry */
        }

        DPRINT("Flags: 0x%x\n", Flags);

        if (Delete || (Flags & FLG_ADDREG_OVERWRITEONLY))
        {
            if (RegOpenKeyW(NULL, Buffer, &KeyHandle) != ERROR_SUCCESS)
            {
                DPRINT("RegOpenKey(%S) failed\n", Buffer);
                continue;  /* ignore if it doesn't exist */
            }
        }
        else
        {
            if (RegCreateKeyW(NULL, Buffer, &KeyHandle) != ERROR_SUCCESS)
            {
                DPRINT("RegCreateKey(%S) failed\n", Buffer);
                continue;
            }
        }

        /* Get value name */
        if (InfHostGetStringField(Context, 3, Buffer, sizeof(Buffer)/sizeof(WCHAR), NULL) == 0)
        {
            ValuePtr = Buffer;
        }
        else
        {
            ValuePtr = NULL;
        }

        /* And now do it */
        if (!do_reg_operation(KeyHandle, ValuePtr, Context, Flags))
        {
            RegCloseKey(KeyHandle);
            return FALSE;
        }

        RegCloseKey(KeyHandle);
    }

    InfHostFreeContext(Context);

    return TRUE;
}