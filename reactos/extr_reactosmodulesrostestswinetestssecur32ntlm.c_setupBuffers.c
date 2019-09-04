#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int cbBuffer; int /*<<< orphan*/ * pvBuffer; void* BufferType; } ;
struct TYPE_11__ {int cbMaxToken; } ;
struct TYPE_10__ {int max_token; TYPE_2__* out_buf; TYPE_1__* in_buf; } ;
struct TYPE_9__ {int cBuffers; TYPE_5__* pBuffers; void* ulVersion; } ;
struct TYPE_8__ {int cBuffers; TYPE_5__* pBuffers; void* ulVersion; } ;
typedef  TYPE_3__ SspiData ;
typedef  TYPE_4__ SecPkgInfoA ;
typedef  int /*<<< orphan*/  SecBufferDesc ;
typedef  int /*<<< orphan*/  SecBuffer ;
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  TYPE_5__* PSecBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* SECBUFFER_TOKEN ; 
 void* SECBUFFER_VERSION ; 
 int /*<<< orphan*/  SEC_E_INSUFFICIENT_MEMORY ; 
 int /*<<< orphan*/  SEC_E_OK ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static SECURITY_STATUS setupBuffers(SspiData *sspi_data, SecPkgInfoA *sec_pkg_info)
{
    
    sspi_data->in_buf  = HeapAlloc(GetProcessHeap(), 0, sizeof(SecBufferDesc));
    sspi_data->out_buf = HeapAlloc(GetProcessHeap(), 0, sizeof(SecBufferDesc));
    sspi_data->max_token = sec_pkg_info->cbMaxToken;

    if(sspi_data->in_buf != NULL)
    {
        PSecBuffer sec_buffer = HeapAlloc(GetProcessHeap(), 0,
                sizeof(SecBuffer));
        if(sec_buffer == NULL){
            trace("in_buf: sec_buffer == NULL\n");
            return SEC_E_INSUFFICIENT_MEMORY;
        }
        
        sspi_data->in_buf->ulVersion = SECBUFFER_VERSION;
        sspi_data->in_buf->cBuffers = 1;
        sspi_data->in_buf->pBuffers = sec_buffer;

        sec_buffer->cbBuffer = sec_pkg_info->cbMaxToken;
        sec_buffer->BufferType = SECBUFFER_TOKEN;
        if((sec_buffer->pvBuffer = HeapAlloc(GetProcessHeap(), 0, 
                        sec_pkg_info->cbMaxToken)) == NULL)
        {
            trace("in_buf: sec_buffer->pvBuffer == NULL\n");
            return SEC_E_INSUFFICIENT_MEMORY;
        }
    }
    else
    {
        trace("HeapAlloc in_buf returned NULL\n");
        return SEC_E_INSUFFICIENT_MEMORY;
    }
    
    if(sspi_data->out_buf != NULL)
    {
        PSecBuffer sec_buffer = HeapAlloc(GetProcessHeap(), 0,
                sizeof(SecBuffer));
        
        if(sec_buffer == NULL){
            trace("out_buf: sec_buffer == NULL\n");
            return SEC_E_INSUFFICIENT_MEMORY;
        }

        sspi_data->out_buf->ulVersion = SECBUFFER_VERSION;
        sspi_data->out_buf->cBuffers = 1;
        sspi_data->out_buf->pBuffers = sec_buffer;

        sec_buffer->cbBuffer = sec_pkg_info->cbMaxToken;
        sec_buffer->BufferType = SECBUFFER_TOKEN;
        if((sec_buffer->pvBuffer = HeapAlloc(GetProcessHeap(), 0, 
                        sec_pkg_info->cbMaxToken)) == NULL){
            trace("out_buf: sec_buffer->pvBuffer == NULL\n");
            return SEC_E_INSUFFICIENT_MEMORY;
        }
    }
    else
    {
        trace("HeapAlloc out_buf returned NULL\n");
        return SEC_E_INSUFFICIENT_MEMORY;
    }

    return SEC_E_OK;
}