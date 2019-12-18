#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_4__ {int hmac_running; int /*<<< orphan*/  hmac; int /*<<< orphan*/  fsprg_state; int /*<<< orphan*/  seal; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  FSPRG_GetKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  gcry_md_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int journal_file_hmac_start(JournalFile *f) {
        uint8_t key[256 / 8]; /* Let's pass 256 bit from FSPRG to HMAC */
        assert(f);

        if (!f->seal)
                return 0;

        if (f->hmac_running)
                return 0;

        /* Prepare HMAC for next cycle */
        gcry_md_reset(f->hmac);
        FSPRG_GetKey(f->fsprg_state, key, sizeof(key), 0);
        gcry_md_setkey(f->hmac, key, sizeof(key));

        f->hmac_running = true;

        return 0;
}