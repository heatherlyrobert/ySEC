/*===[[ START ]]==============================================================*/
#include  "ySEC.h"


char        rc          = 0;



/*====================------------------------------------====================*/
/*===----                             UTILITIES                        ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITIES_______________o (void) {;}

static char      ySEC_ver [200] = "";

char*      /* ---- : return library versioning information -------------------*/
ySEC_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 18);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 18);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 18);
#endif
   snprintf (ySEC_ver, 100, "%s   %s : %s", t, YSEC_VER_NUM, YSEC_VER_TXT);
   return ySEC_ver;
}

char             /* [------] append a new wtmpx record -----------------------*/
ySEC__wtmp         (
      int     a_type,        /* record type (boot, login, user, ...)          */
      int     a_pid,         /* pid of process                                */
      int     a_sid,         /* sid of process                                */
      char    *a_user,       /* user name for process                         */
      char    *a_line)       /* comm line identifier                          */
{
   /*---(locals)-----------+-----------+-*/
   int         f           = 0;
   tUTMP       utmp_recd;
   tUNAME      sys_name;
   tTIMEVAL    curr_time;
   char        id          [5];
   /*---(check file existance)-----------*/
   f  = access (WTMP, W_OK);
   if (f < 0) {
      f = creat (WTMP, 0644);
      if (f < 0) return -1;
      close (f);
   }
   /*---(check file access)--------------*/
   f  = open   (WTMP, O_WRONLY | O_APPEND);
   if (f < 0)    return -2;
   /*---(initialize)---------------------*/
   memset  (&utmp_recd, 0, sizeof (utmp_recd));
   /*---(set time)-----------------------*/
   gettimeofday (&curr_time, NULL);
   utmp_recd.ut_tv.tv_sec  = curr_time.tv_sec;
   utmp_recd.ut_tv.tv_usec = curr_time.tv_usec;
   /*---(basics)-------------------------*/
   utmp_recd.ut_type       = a_type;
   utmp_recd.ut_pid        = a_pid;
   utmp_recd.ut_session    = a_sid;
   strncpy (utmp_recd.ut_name, a_user        , sizeof(utmp_recd.ut_name));
   strncpy (utmp_recd.ut_line, a_line        , sizeof(utmp_recd.ut_line));
   uname   (&sys_name);
   sprintf (utmp_recd.ut_host, "%s, %s", sys_name.nodename, sys_name.release);
   /*---(deal with id)-------------------*/
   if (strcmp (a_line, "-") == 0) {
      strcpy (id, "----");
   } else if (strncmp (a_line, "tty" , 3) == 0) {
      strcpy (id, "c");
      strcat (id, a_line + 3);
   } else if (strncmp (a_line, "pts/", 4) == 0) {
      strcat (id, a_line + strlen (a_line) - 4);
   }
   strncpy (utmp_recd.ut_id  , id            , sizeof(utmp_recd.ut_id  ));
   /*---(write)--------------------------*/
   updwtmp (WTMP, &utmp_recd);
   close   (f);
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] append a new wtmpx record -----------------------*/
ySEC__utmp         (
      int     a_type,        /* record type (boot, login, user, ...)          */
      int     a_pid,         /* pid of process                                */
      int     a_sid,         /* sid of process                                */
      char    *a_user,       /* user name for process                         */
      char    *a_line)       /* comm line identifier                          */
{
   /*---(locals)-----------+-----------+-*/
   int         f           = 0;
   tUTMP       utmp_recd;
   tUNAME      sys_name;
   tTIMEVAL    curr_time;
   char        id          [5];
   /*---(check file existance)-----------*/
   f  = access (UTMP, W_OK);
   if (f < 0) {
      f = creat (UTMP, 0644);
      if (f < 0) return -1;
      close (f);
   }
   /*---(initialize)---------------------*/
   memset  (&utmp_recd, 0, sizeof (utmp_recd));
   /*---(set time)-----------------------*/
   gettimeofday (&curr_time, NULL);
   utmp_recd.ut_tv.tv_sec  = curr_time.tv_sec;
   utmp_recd.ut_tv.tv_usec = curr_time.tv_usec;
   /*---(basics)-------------------------*/
   utmp_recd.ut_type       = a_type;
   utmp_recd.ut_pid        = a_pid;
   utmp_recd.ut_session    = a_sid;
   strncpy (utmp_recd.ut_name, a_user        , sizeof(utmp_recd.ut_name));
   strncpy (utmp_recd.ut_line, a_line        , sizeof(utmp_recd.ut_line));
   uname   (&sys_name);
   sprintf (utmp_recd.ut_host, "%s, %s", sys_name.nodename, sys_name.release);
   /*---(deal with id)-------------------*/
   if (strcmp (a_line, "-") == 0) {
      strcpy (id, "----");
   } else if (strncmp (a_line, "tty", 3) == 0) {
      strcpy (id, "c");
      strcat (id, a_line + 3);
   } else if (strncmp (a_line, "pts/", 4) == 0) {
      strcat (id, a_line + strlen (a_line) - 4);
   }
   strncpy (utmp_recd.ut_id  , id            , sizeof(utmp_recd.ut_id  ));
   /*---(write)--------------------------*/
   setutent  ();
   pututline (&utmp_recd);
   endutent  ();
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] append a new btmpx record -----------------------*/
ySEC__btmp         (
      char    *a_user,       /* user name for process                         */
      char    *a_line)       /* comm line identifier                          */
{
   /*---(locals)-----------+-----------+-*/
   int         f           = 0;
   tUTMP       utmp_recd;
   tUNAME      sys_name;
   tTIMEVAL    curr_time;
   char        id          [5];
   /*---(check file existance)-----------*/
   f  = access (BTMP, W_OK);
   if (f < 0) {
      f = creat (BTMP, 0600);
      if (f < 0) return -1;
      close (f);
   }
   /*---(check file access)--------------*/
   f  = open   (BTMP,  O_WRONLY | O_APPEND);
   if (f < 0)    return -2;
   /*---(initialize)---------------------*/
   memset  (&utmp_recd, 0, sizeof (utmp_recd));
   /*---(set time)-----------------------*/
   gettimeofday (&curr_time, NULL);
   utmp_recd.ut_tv.tv_sec  = curr_time.tv_sec;
   utmp_recd.ut_tv.tv_usec = curr_time.tv_usec;
   /*---(basics)-------------------------*/
   utmp_recd.ut_type       = USER_PROCESS;
   utmp_recd.ut_pid        = 0;
   utmp_recd.ut_session    = 0;
   strncpy (utmp_recd.ut_name, a_user        , sizeof(utmp_recd.ut_name));
   strncpy (utmp_recd.ut_line, a_line        , sizeof(utmp_recd.ut_line));
   uname   (&sys_name);
   sprintf (utmp_recd.ut_host, "%s, %s", sys_name.nodename, sys_name.release);
   /*---(deal with id)-------------------*/
   if (strcmp (a_line, "-") == 0) {
      strcpy (id, "----");
   } else if (strncmp (a_line, "tty" , 3) == 0) {
      strcpy (id, "c");
      strcat (id, a_line + 3);
   } else if (strncmp (a_line, "pts/", 4) == 0) {
      strcat (id, a_line + strlen (a_line) - 4);
   }
   strncpy (utmp_recd.ut_id  , id            , sizeof(utmp_recd.ut_id  ));
   /*---(write)--------------------------*/
   rc = write   (f, &utmp_recd, sizeof (tUTMP));
   close   (f);
   /*---(complete)-----------------------*/
   return errno;
}

