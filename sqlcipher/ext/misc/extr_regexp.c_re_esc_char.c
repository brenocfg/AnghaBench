#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t i; size_t mx; char* z; } ;
struct TYPE_5__ {char* zErr; TYPE_1__ sIn; } ;
typedef  TYPE_2__ ReCompiled ;

/* Variables and functions */
 scalar_t__ re_hex (unsigned char const,int*) ; 

__attribute__((used)) static unsigned re_esc_char(ReCompiled *p){
  static const char zEsc[] = "afnrtv\\()*.+?[$^{|}]";
  static const char zTrans[] = "\a\f\n\r\t\v";
  int i, v = 0;
  char c;
  if( p->sIn.i>=p->sIn.mx ) return 0;
  c = p->sIn.z[p->sIn.i];
  if( c=='u' && p->sIn.i+4<p->sIn.mx ){
    const unsigned char *zIn = p->sIn.z + p->sIn.i;
    if( re_hex(zIn[1],&v)
     && re_hex(zIn[2],&v)
     && re_hex(zIn[3],&v)
     && re_hex(zIn[4],&v)
    ){
      p->sIn.i += 5;
      return v;
    }
  }
  if( c=='x' && p->sIn.i+2<p->sIn.mx ){
    const unsigned char *zIn = p->sIn.z + p->sIn.i;
    if( re_hex(zIn[1],&v)
     && re_hex(zIn[2],&v)
    ){
      p->sIn.i += 3;
      return v;
    }
  }
  for(i=0; zEsc[i] && zEsc[i]!=c; i++){}
  if( zEsc[i] ){
    if( i<6 ) c = zTrans[i];
    p->sIn.i++;
  }else{
    p->zErr = "unknown \\ escape";
  }
  return c;
}