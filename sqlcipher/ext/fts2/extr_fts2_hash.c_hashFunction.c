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
 int FTS2_HASH_BINARY ; 
 int FTS2_HASH_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int binHash (void const*,int) ; 
 int strHash (void const*,int) ; 

__attribute__((used)) static int (*hashFunction(int keyClass))(const void*,int){
  if( keyClass==FTS2_HASH_STRING ){
    return &strHash;
  }else{
    assert( keyClass==FTS2_HASH_BINARY );
    return &binHash;
  }
}