char             /* [------] update lastlog record ---------------------------*/
ySEC__lastlog      (
      char    *a_user,       /* user name for process                         */
      char    *a_line)       /* comm line identifier                          */
{
   /*---(locals)-----------+-----------+-*/
   int         f           = 0;
   tLASTLOG    last_recd;
   tUNAME      sys_name;
   tTIMEVAL    curr_time;
   tPASSWD    *pw          = NULL;
   /*---(check file existance)-----------*/
   f  = access (LASTLOG, W_OK);
   if (f < 0) {
      f = creat (LASTLOG, 0644);
      if (f < 0) return -1;
      close (f);
   }
   /*---(check file access)--------------*/
   f  = open   (LASTLOG, O_WRONLY);
   if (f < 0)    return -2;
   /*---(initialize)---------------------*/
   memset  (&last_recd, 0, sizeof (last_recd));
   /*---(get uid)------------------------*/
   pw  = getpwnam (a_user);
   if (pw == NULL) {
      return -3;
   }
   /*---(set time)-----------------------*/
   last_recd.ll_time = time (NULL);
   /*---(basics)-------------------------*/
   strncpy (last_recd.ll_line, a_line        , sizeof(last_recd.ll_line));
   uname   (&sys_name);
   sprintf (last_recd.ll_host, "%-8.8s", sys_name.nodename);
   /*---(write)--------------------------*/
   lseek (f, ((long) pw->pw_uid) * sizeof (tLASTLOG), 0);
   write (f, &last_recd, sizeof (tLASTLOG));
   close (f);
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] create a system reboot/startup record -----------*/
ySEC_startup       (void)
{
   ySEC__wtmp    (BOOT_TIME    , 0, 0, "--- EOS ----------------", "-");
   ySEC__utmp    (BOOT_TIME    , 0, 0, "--- EOS ----------------", "-");
   return 0;
}

char             /* [------] create a system shutdown record -----------------*/
ySEC_shutdown      (void)
{
   ySEC__wtmp    (RUN_LVL      , 0, 0, "---------------- NYX ---", "-");
   ySEC__utmp    (RUN_LVL      , 0, 0, "---------------- NYX ---", "-");
   return 0;
}

char             /* [------] create a getty login record ---------------------*/
ySEC_getty_on      (char *a_line)
{
   ySEC__wtmp    (LOGIN_PROCESS, getpid(), getsid(getpid()), "HESTIA", a_line);
   ySEC__utmp    (LOGIN_PROCESS, getpid(), getsid(getpid()), "HESTIA", a_line);
   return 0;
}

char             /* [------] close a getty login record ----------------------*/
ySEC_getty_off     (char *a_line, int a_pid)
{
   ySEC__wtmp    (DEAD_PROCESS , a_pid, 0, "", a_line);
   ySEC__utmp    (DEAD_PROCESS , a_pid, 0, "", a_line);
   return 0;
}

char             /* [------] create a user record ----------------------------*/
ySEC_login         (char *a_line, char *a_user, int a_pid)
{
   rc = 0;
   rc = ySEC__wtmp    (USER_PROCESS , a_pid, getsid(a_pid), a_user, a_line);
   rc = ySEC__utmp    (USER_PROCESS , a_pid, getsid(a_pid), a_user, a_line);
   rc = ySEC__lastlog (a_user, a_line);
   return rc;
}

char             /* [------] record a failed login ---------------------------*/
ySEC_failed        (char *a_line, char *a_user)
{
   rc = 0;
   rc = ySEC__btmp    (a_user, a_line);
   return rc;
}

char             /* [------] create a user record ----------------------------*/
ySEC_logout        (char *a_line, char *a_user, int a_pid)
{
   ySEC__wtmp    (DEAD_PROCESS , a_pid, 0, a_user, a_line);
   ySEC__utmp    (DEAD_PROCESS , a_pid, 0, a_user, a_line);
   return 0;
}







/*===[[ END ]]================================================================*/
