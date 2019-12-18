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
struct TYPE_3__ {unsigned int* count; unsigned char const* buffer; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SHA1Context ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Transform (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,unsigned int) ; 

__attribute__((used)) static void hash_step(
  SHA1Context *p,                 /* Add content to this context */
  const unsigned char *data,      /* Data to be added */
  unsigned int len                /* Number of bytes in data */
){
  unsigned int i, j;

  j = p->count[0];
  if( (p->count[0] += len << 3) < j ){
    p->count[1] += (len>>29)+1;
  }
  j = (j >> 3) & 63;
  if( (j + len) > 63 ){
    (void)memcpy(&p->buffer[j], data, (i = 64-j));
    SHA1Transform(p->state, p->buffer);
    for(; i + 63 < len; i += 64){
      SHA1Transform(p->state, &data[i]);
    }
    j = 0;
  }else{
    i = 0;
  }
  (void)memcpy(&p->buffer[j], &data[i], len - i);
}