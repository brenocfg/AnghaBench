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
typedef  enum ExtensionState { ____Placeholder_ExtensionState } ExtensionState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int EXTENSION_STATE_CREATED ; 
 int EXTENSION_STATE_NOT_INSTALLED ; 
 int EXTENSION_STATE_TRANSITIONING ; 
 int EXTENSION_STATE_UNKNOWN ; 
 int /*<<< orphan*/  IsNormalProcessingMode () ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 int /*<<< orphan*/  extension_exists () ; 
 scalar_t__ extension_is_transitioning () ; 
 scalar_t__ proxy_table_exists () ; 

__attribute__((used)) static enum ExtensionState
extension_current_state()
{
	/*
	 * NormalProcessingMode necessary to avoid accessing cache before its
	 * ready (which may result in an infinite loop). More concretely we need
	 * RelationCacheInitializePhase3 to have been already called.
	 */
	if (!IsNormalProcessingMode() || !IsTransactionState())
		return EXTENSION_STATE_UNKNOWN;

	/*
	 * NOTE: do not check for proxy_table_exists here. Want to be in
	 * TRANSITIONING state even before the proxy table is created
	 */
	if (extension_is_transitioning())
		return EXTENSION_STATE_TRANSITIONING;

	/*
	 * proxy_table_exists uses syscache. Must come first. NOTE: during DROP
	 * EXTENSION proxy_table_exists() will return false right away, while
	 * extension_exists will return true until the end of the command
	 */
	if (proxy_table_exists())
	{
		Assert(extension_exists());
		return EXTENSION_STATE_CREATED;
	}

	return EXTENSION_STATE_NOT_INSTALLED;
}