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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_3__ {int /*<<< orphan*/  out_buf; int /*<<< orphan*/  ctxt; int /*<<< orphan*/  in_buf; int /*<<< orphan*/  cred; } ;
typedef  TYPE_1__ SspiData ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_COMPLETE_AND_CONTINUE ; 
 scalar_t__ SEC_I_COMPLETE_NEEDED ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 scalar_t__ pAcceptSecurityContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pCompleteAuthToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static SECURITY_STATUS runServer(SspiData *sspi_data, BOOL first, ULONG data_rep)
{
    SECURITY_STATUS ret;
    ULONG ctxt_attr;
    TimeStamp ttl;

    trace("Running the server the %s time\n", first?"first":"second");

    ret = pAcceptSecurityContext(&sspi_data->cred, first?NULL:&sspi_data->ctxt,
            sspi_data->in_buf, 0, data_rep, &sspi_data->ctxt,
            sspi_data->out_buf, &ctxt_attr, &ttl);

    if(ret == SEC_I_COMPLETE_AND_CONTINUE || ret == SEC_I_COMPLETE_NEEDED)
    {
        pCompleteAuthToken(&sspi_data->ctxt, sspi_data->out_buf);
        if(ret == SEC_I_COMPLETE_AND_CONTINUE)
            ret = SEC_I_CONTINUE_NEEDED;
        else if(ret == SEC_I_COMPLETE_NEEDED)
            ret = SEC_E_OK;
    }

    return ret;
}