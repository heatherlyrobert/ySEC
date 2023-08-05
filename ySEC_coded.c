/*===[[ START ]]==============================================================*/
#include    "ySEC.h"
#include    "ySEC_priv.h"


static char s [LEN_HUND] = "";
static char s_type       = '4';
static char r [LEN_HUND] = "";

/*  123456789-123456789-123456789-123456789-123456789-123456789-123456789- */
/*> k!'++a'+'a12'b63'c78'd44'e23'aAzJkCa'123'454'454'454'454'++z'+';L                 <*/
/*> '++'+'12'63'78'44'23'AJC'123'454'454'++'+'                                        <*/



/*====================------------------------------------====================*/
/*===----                      challenge generation                    ----===*/
/*====================------------------------------------====================*/
static void      o___CHALLENGE_______________o (void) {;}

char*
ysec__challenge_42byte   (int a_seed, char *a_challenge)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        a, b, c, d;
   char       *t           = "'+";
   /*---(check for testing force)--------*/
   if (a_seed < 0) {
      strlcpy (s, a_challenge, LEN_DESC);
      return s;
   }
   /*---(prepare)------------------------*/
   srand (a_seed);
   sprintf (s, "%42.42s", YSTR_EMPTY);
   for (i =  0; i <=  5; ++i)      s [i] = t [rand () %  2];
   for (i =  6; i <= 19; ++i)      s [i] = (rand () % 10) + '0';
   for (i =  8; i <= 19; i += 3)   s [i] = '\'';
   s [20] = '\'';
   a = (rand () %  4) + ((rand () % 2) ? 'a' : 'A');
   b = (rand () % 19) + ((rand () % 2) ? 'e' : 'E');
   c = (rand () %  3) + ((rand () % 2) ? 'x' : 'X');
   d = rand () % 3;
   switch (d) {
   case 0 : s [21] = a; a = c;  break;
   case 1 : s [21] = b; b = c;  break;
   case 2 : s [21] = c;         break;
   }
   d = rand () % 2;
   switch (d) {
   case 0 : s [22] = a; s [23] = b;  break;
   case 1 : s [22] = b; s [23] = a;  break;
   }
   s [24] = '\'';
   for (i = 25; i <= 35; ++i)      s [i] = (rand () % 10) + '0';
   for (i = 28; i <= 35; i += 4)   s [i] = '\'';
   /*> for (i = 36; i <= 41; ++i)      s [i] = (rand () %  2 == 0) ? '\'' : '+';      <*/
   for (i = 36; i <= 41; ++i)      s [i] = t [rand () %  2];
   /*---(saveback)-----------------------*/
   if (a_challenge != NULL)  strlcpy (a_challenge, s, LEN_DESC);
   s_type = '4';
   /*---(complete)-----------------------*/
   return s;
}

