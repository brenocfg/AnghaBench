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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  progdir ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CCP_WIN_A_TO_POSIX ; 
 int CTL_KERN ; 
 int GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 int KERN_PROC ; 
 int KERN_PROC_PATHNAME ; 
 scalar_t__* LUA_DIRSEP ; 
 int /*<<< orphan*/  LUA_EXEC_DIR ; 
 scalar_t__ _NSGetExecutablePath (char*,int*) ; 
 int /*<<< orphan*/  _PATH_MAX ; 
 int /*<<< orphan*/  cygwin_conv_path (int /*<<< orphan*/ ,char*,char*,int) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int getpid () ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_gsub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int readlink (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 
 char* strrchr (char*,int) ; 
 int /*<<< orphan*/  sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setprogdir(lua_State *L) {
  char progdir[_PATH_MAX + 1];
  char *lb;
  int nsize = sizeof(progdir)/sizeof(char);
  int n = 0;
#if defined(__CYGWIN__)
  char win_buff[_PATH_MAX + 1];
  GetModuleFileNameA(NULL, win_buff, nsize);
  cygwin_conv_path(CCP_WIN_A_TO_POSIX, win_buff, progdir, nsize);
  n = strlen(progdir);
#elif defined(_WIN32)
  n = GetModuleFileNameA(NULL, progdir, nsize);
#elif defined(__linux__)
  n = readlink("/proc/self/exe", progdir, nsize);
  if (n > 0) progdir[n] = 0;
#elif defined(__sun)
  pid_t pid = getpid();
  char linkname[256];
  sprintf(linkname, "/proc/%d/path/a.out", pid);
  n = readlink(linkname, progdir, nsize);
  if (n > 0) progdir[n] = 0;  
#elif defined(__FreeBSD__)
  int mib[4];
  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC;
  mib[2] = KERN_PROC_PATHNAME;
  mib[3] = -1;
  size_t cb = nsize;
  sysctl(mib, 4, progdir, &cb, NULL, 0);
  n = cb;
#elif defined(__BSD__)
  n = readlink("/proc/curproc/file", progdir, nsize);
  if (n > 0) progdir[n] = 0;
#elif defined(__APPLE__)
  uint32_t nsize_apple = nsize;
  if (_NSGetExecutablePath(progdir, &nsize_apple) == 0)
    n = strlen(progdir);
#else
  // FALLBACK
  // Use 'lsof' ... should work on most UNIX systems (incl. OSX)
  // lsof will list open files, this captures the 1st file listed (usually the executable)
  int pid;
  FILE* fd;
  char cmd[80];
  pid = getpid();

  sprintf(cmd, "lsof -p %d | awk '{if ($5==\"REG\") { print $9 ; exit}}' 2> /dev/null", pid);
  fd = popen(cmd, "r");
  n = fread(progdir, 1, nsize, fd);
  pclose(fd);

  // remove newline
  if (n > 1) progdir[--n] = '\0';
#endif
  if (n == 0 || n == nsize || (lb = strrchr(progdir, (int)LUA_DIRSEP[0])) == NULL)
    luaL_error(L, "unable to get process executable path");
  else {
    *lb = '\0';
    
    // Replace the relative path placeholder
    luaL_gsub(L, lua_tostring(L, -1), LUA_EXEC_DIR, progdir);
    lua_remove(L, -2);
  }
}