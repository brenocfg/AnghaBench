#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {unsigned int buf; } ;
struct TYPE_3__ {unsigned int buf; } ;

/* Variables and functions */
#define  JSSTR_HEAP 130 
#define  JSSTR_INLINE 129 
#define  JSSTR_ROPE 128 
 TYPE_2__* jsstr_as_heap (int /*<<< orphan*/ *) ; 
 TYPE_1__* jsstr_as_inline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_as_rope (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_rope_extract (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int jsstr_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

void jsstr_extract(jsstr_t *str, unsigned off, unsigned len, WCHAR *buf)
{
    switch(jsstr_tag(str)) {
    case JSSTR_INLINE:
        memcpy(buf, jsstr_as_inline(str)->buf+off, len*sizeof(WCHAR));
        return;
    case JSSTR_HEAP:
        memcpy(buf, jsstr_as_heap(str)->buf+off, len*sizeof(WCHAR));
        return;
    case JSSTR_ROPE:
        jsstr_rope_extract(jsstr_as_rope(str), off, len, buf);
        return;
    }
}