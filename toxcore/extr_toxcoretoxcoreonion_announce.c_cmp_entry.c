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
struct TYPE_3__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  time; } ;
typedef  TYPE_1__ Onion_Announce_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  ONION_ANNOUNCE_TIMEOUT ; 
 int /*<<< orphan*/  cmp_public_key ; 
 int id_closest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,void const*,int) ; 

__attribute__((used)) static int cmp_entry(const void *a, const void *b)
{
    Onion_Announce_Entry entry1, entry2;
    memcpy(&entry1, a, sizeof(Onion_Announce_Entry));
    memcpy(&entry2, b, sizeof(Onion_Announce_Entry));
    int t1 = is_timeout(entry1.time, ONION_ANNOUNCE_TIMEOUT);
    int t2 = is_timeout(entry2.time, ONION_ANNOUNCE_TIMEOUT);

    if (t1 && t2)
        return 0;

    if (t1)
        return -1;

    if (t2)
        return 1;

    int close = id_closest(cmp_public_key, entry1.public_key, entry2.public_key);

    if (close == 1)
        return 1;

    if (close == 2)
        return -1;

    return 0;
}