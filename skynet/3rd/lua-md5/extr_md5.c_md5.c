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
typedef  scalar_t__ WORD32 ;

/* Variables and functions */
 int converte (scalar_t__*,char const*,int,int) ; 
 int /*<<< orphan*/  digest (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  inic_digest (scalar_t__*) ; 
 int /*<<< orphan*/  put_length (scalar_t__*,long) ; 
 int /*<<< orphan*/  word32tobytes (scalar_t__*,char*) ; 

void md5 (const char *message, long len, char *output) {
  WORD32 d[4];
  int status = 0;
  long i = 0;
  inic_digest(d);
  while (status != 2) {
    WORD32 d_old[4];
    WORD32 wbuff[16];
    int numbytes = (len-i >= 64) ? 64 : len-i;
    /*salva os valores do vetor digest*/
    d_old[0]=d[0]; d_old[1]=d[1]; d_old[2]=d[2]; d_old[3]=d[3];
    status = converte(wbuff, message+i, numbytes, status);
    if (status == 2) put_length(wbuff, len);
    digest(wbuff, d);
    d[0]+=d_old[0]; d[1]+=d_old[1]; d[2]+=d_old[2]; d[3]+=d_old[3];
    i += numbytes;
  }
  word32tobytes(d, output);
}