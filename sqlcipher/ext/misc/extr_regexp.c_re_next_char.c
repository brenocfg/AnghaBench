#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t i; size_t mx; unsigned int* z; } ;
typedef  TYPE_1__ ReInput ;

/* Variables and functions */

__attribute__((used)) static unsigned re_next_char(ReInput *p){
  unsigned c;
  if( p->i>=p->mx ) return 0;
  c = p->z[p->i++];
  if( c>=0x80 ){
    if( (c&0xe0)==0xc0 && p->i<p->mx && (p->z[p->i]&0xc0)==0x80 ){
      c = (c&0x1f)<<6 | (p->z[p->i++]&0x3f);
      if( c<0x80 ) c = 0xfffd;
    }else if( (c&0xf0)==0xe0 && p->i+1<p->mx && (p->z[p->i]&0xc0)==0x80
           && (p->z[p->i+1]&0xc0)==0x80 ){
      c = (c&0x0f)<<12 | ((p->z[p->i]&0x3f)<<6) | (p->z[p->i+1]&0x3f);
      p->i += 2;
      if( c<=0x3ff || (c>=0xd800 && c<=0xdfff) ) c = 0xfffd;
    }else if( (c&0xf8)==0xf0 && p->i+3<p->mx && (p->z[p->i]&0xc0)==0x80
           && (p->z[p->i+1]&0xc0)==0x80 && (p->z[p->i+2]&0xc0)==0x80 ){
      c = (c&0x07)<<18 | ((p->z[p->i]&0x3f)<<12) | ((p->z[p->i+1]&0x3f)<<6)
                       | (p->z[p->i+2]&0x3f);
      p->i += 3;
      if( c<=0xffff || c>0x10ffff ) c = 0xfffd;
    }else{
      c = 0xfffd;
    }
  }
  return c;
}