char*
ysec__challenge_65byte   (int a_seed, char *a_challenge)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        a           =    0;
   char       *x_fill      = "efghijklmnopqrstuvwEFGHIJKLMNOPQRSTUVW";
   /*---(check for testing force)--------*/
   if (a_seed < 0) {
      strlcpy (s, a_challenge, LEN_LONG);
      return s;
   }
   /*---(prepare)------------------------*/
   srand (a_seed);
   sprintf (s, "%65.65s", YSTR_EMPTY);
   /*---(prefix/ticks)-------------------*/
   s [ 0] = YSTR_UPLOW [rand () % strlen (YSTR_UPLOW)];
   s [ 1] = YSTR_BPUNC [rand () % strlen (YSTR_BPUNC)];
   for (i =  2; i <=  8; ++i)   s [i] = YSTR_TICK [rand () %  strlen (YSTR_TICK)];
   /*---(left)---------------------------*/
   for (i =  9; i <= 28; ++i)      s [i] = YSTR_NUMBER [rand () % strlen (YSTR_NUMBER)];
   for (i = 12; i <= 28; i += 4)   s [i] = '\'';
   for (i =  9; i <= 28; i += 4)   s [i] = YSTR_UPLOW  [rand () % strlen (YSTR_UPLOW )];
   /*---(center)-------------------------*/
   for (i = 29; i <= 35; ++i)      s [i] = x_fill      [rand () % strlen (x_fill     )];
   a = (rand () %  4) + ((rand () % 2) ? 'a' : 'A');
   s [29 + rand () % 3] = a;
   a = (rand () %  3) + ((rand () % 2) ? 'x' : 'X');
   s [33 + rand () % 3] = a;
   /*---(right)--------------------------*/
   for (i = 36; i <= 55; ++i)      s [i] = YSTR_NUMBER [rand () % strlen (YSTR_NUMBER)];
   for (i = 36; i <= 55; i += 4)   s [i] = '\'';
   /*---(suffix/ticks)-------------------*/
   for (i = 56; i <= 62; ++i)   s [i] = YSTR_TICK [rand () %  strlen (YSTR_TICK)];
   s [63] = YSTR_BPUNC [rand () % strlen (YSTR_BPUNC)];
   s [64] = YSTR_UPLOW [rand () % strlen (YSTR_UPLOW)];
   /*---(subtle change)------------------*/
   s [ 5] = YSTR_UPLOW [rand () % strlen (YSTR_UPLOW )];
   s [59] = YSTR_UPLOW [rand () % strlen (YSTR_UPLOW )];
   s [32] = YSTR_FILES [rand () % 64];
   /*---(saveback)-----------------------*/
   if (a_challenge != NULL)  strlcpy (a_challenge, s, LEN_LONG);
   s_type = '6';
   /*---(complete)-----------------------*/
   return s;
}

char*
ySEC_challenge          (char *a_challenge)
{
   return ysec__challenge_42byte (time (NULL), a_challenge);
}

/*> e9e08c5188191113828320077bf41a3cfbed2fbe  /usr/local/include/ySEC.h               <* 
 *> 5d3e2964b320ea875c61b363fa920d51529440ad  /usr/local/lib64/libySEC.so.1.0         <* 
 *> 12dea589649eb7c664b4b8a56031c0cc86c9dbe4  /usr/local/lib64/libySEC.a              <* 
 *> 331b547c6d8a8a079eb951a0b6f5bc91ecf3d31e  /usr/local/lib64/libySEC_debug.so.1.0   <* 
 *> 96bf7d4ffc6cf51bdebca69b8e67b90552c365dc  /usr/local/lib64/libySEC_debug.a        <*/

/*> 123456789-123456789-123456789-123456789-12                                        <*/
/*> '++'+'12'63'78'44'23'AJC'123'454'454'++'+'                                        <*/
/*> '++'23bermem/8testing/454¥                                    <*/

static char s_phase      = '-';
static char s_judge      = '-';
static char s_rot        =   0;
static char s_off        =   0;
static char s_pos        =   0;
static char s_rce        = -10;
static char s_user       [LEN_LABEL] = "";

/*> #define  FAILURE    { s_judge = 'F';  if (a_phase != NULL)  *a_phase = s_phase;  if (a_judge != NULL)  *a_judge = s_judge;  if (a_pos != NULL)  *a_pos = s_pos - 1;  return s_rce; }   <*/
#define  FAILURE    { s_judge = 'F';  return s_rce; }
/*> #define  PARTIAL    {                     if (a_phase != NULL)  *a_phase = s_phase;  if (a_judge != NULL)  *a_judge = s_judge;  if (a_pos != NULL)  *a_pos = s_pos - 1;  return s_rce; }   <*/
#define  PARTIAL    return s_rce;
#define  UPDATE     if (a_phase != NULL)  *a_phase = s_phase;  if (a_judge != NULL)  *a_judge = s_judge;  if (a_pos != NULL)  *a_pos = s_pos - 1;

