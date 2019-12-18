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
 scalar_t__ strncmp (char const*,char const*,int) ; 
 char const* vtablog_skip_whitespace (char const*) ; 

__attribute__((used)) static const char *vtablog_parameter(const char *zTag, int nTag, const char *z){
  z = vtablog_skip_whitespace(z);
  if( strncmp(zTag, z, nTag)!=0 ) return 0;
  z = vtablog_skip_whitespace(z+nTag);
  if( z[0]!='=' ) return 0;
  return vtablog_skip_whitespace(z+1);
}