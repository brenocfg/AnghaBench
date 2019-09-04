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
typedef  int /*<<< orphan*/  xmlreaderinput ;
struct TYPE_3__ {int allocated; int /*<<< orphan*/  prev_cr; scalar_t__ written; scalar_t__ cur; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ encoded_buffer ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readerinput_alloc (int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static HRESULT init_encoded_buffer(xmlreaderinput *input, encoded_buffer *buffer)
{
    const int initial_len = 0x2000;
    buffer->data = readerinput_alloc(input, initial_len);
    if (!buffer->data) return E_OUTOFMEMORY;

    memset(buffer->data, 0, 4);
    buffer->cur = 0;
    buffer->allocated = initial_len;
    buffer->written = 0;
    buffer->prev_cr = FALSE;

    return S_OK;
}