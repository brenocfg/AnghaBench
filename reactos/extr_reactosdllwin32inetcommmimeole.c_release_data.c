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
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IStream ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IStream ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_data(REFIID riid, void *data)
{
    if(!data) return;

    if(IsEqualIID(riid, &IID_IStream))
        IStream_Release((IStream *)data);
    else
        FIXME("Unhandled data format %s\n", debugstr_guid(riid));
}