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
struct PropertyClosure {int /*<<< orphan*/  hr; int /*<<< orphan*/  sectionOffset; int /*<<< orphan*/  propNum; } ;
typedef  int /*<<< orphan*/  PropertyStorage_impl ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  PropertyStorage_WritePropertyToStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtrToUlong (void const*) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (void*) ; 

__attribute__((used)) static BOOL PropertyStorage_PropertiesWriter(const void *key, const void *value,
 void *extra, void *closure)
{
    PropertyStorage_impl *This = extra;
    struct PropertyClosure *c = closure;

    assert(key);
    assert(value);
    assert(extra);
    assert(closure);
    c->hr = PropertyStorage_WritePropertyToStream(This, c->propNum++,
                                                  PtrToUlong(key), value, c->sectionOffset);
    return SUCCEEDED(c->hr);
}