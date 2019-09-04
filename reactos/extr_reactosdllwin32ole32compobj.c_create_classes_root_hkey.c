#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  attr ;
struct TYPE_5__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_6__ {int Length; TYPE_1__* ObjectName; int /*<<< orphan*/ * SecurityQualityOfService; int /*<<< orphan*/ * SecurityDescriptor; scalar_t__ Attributes; scalar_t__ RootDirectory; } ;
typedef  TYPE_2__ OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedCompareExchangePointer (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  classes_rootW ; 
 int /*<<< orphan*/  classes_root_hkey ; 
 scalar_t__ create_key (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HKEY create_classes_root_hkey(DWORD access)
{
    HKEY hkey, ret = 0;
    OBJECT_ATTRIBUTES attr;
    UNICODE_STRING name;

    attr.Length = sizeof(attr);
    attr.RootDirectory = 0;
    attr.ObjectName = &name;
    attr.Attributes = 0;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;
    RtlInitUnicodeString( &name, classes_rootW );
    if (create_key( &hkey, access, &attr )) return 0;
    TRACE( "%s -> %p\n", debugstr_w(attr.ObjectName->Buffer), hkey );

    if (!(access & KEY_WOW64_64KEY))
    {
        if (!(ret = InterlockedCompareExchangePointer( (void **)&classes_root_hkey, hkey, 0 )))
            ret = hkey;
        else
            NtClose( hkey );  /* somebody beat us to it */
    }
    else
        ret = hkey;
    return ret;
}