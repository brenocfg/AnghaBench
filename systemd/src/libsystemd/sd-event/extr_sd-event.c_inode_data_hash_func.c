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
struct siphash {int dummy; } ;
struct inode_data {int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct inode_data const*) ; 
 int /*<<< orphan*/  siphash24_compress (int /*<<< orphan*/ *,int,struct siphash*) ; 

__attribute__((used)) static void inode_data_hash_func(const struct inode_data *d, struct siphash *state) {
        assert(d);

        siphash24_compress(&d->dev, sizeof(d->dev), state);
        siphash24_compress(&d->ino, sizeof(d->ino), state);
}