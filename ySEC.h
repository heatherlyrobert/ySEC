/*============================[[    beg-code    ]]============================*/

/*===[[ HEADER ]]=============================================================*/

/*   focus         : SA          (system_admin)
 *   niche         : sl          (security_logging)
 *   heritage      : aeolus-hippotades (reiner and keeper of the winds)
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



/*===[[ PUBLIC FUNCTIONS ]]===============================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/

/*---(overall)--------------*/
char*       ySEC_version            (void);
/*---(system)---------------*/
char        ySEC_startup            (void);
char        ySEC_shutdown           (void);
/*---(getty)----------------*/
char        ySEC_watch              (char *a_line);
char        ySEC_ignore             (char *a_line, int a_pid);
/*---(logins)---------------*/
char        ySEC_login              (char *a_line, char *a_user, int a_pid);
char        ySEC_failed             (char *a_line, char *a_user);    
char        ySEC_logout             (char *a_line, char *a_user, int a_pid);
/*---(hestia)---------------*/
char        ySEC_request            (char *a_dev, int a_rpid, int a_timeout, int a_lockout, char a_hint, char *a_challenge);
char        ySEC_active             (int a_rpid, char *a_response, char a_phase, char a_judge, char a_status, char a_result, char *a_user);
char        ySEC_complete           (int a_rpid, char a_good);
/*---(codes)----------------*/
char*       ySEC_challenge          (char *a_challenge);
char        ySEC_response           (char *a_response, char *a_phase, char *a_judgement, char *a_position, char *a_user);
/*---(tty)------------------*/
char        ySEC_valid              (char *a_dev);
char        ySEC_open               (char *a_dev, int *a_fd, char a_std, char a_keep);
char        ySEC_close              (int *a_fd);
char        ySEC_noecho             (int a_fd);
char        ySEC_clear              (int a_fd);


#endif

/*===[[ END ]]================================================================*/
