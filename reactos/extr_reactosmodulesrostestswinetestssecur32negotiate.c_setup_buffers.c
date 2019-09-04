#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sspi_data {int max_token; TYPE_2__* out_buf; TYPE_1__* in_buf; } ;
struct TYPE_9__ {int cbBuffer; void* pvBuffer; void* BufferType; } ;
struct TYPE_8__ {int cbMaxToken; } ;
struct TYPE_7__ {int cBuffers; TYPE_4__* pBuffers; void* ulVersion; } ;
struct TYPE_6__ {int cBuffers; TYPE_4__* pBuffers; void* ulVersion; } ;
typedef  TYPE_3__ SecPkgInfoA ;
typedef  int /*<<< orphan*/  SecBufferDesc ;
typedef  TYPE_4__ SecBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* SECBUFFER_TOKEN ; 
 void* SECBUFFER_VERSION ; 

__attribute__((used)) static void setup_buffers( struct sspi_data *data, SecPkgInfoA *info )
{
    SecBuffer *buffer = HeapAlloc( GetProcessHeap(), 0, sizeof(SecBuffer) );

    data->in_buf  = HeapAlloc( GetProcessHeap(), 0, sizeof(SecBufferDesc) );
    data->out_buf = HeapAlloc( GetProcessHeap(), 0, sizeof(SecBufferDesc) );
    data->max_token = info->cbMaxToken;

    data->in_buf->ulVersion = SECBUFFER_VERSION;
    data->in_buf->cBuffers  = 1;
    data->in_buf->pBuffers  = buffer;

    buffer->cbBuffer   = info->cbMaxToken;
    buffer->BufferType = SECBUFFER_TOKEN;
    buffer->pvBuffer   = HeapAlloc( GetProcessHeap(), 0, info->cbMaxToken );

    buffer = HeapAlloc( GetProcessHeap(), 0, sizeof(SecBuffer) );

    data->out_buf->ulVersion = SECBUFFER_VERSION;
    data->out_buf->cBuffers  = 1;
    data->out_buf->pBuffers  = buffer;

    buffer->cbBuffer   = info->cbMaxToken;
    buffer->BufferType = SECBUFFER_TOKEN;
    buffer->pvBuffer   = HeapAlloc( GetProcessHeap(), 0, info->cbMaxToken );
}