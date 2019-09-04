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
typedef  int /*<<< orphan*/  VOID ;
typedef  void* USHORT ;
struct TYPE_3__ {void* NumberOfIdEntries; void* NumberOfNamedEntries; scalar_t__ MinorVersion; scalar_t__ MajorVersion; scalar_t__ TimeDateStamp; scalar_t__ Characteristics; } ;
typedef  TYPE_1__* PIMAGE_RESOURCE_DIRECTORY ;

/* Variables and functions */

__attribute__((used)) static
VOID
InitializeResourceDirectory(
    PIMAGE_RESOURCE_DIRECTORY ResourceDirectory,
    USHORT NumberOfNamedEntries,
    USHORT NumberOfIdEntries)
{
    ResourceDirectory->Characteristics = 0;
    ResourceDirectory->TimeDateStamp = 0;
    ResourceDirectory->MajorVersion = 0;
    ResourceDirectory->MinorVersion = 0;
    ResourceDirectory->NumberOfNamedEntries = NumberOfNamedEntries;
    ResourceDirectory->NumberOfIdEntries = NumberOfIdEntries;
}