/*============================[[    beg-code    ]]============================*/

/*===[[ HEADER ]]=============================================================*/

/*   focus         : SA          (system_admin)
 *   niche         : sl          (security_logging)
 *   application   : ySEC        (shared library)
 *   purpose       : provide consistent, standard security logging services
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : ansi-c      (wicked, limitless, universal, and everlasting)
 *   dependencies  : none
 *   size          : small       (less than 2000 slocL)
 * 
 *   author        : the_heatherlys
 *   created       : 2012-08
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 * 
 */
/*===[[ SUMMARY ]]============================================================*/

/*   ySEC is a simple, direct, consistent, and clean shared library to enable
 *   the full, architected system security logging which has become less and
 *   less common in later verions of unix-like system.
 *
 */
/*===[[ PURPOSE ]]============================================================*/

/*   ySEC is a simple, direct, and clear approach to security logging on our
 *   systems that ensures the full, architected system security logging expected
 *   on a unix-like system is done correctly.
 *
 *   the tragedy in modern unix-like systems is that they have become complex
 *   and forgotten their simple, coherent, and secure roots.  in later years
 *   they have grown behemoth security architectures like selinux and pam that
 *   are unmaintainable by ordinary administrators and require specialists just
 *   to make sure they work at all.  most folks just download packaged rules
 *   created by faceless maintainers.  wow.
 *
 *   so, ySEC provides a set of functions for security logging in order to
 *   ensure that the original security capabilities are fully utilized to
 *   support tracing, monitoring, warning, debugging, and maintenance.  it is
 *   designed to take a repetative, tedious, haphazard, neglected, and
 *   error-prone task and make it easy, systematic, shared, consistent, and
 *   maintainable.
 *
 *   ySEC focuses on improving normal security logging capabilities by...
 *     - supporting manditory utmp and wtmp record keeping
 *     - adding back mandatory btmp failure logging
 *     - supporting lastlog statistics
 *     - adding back and enhancing sulog records
 *     - adding additional, parallel logging to test internal consistency
 *
 *   many existing libraries and utilities have been built by better programmers
 *   which are likely superior in speed, size, capability, and reliability; BUT,
 *   i would not have learned nearly as much using them, so i follow the adage...
 *
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 *
 */
/*===[[ CRITICAL FILES ]]=====================================================*/

/*   /var/log/wtmp     (some call this wtmpx, or store in /var/adm/)
 *      this file is the most important of the user logging files as it records
 *      boot, shutdown, login, and logout for historical records.  it must be
 *      writable only by root, but readable by others for reporting -- that
 *      means it is owned by root:root and set to 0644.
 *
 *   /var/run/utmp     (some call this utmpx, or store in /etc/)
 *      this file shows a summary of the current situation on the machine --
 *      meaning last boot and who is monitoring which lines.  it must be
 *      writable only by root, but readable by others for reporting -- that
 *      means it is owned by root:root and set to 0644.
 *
 *   /var/log/btmp     (some call this btmpx, loginlog, or faillog)
 *      this file shows all failed logins to the system which is critical to
 *      show the build-up to a hack.  it must be writable only by root,
 *      AND NOT-readable by others -- that means it is owned by root:root and
 *      set to 0600.  the reason for caution is that the most common login
 *      mistake is typing the password as the username, this file would then
 *      have the username in plain-text.  ouch.
 *
 *   /var/log/lastlog
 *      this file records the last successful login times and device on the
 *      system for convienence.  it must be writable only by root, but readable
 *      by others for reporting -- that means it is owned by root:root and
 *      set to 0644.
 *
 *   users
 *   last
 *   lastlog
 *
 */
/*===[[ RELATED ]]============================================================*/

/*   who
 *   users
 *   last
 *   lastlog
 *
 */
/*===[[ END HDOC ]]===========================================================*/


#ifndef     YSEC_HGUARD
#define     YSEC_HGUARD       loaded



/*===[[ VERSION ]]========================================*/
/* rapidly evolving version number to aid with visual change confirmation     */
#define     YSEC_VER_NUM       "0.5b"
#define     YSEC_VER_TXT       "moved to make_program makefile enhancement"



/*===[[ HEADERS ]]========================================*/
#include    <stdio.h>             /* printf, scanf                            */
#include    <stdlib.h>            /* exit, system, ...                        */
#include    <sys/unistd.h>        /* fork, execl, getpid, getuid, gethostname */
#include    <string.h>            /* strcat, strcpy, strlen, ...              */

#include    <sys/utsname.h>       /* uname                                    */
#include    <sys/time.h>          /* gettimeofday                             */

#include    <fcntl.h>             /* open                                     */
#include    <sys/stat.h>          /* fstat, umask                             */
#include    <utmp.h>              /* utmp, btmp, wtmp, and lastlog tracking   */
#include    <pwd.h>               /* getpwuid, getpwnam                       */

#include    <errno.h>             /*                                          */

/*===[[ CONSTANTS ]]======================================*/
#define     UTMP             "/var/run/utmp"
#define     WTMP             "/var/log/wtmp"
#define     BTMP             "/var/log/btmp"
#define     SULOG            "/var/log/sulog"
#define     LASTLOG          "/var/log/lastlog"
#define     PASSWD           "/etc/passwd"
#define     SHADOW           "/etc/shadow"
#define     GROUP            "/etc/group"
#define     GSHADOW          "/etc/gshadow"
#define     STTY             "/etc/securetty"
#define     HESTIA           "/var/log/hestia.logging"


/*===[[ TYPES ]]==========================================*/
typedef     const char         cchar;
typedef     long long          llong;
typedef     const int          cint;

typedef     struct utmp        tUTMP;
typedef     struct lastlog     tLASTLOG;
typedef     struct utsname     tUNAME;
typedef     struct timeval     tTIMEVAL;
typedef     struct passwd      tPASSWD;


/*===[[ PUBLIC FUNCTIONS ]]===============================*/

char             /* [------] create a system reboot/startup record -----------*/
ySEC_startup       (void);

char             /* [------] create a system shutdown record -----------------*/
ySEC_shutdown      (void);

char             /* [------] create a getty login record ---------------------*/
ySEC_getty_on      (char *a_line);

char             /* [------] close a getty login record ----------------------*/
ySEC_getty_off     (char *a_line, int a_pid);

char             /* [------] create a user record ----------------------------*/
ySEC_login         (char *a_line, char *a_user, int a_pid);

char             /* [------] record a failed login ---------------------------*/
ySEC_failed        (char *a_line, char *a_user);

char             /* [------] create a user record ----------------------------*/
ySEC_logout        (char *a_line, char *a_user, int a_pid);



#endif

/*===[[ END ]]================================================================*/
