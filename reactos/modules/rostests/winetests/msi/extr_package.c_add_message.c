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
struct externalui_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct externalui_message* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct externalui_message* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct externalui_message*,int) ; 
 int /*<<< orphan*/  assert (struct externalui_message*) ; 
 struct externalui_message* sequence ; 
 int sequence_count ; 
 int sequence_size ; 

__attribute__((used)) static void add_message(const struct externalui_message *msg)
{
    if (!sequence)
    {
        sequence_size = 10;
        sequence = HeapAlloc(GetProcessHeap(), 0, sequence_size * sizeof(*sequence));
    }
    if (sequence_count == sequence_size)
    {
        sequence_size *= 2;
        sequence = HeapReAlloc(GetProcessHeap(), 0, sequence, sequence_size * sizeof(*sequence));
    }

    assert(sequence);

    sequence[sequence_count++] = *msg;
}