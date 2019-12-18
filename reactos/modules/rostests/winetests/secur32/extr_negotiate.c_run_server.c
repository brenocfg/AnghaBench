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
struct sspi_data {int /*<<< orphan*/  out_buf; int /*<<< orphan*/  ctxt; int /*<<< orphan*/  in_buf; int /*<<< orphan*/  cred; } ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  TimeStamp ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ AcceptSecurityContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CompleteAuthToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECURITY_NETWORK_DREP ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_COMPLETE_AND_CONTINUE ; 
 scalar_t__ SEC_I_COMPLETE_NEEDED ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static SECURITY_STATUS run_server( struct sspi_data *data, BOOL first )
{
    SECURITY_STATUS ret;
    TimeStamp ttl;
    ULONG attr;

    trace( "running server for the %s time\n", first ? "first" : "second" );

    ret = AcceptSecurityContext( &data->cred, first ? NULL : &data->ctxt,
                                 data->in_buf, 0, SECURITY_NETWORK_DREP,
                                 &data->ctxt, data->out_buf, &attr, &ttl );
    if (ret == SEC_I_COMPLETE_AND_CONTINUE || ret == SEC_I_COMPLETE_NEEDED)
    {
        CompleteAuthToken( &data->ctxt, data->out_buf );
        if (ret == SEC_I_COMPLETE_AND_CONTINUE)
            ret = SEC_I_CONTINUE_NEEDED;
        else if (ret == SEC_I_COMPLETE_NEEDED)
            ret = SEC_E_OK;
    }
    return ret;
}