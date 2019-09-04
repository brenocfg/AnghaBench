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
struct TYPE_3__ {int size; scalar_t__* buf; scalar_t__ len; } ;
typedef  TYPE_1__ wstrbuf_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__* heap_alloc (int) ; 

__attribute__((used)) static inline BOOL wstrbuf_init(wstrbuf_t *buf)
{
    buf->len = 0;
    buf->size = 16;
    buf->buf = heap_alloc(buf->size * sizeof(WCHAR));
    if (!buf->buf) return FALSE;
    *buf->buf = 0;
    return TRUE;
}