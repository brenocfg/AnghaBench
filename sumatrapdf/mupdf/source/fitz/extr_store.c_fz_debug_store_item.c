#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size; TYPE_2__* val; int /*<<< orphan*/  key; TYPE_1__* type; } ;
typedef  TYPE_3__ fz_item ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int refs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* format_key ) (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_debug_store_item(fz_context *ctx, void *state, void *key_, int keylen, void *item_)
{
	unsigned char *key = key_;
	fz_item *item = item_;
	int i;
	char buf[256];
	fz_unlock(ctx, FZ_LOCK_ALLOC);
	item->type->format_key(ctx, buf, sizeof buf, item->key);
	fz_lock(ctx, FZ_LOCK_ALLOC);
	printf("hash[");
	for (i=0; i < keylen; ++i)
		printf("%02x", key[i]);
	printf("][refs=%d][size=%d] key=%s val=%p\n", item->val->refs, (int)item->size, buf, (void *)item->val);
}