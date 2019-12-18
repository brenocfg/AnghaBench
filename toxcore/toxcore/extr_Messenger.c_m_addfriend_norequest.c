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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {TYPE_1__* net_crypto; } ;
struct TYPE_6__ {int /*<<< orphan*/  self_public_key; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  FAERR_ALREADYSENT ; 
 int /*<<< orphan*/  FAERR_BADCHECKSUM ; 
 int /*<<< orphan*/  FAERR_OWNKEY ; 
 int /*<<< orphan*/  FRIEND_CONFIRMED ; 
 int getfriend_id (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ id_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_new_friend (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  public_key_valid (int /*<<< orphan*/  const*) ; 

int32_t m_addfriend_norequest(Messenger *m, const uint8_t *real_pk)
{
    if (getfriend_id(m, real_pk) != -1)
        return FAERR_ALREADYSENT;

    if (!public_key_valid(real_pk))
        return FAERR_BADCHECKSUM;

    if (id_equal(real_pk, m->net_crypto->self_public_key))
        return FAERR_OWNKEY;

    return init_new_friend(m, real_pk, FRIEND_CONFIRMED);
}