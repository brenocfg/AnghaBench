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

__attribute__((used)) static int ofstSerialSize(int scode){
  if( scode<5 ) return scode;
  if( scode==5 ) return 6;
  if( scode<8 ) return 8;
  if( scode<12 ) return 0;
  return (scode-12)/2;
}