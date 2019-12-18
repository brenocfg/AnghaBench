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
typedef  int /*<<< orphan*/  COVER_ctx_t ;
typedef  void BYTE ;

/* Variables and functions */

__attribute__((used)) static void
COVER_groupBy(const void *data, size_t count, size_t size, COVER_ctx_t *ctx,
              int (*cmp)(COVER_ctx_t *, const void *, const void *),
              void (*grp)(COVER_ctx_t *, const void *, const void *)) {
  const BYTE *ptr = (const BYTE *)data;
  size_t num = 0;
  while (num < count) {
    const BYTE *grpEnd = ptr + size;
    ++num;
    while (num < count && cmp(ctx, ptr, grpEnd) == 0) {
      grpEnd += size;
      ++num;
    }
    grp(ctx, ptr, grpEnd);
    ptr = grpEnd;
  }
}