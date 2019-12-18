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

/* Variables and functions */
 void* cksumNonce ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 void* pageSize ; 
 void* print_decode_line (unsigned char*,int,int,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 unsigned char* read_content (int,int) ; 
 void* sectorSize ; 

__attribute__((used)) static unsigned decode_journal_header(int iOfst){
  unsigned char *pHdr = read_content(64, iOfst);
  unsigned nPage;
  printf("Header at offset %d:\n", iOfst);
  print_decode_line(pHdr, 0, 4, "Header part 1 (3654616569)");
  print_decode_line(pHdr, 4, 4, "Header part 2 (547447767)");
  nPage =
  print_decode_line(pHdr, 8, 4, "page count");
  cksumNonce =
  print_decode_line(pHdr, 12, 4, "chksum nonce");
  print_decode_line(pHdr, 16, 4, "initial database size in pages");
  sectorSize =
  print_decode_line(pHdr, 20, 4, "sector size");
  pageSize =
  print_decode_line(pHdr, 24, 4, "page size");
  print_decode_line(pHdr, 28, 4, "zero");
  print_decode_line(pHdr, 32, 4, "zero");
  print_decode_line(pHdr, 36, 4, "zero");
  print_decode_line(pHdr, 40, 4, "zero");
  free(pHdr);
  return nPage;
}