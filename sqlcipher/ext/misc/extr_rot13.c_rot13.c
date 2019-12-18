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

__attribute__((used)) static unsigned char rot13(unsigned char c){
  if( c>='a' && c<='z' ){
    c += 13;
    if( c>'z' ) c -= 26;
  }else if( c>='A' && c<='Z' ){
    c += 13;
    if( c>'Z' ) c -= 26;
  }
  return c;
}