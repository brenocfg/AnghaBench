#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sspi_data {scalar_t__ max_token; TYPE_2__* out_buf; int /*<<< orphan*/  ctxt; int /*<<< orphan*/ * in_buf; int /*<<< orphan*/  cred; } ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_5__ {TYPE_1__* pBuffers; } ;
struct TYPE_4__ {scalar_t__ cbBuffer; scalar_t__ BufferType; } ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CompleteAuthToken (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ InitializeSecurityContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SECBUFFER_TOKEN ; 
 int /*<<< orphan*/  SECURITY_NETWORK_DREP ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_COMPLETE_AND_CONTINUE ; 
 scalar_t__ SEC_I_COMPLETE_NEEDED ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static SECURITY_STATUS run_client( struct sspi_data *data, BOOL first )
{
    SECURITY_STATUS ret;
    TimeStamp ttl;
    ULONG attr;

    trace( "running client for the %s time\n", first ? "first" : "second" );

    data->out_buf->pBuffers[0].cbBuffer = data->max_token;
    data->out_buf->pBuffers[0].BufferType = SECBUFFER_TOKEN;

    ret = InitializeSecurityContextA( first ? &data->cred : NULL, first ? NULL : &data->ctxt,
                                      NULL, 0, 0, SECURITY_NETWORK_DREP, first ? NULL : data->in_buf,
                                      0, &data->ctxt, data->out_buf, &attr, &ttl );
    if (ret == SEC_I_COMPLETE_AND_CONTINUE || ret == SEC_I_COMPLETE_NEEDED)
    {
        CompleteAuthToken( &data->ctxt, data->out_buf );
        if (ret == SEC_I_COMPLETE_AND_CONTINUE)
            ret = SEC_I_CONTINUE_NEEDED;
        else if (ret == SEC_I_COMPLETE_NEEDED)
            ret = SEC_E_OK;
    }
    ok( data->out_buf->pBuffers[0].BufferType == SECBUFFER_TOKEN,
        "buffer type changed from SECBUFFER_TOKEN to %u\n", data->out_buf->pBuffers[0].BufferType );
    ok( data->out_buf->pBuffers[0].cbBuffer < data->max_token,
        "InitializeSecurityContext didn't change buffer size\n" );
    return ret;
}