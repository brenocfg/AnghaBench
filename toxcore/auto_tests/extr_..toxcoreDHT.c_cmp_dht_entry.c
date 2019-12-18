#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hardening; int /*<<< orphan*/  timestamp; } ;
struct TYPE_5__ {int /*<<< orphan*/  hardening; int /*<<< orphan*/  timestamp; } ;
struct TYPE_7__ {int /*<<< orphan*/  public_key; TYPE_2__ assoc6; TYPE_1__ assoc4; } ;
typedef  TYPE_3__ Client_data ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_NODE_TIMEOUT ; 
 scalar_t__ HARDENING_ALL_OK ; 
 int /*<<< orphan*/  cmp_public_key ; 
 scalar_t__ hardening_correct (int /*<<< orphan*/ *) ; 
 int id_closest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,void const*,int) ; 

__attribute__((used)) static int cmp_dht_entry(const void *a, const void *b)
{
    Client_data entry1, entry2;
    memcpy(&entry1, a, sizeof(Client_data));
    memcpy(&entry2, b, sizeof(Client_data));
    int t1 = is_timeout(entry1.assoc4.timestamp, BAD_NODE_TIMEOUT) && is_timeout(entry1.assoc6.timestamp, BAD_NODE_TIMEOUT);
    int t2 = is_timeout(entry2.assoc4.timestamp, BAD_NODE_TIMEOUT) && is_timeout(entry2.assoc6.timestamp, BAD_NODE_TIMEOUT);

    if (t1 && t2)
        return 0;

    if (t1)
        return -1;

    if (t2)
        return 1;

    t1 = hardening_correct(&entry1.assoc4.hardening) != HARDENING_ALL_OK
         && hardening_correct(&entry1.assoc6.hardening) != HARDENING_ALL_OK;
    t2 = hardening_correct(&entry2.assoc4.hardening) != HARDENING_ALL_OK
         && hardening_correct(&entry2.assoc6.hardening) != HARDENING_ALL_OK;

    if (t1 != t2) {
        if (t1)
            return -1;

        if (t2)
            return 1;
    }

    int close = id_closest(cmp_public_key, entry1.public_key, entry2.public_key);

    if (close == 1)
        return 1;

    if (close == 2)
        return -1;

    return 0;
}