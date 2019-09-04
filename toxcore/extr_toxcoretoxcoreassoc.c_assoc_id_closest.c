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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  Assoc ;

/* Variables and functions */
 int id_closest (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int assoc_id_closest(const Assoc *assoc, void *callback_data, const uint8_t *client_id,
                            const uint8_t *client_id1, const uint8_t *client_id2)
{
    return id_closest(client_id, client_id1, client_id2);
}