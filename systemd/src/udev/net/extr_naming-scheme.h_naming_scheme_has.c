#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  NamingSchemeFlags ;

/* Variables and functions */
 int FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* naming_scheme () ; 

__attribute__((used)) static inline bool naming_scheme_has(NamingSchemeFlags flags) {
        return FLAGS_SET(naming_scheme()->flags, flags);
}