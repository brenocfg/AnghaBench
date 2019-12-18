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
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ pageSize ; 
 int /*<<< orphan*/  print_decode_line (unsigned char*,int,int,char*) ; 
 unsigned char* read_content (scalar_t__,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void print_page(int iOfst){
  unsigned char *aData;
  char zTitle[50];
  aData = read_content(pageSize+8, iOfst);
  sprintf(zTitle, "page number for page at offset %d", iOfst);
  print_decode_line(aData-iOfst, iOfst, 4, zTitle);
  free(aData);
}