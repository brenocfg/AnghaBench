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
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 unsigned char FC_CONSTANT_IID ; 
 unsigned char FC_IP ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static size_t write_ip_tfs(unsigned char *str, size_t *len, const GUID *iid)
{
    size_t off = *len;

    if (str)
    {
        str[*len] = FC_IP;
        str[*len+1] = FC_CONSTANT_IID;
        memcpy(str + *len + 2, iid, sizeof(*iid));
    }
    *len += 2 + sizeof(*iid);

    return off;
}