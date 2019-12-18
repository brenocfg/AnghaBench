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
struct sltg_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_index (struct sltg_data*,char const*) ; 
 int /*<<< orphan*/  init_sltg_data (struct sltg_data*) ; 

__attribute__((used)) static void init_index(struct sltg_data *index)
{
    static const char compobj[] = { 1,'C','o','m','p','O','b','j',0 };

    init_sltg_data(index);

    add_index(index, compobj);
}