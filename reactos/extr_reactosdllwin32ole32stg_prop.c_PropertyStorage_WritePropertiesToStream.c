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
struct PropertyClosure {int /*<<< orphan*/  hr; int /*<<< orphan*/ * sectionOffset; int /*<<< orphan*/  propNum; } ;
struct TYPE_3__ {int /*<<< orphan*/  propid_to_prop; } ;
typedef  TYPE_1__ PropertyStorage_impl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PropertyStorage_PropertiesWriter ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictionary_enumerate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct PropertyClosure*) ; 

__attribute__((used)) static HRESULT PropertyStorage_WritePropertiesToStream(
 PropertyStorage_impl *This, DWORD startingPropNum, DWORD *sectionOffset)
{
    struct PropertyClosure closure;

    assert(sectionOffset);
    closure.hr = S_OK;
    closure.propNum = startingPropNum;
    closure.sectionOffset = sectionOffset;
    dictionary_enumerate(This->propid_to_prop, PropertyStorage_PropertiesWriter,
     &closure);
    return closure.hr;
}