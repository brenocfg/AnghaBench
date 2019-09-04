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
typedef  int /*<<< orphan*/  attr ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_3__ {int Length; void* RootDirectory; int /*<<< orphan*/ * SecurityQualityOfService; int /*<<< orphan*/ * SecurityDescriptor; scalar_t__ Attributes; int /*<<< orphan*/ * ObjectName; } ;
typedef  TYPE_1__ OBJECT_ATTRIBUTES ;
typedef  void* HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  NtClose (void*) ; 
 scalar_t__ NtCreateKey (void**,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ RtlOpenCurrentUser (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ STATUS_SUCCESS ; 

__attribute__((used)) static inline HANDLE create_registry_key(void)
{
    static const WCHAR cplW[] = {'C','o','n','t','r','o','l',' ','P','a','n','e','l',0};
    static const WCHAR intlW[] = {'I','n','t','e','r','n','a','t','i','o','n','a','l',0};
    OBJECT_ATTRIBUTES attr;
    UNICODE_STRING nameW;
    HANDLE cpl_key, hkey = 0;

    if (RtlOpenCurrentUser( KEY_ALL_ACCESS, &hkey ) != STATUS_SUCCESS) return 0;

    attr.Length = sizeof(attr);
    attr.RootDirectory = hkey;
    attr.ObjectName = &nameW;
    attr.Attributes = 0;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;
    RtlInitUnicodeString( &nameW, cplW );

    if (!NtCreateKey( &cpl_key, KEY_ALL_ACCESS, &attr, 0, NULL, 0, NULL ))
    {
        NtClose( attr.RootDirectory );
        attr.RootDirectory = cpl_key;
        RtlInitUnicodeString( &nameW, intlW );
        if (NtCreateKey( &hkey, KEY_ALL_ACCESS, &attr, 0, NULL, 0, NULL )) hkey = 0;
    }
    NtClose( attr.RootDirectory );
    return hkey;
}