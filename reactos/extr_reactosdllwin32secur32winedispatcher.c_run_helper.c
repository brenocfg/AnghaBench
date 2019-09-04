#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* com_buf; int /*<<< orphan*/  pipe_out; } ;
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  TYPE_1__* PNegoHelper ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,unsigned int,int) ; 
 int /*<<< orphan*/  SEC_E_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  SEC_E_ILLEGAL_MESSAGE ; 
 int /*<<< orphan*/  SEC_E_INVALID_TOKEN ; 
 int /*<<< orphan*/  SEC_E_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  preserve_unused (TYPE_1__*,int) ; 
 int /*<<< orphan*/  read_line (TYPE_1__*,int*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

SECURITY_STATUS run_helper(PNegoHelper helper, char *buffer,
        unsigned int max_buflen, int *buflen)
{
    int offset_len;
    SECURITY_STATUS sec_status = SEC_E_OK;

    TRACE("In helper: sending %s\n", debugstr_a(buffer));

    /* buffer + '\n' */
    write(helper->pipe_out, buffer, lstrlenA(buffer));
    write(helper->pipe_out, "\n", 1);

    if((sec_status = read_line(helper, &offset_len)) != SEC_E_OK)
    {
        return sec_status;
    }
    
    TRACE("In helper: received %s\n", debugstr_a(helper->com_buf));
    *buflen = lstrlenA(helper->com_buf);

    if( *buflen > max_buflen)
    {   
        ERR("Buffer size too small(%d given, %d required) dropping data!\n",
                max_buflen, *buflen);
        return SEC_E_BUFFER_TOO_SMALL;
    }

    if( *buflen < 2 )
    {
        return SEC_E_ILLEGAL_MESSAGE;
    }

    /* We only get ERR if the input size is too big. On a GENSEC error,
     * ntlm_auth will return BH */
    if(strncmp(helper->com_buf, "ERR", 3) == 0)
    {
        return SEC_E_INVALID_TOKEN;
    }

    memcpy(buffer, helper->com_buf, *buflen+1);

    sec_status = preserve_unused(helper, offset_len);
    
    return sec_status;
}