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
#define  HASH_BINARY 131 
#define  HASH_INT 130 
#define  HASH_POINTER 129 
#define  HASH_STRING 128 
 int /*<<< orphan*/  assert (int) ; 
 int binHash (void const*,int) ; 
 int intHash (void const*,int) ; 
 int ptrHash (void const*,int) ; 
 int strHash (void const*,int) ; 

__attribute__((used)) static int (*hashFunction(int keyClass))(const void*,int){
#if 0  /* HASH_INT and HASH_POINTER are never used */
  switch( keyClass ){
    case HASH_INT:     return &intHash;
    case HASH_POINTER: return &ptrHash;
    case HASH_STRING:  return &strHash;
    case HASH_BINARY:  return &binHash;;
    default: break;
  }
  return 0;
#else
  if( keyClass==HASH_STRING ){
    return &strHash;
  }else{
    assert( keyClass==HASH_BINARY );
    return &binHash;
  }
#endif
}