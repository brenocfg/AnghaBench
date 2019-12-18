#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ stream; } ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  TYPE_1__ FILENULL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
cmsBool  NULLClose(cmsContext ContextID, cmsIOHANDLER* iohandler)
{
    FILENULL* ResData = (FILENULL*) iohandler ->stream;

    _cmsFree(ContextID, ResData);
    _cmsFree(ContextID, iohandler);
    return TRUE;
}