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
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  int* PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_E_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  SEC_E_INVALID_TOKEN ; 
 int /*<<< orphan*/  SEC_E_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int decode (char) ; 

SECURITY_STATUS decodeBase64(char *in_buf, int in_len, PBYTE out_buf,
        int max_len, int *out_len)
{
    int len = in_len, i;
    char *d = in_buf;
    int  ip0, ip1, ip2, ip3;

    TRACE("in_len: %d\n", in_len);

    if((in_len % 4) != 0)
        return SEC_E_INVALID_TOKEN;

    if(in_len > max_len)
        return SEC_E_BUFFER_TOO_SMALL;

    i = 0;
    while(len > 4)
    {
        if((ip0 = decode(d[0])) > 63)
            return SEC_E_INVALID_TOKEN;
        if((ip1 = decode(d[1])) > 63)
            return SEC_E_INVALID_TOKEN;
        if((ip2 = decode(d[2])) > 63)
            return SEC_E_INVALID_TOKEN;
        if((ip3 = decode(d[3])) > 63)
            return SEC_E_INVALID_TOKEN;

        out_buf[i + 0] = (ip0 << 2) | (ip1 >> 4);
        out_buf[i + 1] = (ip1 << 4) | (ip2 >> 2);
        out_buf[i + 2] = (ip2 << 6) |  ip3;
        len -= 4;
        i += 3;
        d += 4;
    }

    if(d[2] == '=')
    {
        if((ip0 = decode(d[0])) > 63)
            return SEC_E_INVALID_TOKEN;
        if((ip1 = decode(d[1])) > 63)
            return SEC_E_INVALID_TOKEN;

        out_buf[i] = (ip0 << 2) | (ip1 >> 4);
        i++;
    }
    else if(d[3] == '=')
    {
        if((ip0 = decode(d[0])) > 63)
            return SEC_E_INVALID_TOKEN;
        if((ip1 = decode(d[1])) > 63)
            return SEC_E_INVALID_TOKEN;
        if((ip2 = decode(d[2])) > 63)
            return SEC_E_INVALID_TOKEN;

        out_buf[i + 0] = (ip0 << 2) | (ip1 >> 4);
        out_buf[i + 1] = (ip1 << 4) | (ip2 >> 2);
        i += 2;
    }
    else
    {
        if((ip0 = decode(d[0])) > 63)
            return SEC_E_INVALID_TOKEN;
        if((ip1 = decode(d[1])) > 63)
            return SEC_E_INVALID_TOKEN;
        if((ip2 = decode(d[2])) > 63)
            return SEC_E_INVALID_TOKEN;
        if((ip3 = decode(d[3])) > 63)
            return SEC_E_INVALID_TOKEN;


        out_buf[i + 0] = (ip0 << 2) | (ip1 >> 4);
        out_buf[i + 1] = (ip1 << 4) | (ip2 >> 2);
        out_buf[i + 2] = (ip2 << 6) |  ip3;
        i += 3;
    }
    *out_len = i;
    return SEC_E_OK;
}