char
ysec__prepare           (char *a_response, char *a_phase, char *a_judge, char *a_pos, char *a_user)
{
   /*---(default save backs)-------------*/
   if (a_phase != NULL)  *a_phase = '-';
   if (a_judge != NULL)  *a_judge = '-';
   if (a_pos   != NULL)  *a_pos   = 0;
   if (a_user  != NULL)  strlcpy (a_user, "", LEN_LABEL);
   /*---(initialize globals)-------------*/
   s_phase = '-';
   s_judge = 'i';
   s_rot   =   0;
   s_off   =   0;
   s_pos   =   0;
   s_rce   = -10;
   strlcpy (s_user, "", LEN_LABEL);
   /*---(defense)------------------------*/
   --s_rce;  if (a_response  == NULL)  PARTIAL;
   strlcpy (r, a_response, LEN_HUND);
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__prepare_unit      (char a_test, char *a_response, char a_judge)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(prepare)------------------------*/
   rc = ysec__prepare (a_response, NULL, NULL, NULL, NULL);
   /*---(ready test)---------------------*/
   switch (a_test) {
   case 'k' :  s_phase = '-'; s_pos =  0; break;
   case 'p' :  s_phase = 'k'; s_pos =  4; break;
   case 'u' :  s_phase = 'p'; s_pos =  6; break;
   case 'i' :  s_phase = 'u'; s_pos = 14; break;
   case 'c' :  s_phase = 'i'; s_pos = 15; strlcpy (s_user, "yexecer", LEN_LABEL);  break;
   case 's' :  s_phase = 'c'; s_pos = 24; break;
   case 'f' :  s_phase = 's'; s_pos = 27; break;
   default  :  return -1;
   }
   /*---(status)-------------------------*/
   s_judge = a_judge;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__knock             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_ticks     [LEN_LABEL] = "";
   char        a, b, c, d;
   int         l           =    0;
   /*---(quick out)----------------------*/
   --s_rce;  if (s_judge != 'i')  return s_rce;
   --s_rce;  if (s_phase != '-')  return s_rce;
   /*---(update)-------------------------*/
   s_phase = 'k';
   /*---(prepare)------------------------*/
   strlcpy (x_ticks, r, 5);
   l = strlen (x_ticks);
   /*---(make sure exact can not match)--*/
   strldchg (x_ticks, '+' , '-' , LEN_LABEL);
   strldchg (x_ticks, '\'', '-' , LEN_LABEL);
   /*---(transform)----------------------*/
   strldchg (x_ticks, '.' , '+' , LEN_LABEL);
   strldchg (x_ticks, ' ' , '\'', LEN_LABEL);
   /*---(unit testing)-------------------*/
   strldchg (x_ticks, '¬' , '\'', LEN_LABEL);
   strldchg (x_ticks, '·' , '\'', LEN_LABEL);
   /*---(positions)----------------------*/
   switch (s_type) {
   case '4' : a =  1; b =  4; c = 37; d = 40;  break;
   case '6' : a =  3; b =  7; c = 57; d = 61;  break;
   }
   /*---(eval)---------------------------*/
   --s_rce;  ++s_pos;  if (l >= s_pos && x_ticks [s_pos - 1] != s [ a])  FAILURE;
   --s_rce;  if (l <= s_pos)   PARTIAL;
   --s_rce;  ++s_pos;  if (l >= s_pos && x_ticks [s_pos - 1] != s [ b])  FAILURE;
   --s_rce;  if (l <= s_pos)   PARTIAL;
   --s_rce;  ++s_pos;  if (l >= s_pos && x_ticks [s_pos - 1] != s [ c])  FAILURE;
   --s_rce;  if (l <= s_pos)   PARTIAL;
   --s_rce;  ++s_pos;  if (l >= s_pos && x_ticks [s_pos - 1] != s [ d])  FAILURE;
   /*---(ending)-------------------------*/
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__prefix            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_prefix    [LEN_LABEL] = "";
   char        a, b;
   int         l           =    0;
   /*---(quick out)----------------------*/
   --s_rce;  if (s_judge != 'i')  return s_rce;
   --s_rce;  if (s_phase != 'k')  return s_rce;
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(update)-------------------------*/
   s_phase = 'p';
   /*---(prepare)------------------------*/
   strlcpy (x_prefix, r, 7);
   l = strlen (x_prefix);
   /*---(positions)----------------------*/
   switch (s_type) {
   case '4' : a =  6; b = 18;  break;
   case '6' : a = 10; b = 26;  break;
   }
   /*---(eval)---------------------------*/
   --s_rce;  ++s_pos;  if (l >= s_pos && x_prefix [s_pos - 1] != s [ a])  FAILURE;
   --s_rce;  if (l <= s_pos)   PARTIAL;
   --s_rce;  ++s_pos;  if (l >= s_pos && x_prefix [s_pos - 1] != s [ b])  FAILURE;
   /*---(ending)-------------------------*/
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__user              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_user      [LEN_HUND]  = "";
   char        a           =    0;
   char        c           =    0;
   char       *p           = NULL;
   int         l           =    0;
   /*---(quick out)----------------------*/
   --s_rce;  if (s_judge != 'i')  return s_rce;
   --s_rce;  if (s_phase != 'p')  return s_rce;
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(update)-------------------------*/
   s_phase = 'u';
   /*---(figure rotation)----------------*/
   switch (s_type) {
   case '4' : a = 21;  break;
   case '6' : a = 29;  break;
   }
   if      (strchr ("ABCD", s [a + 0]) != NULL)  s_rot = s [a + 0] - 'A' + 1;
   else if (strchr ("abcd", s [a + 0]) != NULL)  s_rot = s [a + 0] - 'a' + 1;
   else if (strchr ("ABCD", s [a + 1]) != NULL)  s_rot = s [a + 1] - 'A' + 1;
   else if (strchr ("abcd", s [a + 1]) != NULL)  s_rot = s [a + 1] - 'a' + 1;
   else if (strchr ("ABCD", s [a + 2]) != NULL)  s_rot = s [a + 2] - 'A' + 1;
   else if (strchr ("abcd", s [a + 2]) != NULL)  s_rot = s [a + 2] - 'a' + 1;
   /*---(find marker)--------------------*/
   c = strldcnt (r, '/', LEN_HUND);
   /*> printf ("%1d  %2d[%s]\n", c, strlen (r), r);                                   <*/
   --s_rce;  if (c < 1)        PARTIAL;
   /*---(copy user name)-----------------*/
   strlcpy (x_user, r + 6, LEN_HUND);
   p = strtok (x_user, "/");
   /*> printf ("      %-10.10s  %-10p  %2d[%s]\n", x_user, p, strlen (p), p);         <*/
   --s_rce;  if (p == NULL)    PARTIAL;
   /*---(check name)---------------------*/
   l = strlen (p);
   s_pos += l;
   rc = ysec__username (p, s_rot, s_user);
   /*> printf ("      %1d  %2d  %2d[%s]\n", s_rot, rc, l, s_user);                    <*/
   --s_rce;  ++s_pos;  if (rc < 0)  FAILURE;
   /*---(ending)-------------------------*/
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__infix             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char       *p           = NULL;
   char        x_infix     [LEN_HUND]  = "";
   char        a           =    0;
   int         l           =    0;
   /*---(quick out)----------------------*/
   --s_rce;  if (s_judge != 'i')  return s_rce;
   --s_rce;  if (s_phase != 'u')  return s_rce;
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(update)-------------------------*/
   s_phase = 'i';
   /*---(prepare)------------------------*/
   switch (s_type) {
   case '4' : a = 13;  break;
   case '6' : a = 19;  break;
   }
   /*---(parse)--------------------------*/
   strlcpy (x_infix, r, LEN_HUND);
   p = strtok (x_infix, "/");
   p = strtok (NULL   , "/");
   --s_rce;  if (p == NULL)    PARTIAL;
   /*---(eval)---------------------------*/
   --s_rce;  ++s_pos;  if (l >= s_pos && x_infix  [s_pos - 1] != s [ a])  FAILURE;
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__pass              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char       *p           = NULL;
   char        x_pass      [LEN_HUND]  = "";
   char        a           =    0;
   char        c           =    0;
   int         l           =    0;
   /*---(quick out)----------------------*/
   --s_rce;  if (s_judge != 'i')  return s_rce;
   --s_rce;  if (s_phase != 'i')  return s_rce;
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(update)-------------------------*/
   s_phase = 'c';
   /*---(find marker)--------------------*/
   c = strldcnt (r, '/', LEN_HUND);
   /*> printf ("%1d  %2d[%s]\n", c, strlen (r), r);                                   <*/
   --s_rce;  if (c < 2)        PARTIAL;
   /*---(copy pass)----------------------*/
   strlcpy (x_pass, r, LEN_HUND);
   p = strtok (x_pass , "/");
   p = strtok (NULL   , "/");
   ++p;
   /*> printf ("      %-10p  %2d[%s]\n", p, strlen (p), p);                           <*/
   --s_rce;  if (p == NULL)    PARTIAL;
   /*---(check pass)---------------------*/
   l = strlen (p);
   s_pos += l;
   rc = ysec__password (s_user, p);
   /*> printf ("      %1d  %2d  %2d[%s]\n", s_rot, rc, l, s_user);                    <*/
   --s_rce;  ++s_pos;  if (rc < 0)  FAILURE;
   /*---(ending)-------------------------*/
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__suffix            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_suffix    [LEN_HUND]  = "";
   char        a, b;
   char        c           =    0;
   char       *p           = NULL;
   int         l           =    0;
   /*---(quick out)----------------------*/
   --s_rce;  if (s_judge != 'i')  return s_rce;
   --s_rce;  if (s_phase != 'c')  return s_rce;
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(update)-------------------------*/
   s_phase = 's';
   /*---(figure offset)------------------*/
   switch (s_type) {
   case '4' : a = 21;  break;
   case '6' : a = 33;  break;
   }
   if      (strchr ("XYZ", s [a + 0]) != NULL)  s_off = s [a + 0] - 'X';
   else if (strchr ("xyz", s [a + 0]) != NULL)  s_off = s [a + 0] - 'x';
   else if (strchr ("XYZ", s [a + 1]) != NULL)  s_off = s [a + 1] - 'X';
   else if (strchr ("xyz", s [a + 1]) != NULL)  s_off = s [a + 1] - 'x';
   else if (strchr ("XYZ", s [a + 2]) != NULL)  s_off = s [a + 2] - 'X';
   else if (strchr ("xyz", s [a + 2]) != NULL)  s_off = s [a + 2] - 'x';
   b = a + ((s_off + 1) * 4);
   /*---(find marker)--------------------*/
   c = strldcnt (r, '/', LEN_HUND);
   /*> printf ("%1d  %2d[%s]\n", c, strlen (r), r);                                   <*/
   --s_rce;  if (c < 2)        PARTIAL;
   /*> printf ("      %2do  %2da  %2db  [%-3.3s]\n", s_off, a, b, s + b);             <*/
   /*---(copy suffix)--------------------*/
   strlcpy (x_suffix, r, LEN_HUND);
   p = strtok (x_suffix, "/");
   p = strtok (NULL    , "/");
   p = strtok (NULL    , "/");
   /*> printf ("      %-10p  %2d[%s]\n", p, strlen (p), p);                           <*/
   --s_rce;  if (p == NULL)    PARTIAL;
   /*---(eval)---------------------------*/
   --s_rce;  ++s_pos;  if (l >= s_pos && p [ 0] != s [b + 0])  FAILURE;
   --s_rce;  if (l <= s_pos)   PARTIAL;
   --s_rce;  ++s_pos;  if (l >= s_pos && p [ 1] != s [b + 1])  FAILURE;
   --s_rce;  if (l <= s_pos)   PARTIAL;
   --s_rce;  ++s_pos;  if (l >= s_pos && p [ 2] != s [b + 2])  FAILURE;
   /*---(ending)-------------------------*/
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__final             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_suffix    [LEN_HUND]  = "";
   char        c           =    0;
   char       *p           = NULL;
   int         l           =    0;
   /*---(quick out)----------------------*/
   --s_rce;  if (s_judge != 'i')  return s_rce;
   --s_rce;  if (s_phase != 's')  return s_rce;
   l = strlen (r);
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(update)-------------------------*/
   s_phase = 'f';
   /*---(find marker)--------------------*/
   c = strldcnt (r, '/', LEN_HUND);
   --s_rce;  if (c < 2)        PARTIAL;
   /*---(copy suffix)--------------------*/
   strlcpy (x_suffix, r, LEN_HUND);
   p = strtok (x_suffix, "/");
   p = strtok (NULL    , "/");
   p = strtok (NULL    , "/");
   --s_rce;  if (p == NULL)    PARTIAL;
   /*---(eval)---------------------------*/
   --s_rce;  ++s_pos;  if (l >= s_pos && (p [ 3] != '¥' && p [ 3] != G_KEY_ESCAPE))   FAILURE;
   s_judge = 'Y';
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__response_42byte   (char *a_response, char *a_phase, char *a_judge, char *a_pos, char *a_user)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(prepare)------------------------*/
   rc = ysec__prepare (a_response, a_phase, a_judge, a_pos, a_user);
   UPDATE;
   if (rc < 0)  return rc;
   /*---(knock)--------------------------*/
   rc = ysec__knock   ();
   UPDATE;
   if (rc < 0)  return rc;
   /*---(prefix)-------------------------*/
   rc = ysec__prefix  ();
   UPDATE;
   if (rc < 0)  return rc;
   /*---(user)---------------------------*/
   rc = ysec__user    ();
   UPDATE;
   if (rc < 0)  return rc;
   if (a_user != NULL)  strlcpy (a_user, s_user, LEN_LABEL);
   /*---(infix)--------------------------*/
   rc = ysec__infix   ();
   UPDATE;
   if (rc < 0)  return rc;
   /*---(password)-----------------------*/
   rc = ysec__pass    ();
   UPDATE;
   if (rc < 0)  return rc;
   /*---(suffix)-------------------------*/
   rc = ysec__suffix  ();
   UPDATE;
   if (rc < 0)  return rc;
   /*---(final)--------------------------*/
   rc = ysec__final   ();
   UPDATE;
   if (rc < 0)  return rc;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__response_65byte   (char *a_response, char *a_phase, char *a_judge, char *a_pos, char *a_user)
{
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        n           =    0;
   char        c           =    0;
   char       *p           = NULL;
   char       *q           = NULL;
   char       *r           = NULL;
   char        x_pref      [LEN_LABEL] = "";
   char        x_user      [LEN_LABEL] = "";
   char        t           [LEN_DESC]  = "";
   char        x_off       =    0;
   /*---(default save backs)-------------*/
   if (a_phase != NULL)  *a_phase = '-';
   if (a_judge != NULL)  *a_judge = '-';
   if (a_pos   != NULL)  *a_pos   = 0;
   if (a_user  != NULL)  strlcpy (a_user, "", LEN_LABEL);
   /*---(initialize globals)-------------*/
   s_phase     = '-';
   s_judge = 'i';
   s_rot       =   0;
   s_off       =   0;
   s_pos       =   0;
   /*---(defense)------------------------*/
   --rce;  if (a_response  == NULL)  return rce;
   /*---(knock)--------------------------*/
   rc = ysec__knock ();
   UPDATE;
   if (rc < 0)  return rc;
   /*---(prefix)-------------------------*/
   s_phase = 'p';
   UPDATE;
   --rce;  ++s_pos;  if (x_len >= s_pos && x_pref [s_pos - 1] != s [ 6])  FAILURE;
   --rce;  if (x_len <= s_pos)   PARTIAL;
   --rce;  ++s_pos;  if (x_len >= s_pos && x_pref [s_pos - 1] != s [18])  FAILURE;
   /*---(user)---------------------------*/
   x_len = strlen (a_response);
   --rce;  if (x_len <= s_pos)   PARTIAL;
   s_phase = 'u';
   UPDATE;
   if      (strchr ("ABCD", s [21]) != NULL)  s_rot = s [21] - 'A' + 1;
   else if (strchr ("abcd", s [21]) != NULL)  s_rot = s [21] - 'a' + 1;
   else if (strchr ("ABCD", s [22]) != NULL)  s_rot = s [22] - 'A' + 1;
   else if (strchr ("abcd", s [22]) != NULL)  s_rot = s [22] - 'a' + 1;
   else if (strchr ("ABCD", s [23]) != NULL)  s_rot = s [23] - 'A' + 1;
   else if (strchr ("abcd", s [23]) != NULL)  s_rot = s [23] - 'a' + 1;
   c = strldcnt (a_response, '/', LEN_DESC);
   --rce;  if (c < 1)        PARTIAL;
   strlcpy (t, a_response + 6, LEN_DESC);
   p = strtok_r (t, "/", &r);
   UPDATE;
   --rce;  if (p == NULL)    PARTIAL;
   x_len = strlen (p);
   s_pos += x_len;
   UPDATE;
   rc = ysec__username (p, s_rot, x_user);
   --rce;  ++s_pos;  if (rc < 0)  FAILURE;
   /*---(infix)--------------------------*/
   p = strtok_r (NULL, "/", &r);
   --rce;  if (p == NULL)    PARTIAL;
   s_phase = 'i';
   UPDATE;
   x_len = strlen (p);
   --rce;  ++s_pos;  if (x_len >= 1 && p [ 0] != s [13])  FAILURE;
   --rce;  if (x_len <= 1)   PARTIAL;
   /*---(password)-----------------------*/
   s_phase = 'c';
   UPDATE;
   c = strldcnt (a_response, '/', LEN_DESC);
   --rce;  if (c < 2)        PARTIAL;
   ++p;
   x_len = strlen (p);
   s_pos += x_len;
   UPDATE;
   rc = ysec__password (x_user, p);
   --rce;  ++s_pos;  if (rc < 0)  FAILURE;
   x_len = strlen (a_response);
   --rce;  if (a_response [x_len - 1] == '/')  PARTIAL;
   /*---(suffix)-------------------------*/
   s_phase = 's';
   UPDATE;
   if      (strchr ("XYZ" , s [21]) != NULL)  s_off = s [21] - 'X';
   else if (strchr ("xyz" , s [21]) != NULL)  s_off = s [21] - 'x';
   else if (strchr ("XYZ" , s [22]) != NULL)  s_off = s [22] - 'X';
   else if (strchr ("xyz" , s [22]) != NULL)  s_off = s [22] - 'x';
   else if (strchr ("XYZ" , s [23]) != NULL)  s_off = s [23] - 'X';
   else if (strchr ("xyz" , s [23]) != NULL)  s_off = s [23] - 'x';
   x_off = 25 + (s_off * 4);
   /*> printf ("suffix     [%-3.3s]\n", s + x_off);                                   <*/
   p = strtok_r (NULL, "/", &r);
   --rce;  if (p == NULL)    PARTIAL;
   /*> printf ("remain   %2d[%s]\n", x_len, p);                                       <*/
   --rce;  ++s_pos;  if (x_len >= s_pos  && p [ 0] != s [x_off + 0])  FAILURE;
   --rce;  if (x_len <= s_pos)   PARTIAL;
   --rce;  ++s_pos;  if (x_len >= s_pos && p [ 1] != s [x_off + 1])  FAILURE;
   --rce;  if (x_len <= s_pos)   PARTIAL;
   --rce;  ++s_pos;  if (x_len >= s_pos && p [ 2] != s [x_off + 2])  FAILURE;
   --rce;  if (x_len <= s_pos)   PARTIAL;
   /*---(final)--------------------------*/
   s_phase = 'f';
   UPDATE;
   --rce;  ++s_pos;  if (x_len >= s_pos && (p [ 3] != '¥' && p [ 3] != G_KEY_ESCAPE))   FAILURE;
   s_judge = 'Y';
   UPDATE;
   /*---(save back)----------------------*/
   if (a_user != NULL)  strlcpy (a_user, x_user, LEN_LABEL);
   /*---(complete)-----------------------*/
   return 0;
}

char
ySEC_response           (char *a_response, char *a_user)
{
   char        rc          =    0;
   rc = ysec__response_42byte (a_response, NULL, NULL, NULL, a_user);
   if (rc < 0)  return -1;
   return 0;
}

char
ySEC_full               (char *a_response, char *a_phase, char *a_judge, char *a_pos, char *a_user)
{
   return ysec__response_42byte (a_response, a_phase, a_judge, a_pos, a_user);
}

char
ysec__username          (char *a_user, char a_rotate, char *a_true)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         j           =    0;
   int         x_len       =    0;
   char        x_user      [LEN_LABEL] = "";
   tPASSWD    *x_pass;
   tSHADOW    *x_shad;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_true != NULL)  strlcpy (a_true, "", LEN_LABEL);
   /*---(defense)------------------------*/
   DEBUG_YEXEC  yLOG_point   ("a_user"    , a_user);
   --rce;  if (a_user == NULL) {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_info    ("a_user"    , a_user);
   DEBUG_YEXEC  yLOG_value   ("a_rotate"  , a_rotate);
   --rce;  if (a_rotate < 0 || a_rotate > 4) {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check size)---------------------*/
   x_len = strlen (a_user);
   DEBUG_USER   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 4) {
      DEBUG_USER   yLOG_note    ("length too short (<4)");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len > 15) {
      DEBUG_USER   yLOG_note    ("length too long (>15)");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(rotate)-------------------------*/
   for (i = 0; i < x_len; ++i) {
      j = i + a_rotate;
      if (j <  x_len) {
         x_user [j] = a_user [i];
      } else {
         x_user [j - x_len] = a_user [i];
      }
   }
   x_user [x_len] = '\0';
   DEBUG_USER   yLOG_info    ("x_user"    , x_user);
   /*---(check for root)-----------------*/
   --rce;  if (strcmp (x_user, "root") == 0) {
      DEBUG_USER   yLOG_note    ("can not log directly into root");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (strcmp (x_user, "kurios") == 0) {
      DEBUG_USER   yLOG_note    ("kurios is the alias of root");
      strcpy (x_user, "root");
      DEBUG_USER   yLOG_info    ("x_user"    , x_user);
   }
   /*---(check)--------------------------*/
   x_pass  = getpwnam (x_user);
   DEBUG_USER   yLOG_point   ("x_pass"   , x_pass);
   if (x_pass == NULL) {
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_shad = getspnam (x_user);
   DEBUG_USER   yLOG_point   ("x_shad"   , x_shad);
   if (x_shad == NULL) {
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   if (a_true != NULL)  strlcpy (a_true, x_user, LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ysec__password           (char *a_user, char *a_pass)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   tSHADOW    *x_shad;
   char       *x_pass      = NULL;
   char       *x_salt      = NULL;
   char       *x_encrypt   = NULL;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YEXEC  yLOG_point   ("a_user"    , a_user);
   --rce;  if (a_user == NULL) {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_info    ("a_user"    , a_user);
   DEBUG_YEXEC  yLOG_point   ("a_pass"    , a_pass);
   --rce;  if (a_pass == NULL) {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_info    ("a_pass"    , a_pass);
   /*---(get user name)------------------*/
   x_len = strlen (a_pass);
   DEBUG_USER   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 4) {
      DEBUG_USER   yLOG_note    ("length too short (<4)");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len > 15) {
      DEBUG_USER   yLOG_note    ("length too long (>15)");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   x_shad = getspnam (a_user);
   DEBUG_USER   yLOG_point   ("x_shad"   , x_shad);
   if (x_shad == NULL) {
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(password)-----------------------*/
   x_pass    = strdup (x_shad->sp_pwdp);
   DEBUG_USER   yLOG_info    ("x_pass"    , x_pass);
   x_salt    = strdup (x_shad->sp_pwdp);
   DEBUG_USER   yLOG_info    ("x_salt"    , x_salt);
   x_encrypt = crypt (a_pass, x_salt);
   DEBUG_USER   yLOG_point   ("x_encrypt" , x_encrypt);
   --rce;  if (strcmp (x_encrypt, x_pass) != 0) {
      free (x_pass);
      free (x_salt);
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free)---------------------------*/
   free (x_pass);
   free (x_salt);
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      unit test accessor                      ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /*--> unit test accessor ------------------------------*/
ysec_coded__unit        (char *a_question)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_heartbeat [LEN_HUND];
   /*---(prepare)------------------------*/
   strlcpy  (unit_answer, "CODED            : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "response"      )  == 0) {
      snprintf (unit_answer, LEN_RECD, "CODED response   : type %c, phase %c, judge %c, s_rot %d, s_off %d, s_pos %2d, s_user %2d[%s]", s_type, s_phase, s_judge, s_rot, s_off, s_pos, strlen (s_user), s_user);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



