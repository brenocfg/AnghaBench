#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_10__ {int cBuffers; TYPE_1__* pBuffers; } ;
struct TYPE_9__ {scalar_t__ max_token; int /*<<< orphan*/  ctxt; int /*<<< orphan*/  cred; TYPE_3__* out_buf; TYPE_3__* in_buf; } ;
struct TYPE_8__ {scalar_t__ cbBuffer; scalar_t__ BufferType; int /*<<< orphan*/ * pvBuffer; } ;
typedef  TYPE_2__ SspiData ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  TYPE_3__* PSecBufferDesc ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ SECBUFFER_DATA ; 
 scalar_t__ SECBUFFER_TOKEN ; 
 scalar_t__ SEC_E_BUFFER_TOO_SMALL ; 
 scalar_t__ SEC_E_INTERNAL_ERROR ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_COMPLETE_AND_CONTINUE ; 
 scalar_t__ SEC_I_COMPLETE_NEEDED ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ getSecError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  pCompleteAuthToken (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ pInitializeSecurityContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static SECURITY_STATUS runClient(SspiData *sspi_data, BOOL first, ULONG data_rep)
{
    SECURITY_STATUS ret;
    ULONG req_attr = 0;
    ULONG ctxt_attr;
    TimeStamp ttl;
    PSecBufferDesc in_buf = sspi_data->in_buf;
    PSecBufferDesc out_buf = sspi_data->out_buf;

    assert(in_buf->cBuffers >= 1);
    assert(in_buf->pBuffers[0].pvBuffer != NULL);
    assert(in_buf->pBuffers[0].cbBuffer != 0);

    assert(out_buf->cBuffers >= 1);
    assert(out_buf->pBuffers[0].pvBuffer != NULL);
    assert(out_buf->pBuffers[0].cbBuffer != 0);

    trace("Running the client the %s time.\n", first?"first":"second");

    /* We can either use ISC_REQ_ALLOCATE_MEMORY flag to ask the provider
     * always allocate output buffers for us, or initialize cbBuffer
     * before each call because the API changes it to represent actual
     * amount of data in the buffer.
     */

    /* test a failing call only the first time, otherwise we get
     * SEC_E_OUT_OF_SEQUENCE
     */
    if (first)
    {
        void *old_buf;

        /* pass NULL as an output buffer */
        ret = pInitializeSecurityContextA(&sspi_data->cred, NULL, NULL, req_attr,
            0, data_rep, NULL, 0, &sspi_data->ctxt, NULL,
            &ctxt_attr, &ttl);

        ok(ret == SEC_E_BUFFER_TOO_SMALL, "expected SEC_E_BUFFER_TOO_SMALL, got %s\n", getSecError(ret));

        /* pass NULL as an output buffer */
        old_buf = out_buf->pBuffers[0].pvBuffer;
        out_buf->pBuffers[0].pvBuffer = NULL;

        ret = pInitializeSecurityContextA(&sspi_data->cred, NULL, NULL, req_attr,
            0, data_rep, NULL, 0, &sspi_data->ctxt, out_buf,
            &ctxt_attr, &ttl);

        ok(ret == SEC_E_INTERNAL_ERROR || ret == SEC_I_CONTINUE_NEEDED,
           "expected SEC_E_INTERNAL_ERROR or SEC_I_CONTINUE_NEEDED, got %s\n", getSecError(ret));

        out_buf->pBuffers[0].pvBuffer = old_buf;

        /* pass an output buffer of 0 size */
        out_buf->pBuffers[0].cbBuffer = 0;

        ret = pInitializeSecurityContextA(&sspi_data->cred, NULL, NULL, req_attr,
            0, data_rep, NULL, 0, &sspi_data->ctxt, out_buf,
            &ctxt_attr, &ttl);

        ok(ret == SEC_E_BUFFER_TOO_SMALL, "expected SEC_E_BUFFER_TOO_SMALL, got %s\n", getSecError(ret));

        ok(out_buf->pBuffers[0].cbBuffer == 0,
           "InitializeSecurityContext set buffer size to %u\n", out_buf->pBuffers[0].cbBuffer);

        out_buf->pBuffers[0].cbBuffer = sspi_data->max_token;
        out_buf->pBuffers[0].BufferType = SECBUFFER_DATA;

        ret = pInitializeSecurityContextA(&sspi_data->cred, NULL, NULL, req_attr,
            0, data_rep, NULL, 0, &sspi_data->ctxt, out_buf,
            &ctxt_attr, &ttl);

        ok(ret == SEC_E_BUFFER_TOO_SMALL, "expected SEC_E_BUFFER_TOO_SMALL, got %s\n", getSecError(ret));
        out_buf->pBuffers[0].BufferType = SECBUFFER_TOKEN;
    }

    out_buf->pBuffers[0].cbBuffer = sspi_data->max_token;

    ret = pInitializeSecurityContextA(first?&sspi_data->cred:NULL, first?NULL:&sspi_data->ctxt, NULL, req_attr,
            0, data_rep, first?NULL:in_buf, 0, &sspi_data->ctxt, out_buf,
            &ctxt_attr, &ttl);

    if(ret == SEC_I_COMPLETE_AND_CONTINUE || ret == SEC_I_COMPLETE_NEEDED)
    {
        pCompleteAuthToken(&sspi_data->ctxt, out_buf);
        if(ret == SEC_I_COMPLETE_AND_CONTINUE)
            ret = SEC_I_CONTINUE_NEEDED;
        else if(ret == SEC_I_COMPLETE_NEEDED)
            ret = SEC_E_OK;
    }

    ok(out_buf->pBuffers[0].BufferType == SECBUFFER_TOKEN,
       "buffer type was changed from SECBUFFER_TOKEN to %d\n", out_buf->pBuffers[0].BufferType);
    ok(out_buf->pBuffers[0].cbBuffer < sspi_data->max_token,
       "InitializeSecurityContext set buffer size to %u\n", out_buf->pBuffers[0].cbBuffer);

    return ret;
}