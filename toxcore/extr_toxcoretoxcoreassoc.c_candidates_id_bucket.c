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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  bucket_t ;
struct TYPE_3__ {int /*<<< orphan*/  candidates_bucket_bits; } ;
typedef  TYPE_1__ Assoc ;

/* Variables and functions */
 int /*<<< orphan*/  id_bucket (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bucket_t candidates_id_bucket(const Assoc *assoc, const uint8_t *id)
{
    return id_bucket(id, assoc->candidates_bucket_bits);
}