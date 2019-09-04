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
struct TYPE_4__ {scalar_t__ len; scalar_t__ buf; } ;
typedef  TYPE_1__ strbuf_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  jsstr_flush (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_ensure_size (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static HRESULT strbuf_append_jsstr(strbuf_t *buf, jsstr_t *str)
{
    if(!strbuf_ensure_size(buf, buf->len+jsstr_length(str)))
        return E_OUTOFMEMORY;

    jsstr_flush(str, buf->buf+buf->len);
    buf->len += jsstr_length(str);
    return S_OK;
}