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
typedef  int /*<<< orphan*/  path_env ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetEnvironmentVariableW (char const*,char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetEnvironmentVariableW (char const*,char*) ; 
 int /*<<< orphan*/  strcpyW (char*,int /*<<< orphan*/ ) ; 
 int strlenW (char*) ; 

__attribute__((used)) static void set_environment(LPCWSTR bin_path)
{
    WCHAR path_env[MAX_PATH];
    int len;

    static const WCHAR pathW[] = {'P','A','T','H',0};

    /* We have to modify PATH as Mono loads other DLLs from this directory. */
    GetEnvironmentVariableW(pathW, path_env, sizeof(path_env)/sizeof(WCHAR));
    len = strlenW(path_env);
    path_env[len++] = ';';
    strcpyW(path_env+len, bin_path);
    SetEnvironmentVariableW(pathW, path_env);
}