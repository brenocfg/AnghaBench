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
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateDummyMedia (size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
CreateDummyMediaArray(input_item_t *out[], size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        out[i] = CreateDummyMedia(i);
        assert(out[i]);
    }
}