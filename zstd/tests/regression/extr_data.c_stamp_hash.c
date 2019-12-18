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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  xxhash64; } ;
struct TYPE_5__ {int /*<<< orphan*/  xxhash64; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; TYPE_2__ dict; TYPE_1__ data; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ data_t ;
typedef  int /*<<< orphan*/  XXH64_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  XXH64_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xxh_update_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t stamp_hash(data_t const* const* data) {
    XXH64_state_t state;

    XXH64_reset(&state, 0);
    assert(data != NULL);
    for (; *data != NULL; ++data) {
        data_t const* datum = *data;
        /* We don't care about the URL that we fetch from. */
        /* The path is derived from the name. */
        XXH64_update(&state, datum->name, strlen(datum->name));
        xxh_update_le(&state, datum->data.xxhash64);
        xxh_update_le(&state, datum->dict.xxhash64);
        xxh_update_le(&state, datum->type);
    }
    return XXH64_digest(&state);
}