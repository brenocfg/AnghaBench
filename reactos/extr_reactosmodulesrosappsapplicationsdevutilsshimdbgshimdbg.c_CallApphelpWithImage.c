#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Buffer; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_7__ {scalar_t__ ImageHandle; int /*<<< orphan*/  ImageName; } ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_2__ APPHELP_CACHE_SERVICE_LOOKUP ;
typedef  int /*<<< orphan*/  APPHELPCACHESERVICECLASS ;

/* Variables and functions */
 int /*<<< orphan*/  CallApphelp (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ MapFile (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  NtClose (scalar_t__) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (char*,char*,char*) ; 

void CallApphelpWithImage(char* filename, int MapIt,
                        APPHELPCACHESERVICECLASS Service, char* ServiceName)
{
    UNICODE_STRING PathName = {0};
    APPHELP_CACHE_SERVICE_LOOKUP CacheEntry;

    HANDLE FileHandle = MapFile(filename, &PathName, MapIt);

    xprintf("Calling %s %s mapping\n", ServiceName, (MapIt ? "with" : "without"));

    RtlInitUnicodeString(&CacheEntry.ImageName, PathName.Buffer);
    CacheEntry.ImageHandle = FileHandle ? FileHandle : (HANDLE)-1;
    CallApphelp(Service, &CacheEntry);
    // we piggy-back on the PathName, so let the Cleanup take care of the string
    //RtlFreeUnicodeString(&CacheEntry.ImageName);

    if (FileHandle)
        NtClose(FileHandle);
    RtlFreeUnicodeString(&PathName);
}