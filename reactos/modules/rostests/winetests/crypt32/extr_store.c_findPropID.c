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
struct CertPropIDHeader {int cb; int propID; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static const struct CertPropIDHeader *findPropID(const BYTE *buf, DWORD size,
 DWORD propID)
{
    const struct CertPropIDHeader *ret = NULL;
    BOOL failed = FALSE;

    while (size && !ret && !failed)
    {
        if (size < sizeof(struct CertPropIDHeader))
            failed = TRUE;
        else
        {
            const struct CertPropIDHeader *hdr =
             (const struct CertPropIDHeader *)buf;

            size -= sizeof(struct CertPropIDHeader);
            buf += sizeof(struct CertPropIDHeader);
            if (size < hdr->cb)
                failed = TRUE;
            else if (hdr->propID == propID)
                ret = hdr;
            else
            {
                buf += hdr->cb;
                size -= hdr->cb;
            }
        }
    }
    return ret;
}