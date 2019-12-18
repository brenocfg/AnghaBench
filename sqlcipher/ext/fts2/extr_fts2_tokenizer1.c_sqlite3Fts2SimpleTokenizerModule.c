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
typedef  int /*<<< orphan*/  sqlite3_tokenizer_module ;

/* Variables and functions */
 int /*<<< orphan*/  simpleTokenizerModule ; 

void sqlite3Fts2SimpleTokenizerModule(
  sqlite3_tokenizer_module const**ppModule
){
  *ppModule = &simpleTokenizerModule;
}