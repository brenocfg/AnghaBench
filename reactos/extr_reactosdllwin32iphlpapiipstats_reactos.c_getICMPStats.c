#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {void* dwAddrMaskReps; void* dwAddrMasks; void* dwTimestampReps; void* dwTimestamps; void* dwEchoReps; void* dwRedirects; void* dwSrcQuenchs; void* dwParmProbs; void* dwTimeExcds; void* dwDestUnreachs; void* dwErrors; void* dwMsgs; } ;
struct TYPE_7__ {void* dwAddrMaskReps; void* dwAddrMasks; void* dwTimestampReps; void* dwTimestamps; void* dwEchoReps; void* dwRedirects; void* dwSrcQuenchs; void* dwParmProbs; void* dwTimeExcds; void* dwDestUnreachs; void* dwErrors; void* dwMsgs; } ;
struct TYPE_9__ {TYPE_2__ icmpOutStats; TYPE_1__ icmpInStats; } ;
struct TYPE_10__ {TYPE_3__ stats; } ;
typedef  TYPE_4__ MIB_ICMP ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  NO_ERROR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncasecmp (char*,char const*,int) ; 
 void* strtoul (char*,char**,int) ; 

DWORD getICMPStats(MIB_ICMP *stats)
{
  FILE *fp;

  if (!stats)
    return ERROR_INVALID_PARAMETER;

  memset(stats, 0, sizeof(MIB_ICMP));
  /* get most of these stats from /proc/net/snmp, no error if can't */
  fp = fopen("/proc/net/snmp", "r");
  if (fp) {
    const char hdr[] = "Icmp:";
    char buf[512] = { 0 }, *ptr;

    do {
      ptr = fgets(buf, sizeof(buf), fp);
    } while (ptr && strncasecmp(buf, hdr, sizeof(hdr) - 1));
    if (ptr) {
      /* last line was a header, get another */
      ptr = fgets(buf, sizeof(buf), fp);
      if (ptr && strncasecmp(buf, hdr, sizeof(hdr) - 1) == 0) {
        char *endPtr;

        ptr += sizeof(hdr);
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwMsgs = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwErrors = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwDestUnreachs = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwTimeExcds = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwParmProbs = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwSrcQuenchs = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwRedirects = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwEchoReps = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwTimestamps = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwTimestampReps = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwAddrMasks = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpInStats.dwAddrMaskReps = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwMsgs = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwErrors = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwDestUnreachs = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwTimeExcds = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwParmProbs = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwSrcQuenchs = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwRedirects = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwEchoReps = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwTimestamps = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwTimestampReps = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwAddrMasks = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
        if (ptr && *ptr) {
          stats->stats.icmpOutStats.dwAddrMaskReps = strtoul(ptr, &endPtr, 10);
          ptr = endPtr;
        }
      }
    }
    fclose(fp);
  }
  return NO_ERROR;
}