/*===[[ START ]]==============================================================*/
#include    "ySEC.h"
#include    "ySEC_priv.h"


static char s [LEN_HUND] = "";
static char s_type       = '4';

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
   sprintf (s, "%42.42s", STR_EMPTY);
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
   sprintf (s, "%65.65s", STR_EMPTY);
   /*---(prefix/ticks)-------------------*/
   s [ 0] = LTRS_UPLOW [rand () % strlen (LTRS_UPLOW)];
   s [ 1] = LTRS_BPUNC [rand () % strlen (LTRS_BPUNC)];
   for (i =  2; i <=  8; ++i)   s [i] = LTRS_TICK [rand () %  strlen (LTRS_TICK)];
   /*---(left)---------------------------*/
   for (i =  9; i <= 28; ++i)      s [i] = LTRS_NUMBER [rand () % strlen (LTRS_NUMBER)];
   for (i = 12; i <= 28; i += 4)   s [i] = '\'';
   for (i =  9; i <= 28; i += 4)   s [i] = LTRS_GREEK  [rand () % strlen (LTRS_GREEK )];
   /*---(center)-------------------------*/
   for (i = 29; i <= 35; ++i)      s [i] = x_fill      [rand () % strlen (x_fill     )];
   a = (rand () %  4) + ((rand () % 2) ? 'a' : 'A');
   s [29 + rand () % 3] = a;
   a = (rand () %  3) + ((rand () % 2) ? 'x' : 'X');
   s [33 + rand () % 3] = a;
   /*---(right)--------------------------*/
   for (i = 36; i <= 55; ++i)      s [i] = LTRS_NUMBER [rand () % strlen (LTRS_NUMBER)];
   for (i = 36; i <= 55; i += 4)   s [i] = '\'';
   /*---(suffix/ticks)-------------------*/
   for (i = 56; i <= 62; ++i)   s [i] = LTRS_TICK [rand () %  strlen (LTRS_TICK)];
   s [63] = LTRS_BPUNC [rand () % strlen (LTRS_BPUNC)];
   s [64] = LTRS_UPLOW [rand () % strlen (LTRS_UPLOW)];
   /*---(subtle change)------------------*/
   s [ 5] = LTRS_GREEK [rand () % strlen (LTRS_GREEK )];
   s [59] = LTRS_GREEK [rand () % strlen (LTRS_GREEK )];
   /*---(saveback)-----------------------*/
   if (a_challenge != NULL)  strlcpy (a_challenge, s, LEN_LONG);
   s_type = '6';
   /*---(complete)-----------------------*/
   return s;
}

char*
ySEC_challenge          (char *a_challenge)
{
   return ysec__challenge_65byte (time (NULL), a_challenge);
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
static char s_judgement  = '-';
static char s_rot        =   0;
static char s_off        =   0;
static char s_pos        =   0;
static char s_rce        = -10;

/*> #define  FAILURE    { s_judgement = 'F';  if (a_phase != NULL)  *a_phase = s_phase;  if (a_judgement != NULL)  *a_judgement = s_judgement;  if (a_position != NULL)  *a_position = s_pos - 1;  return s_rce; }   <*/
#define  FAILURE    { s_judgement = 'F';  return s_rce; }
/*> #define  PARTIAL    {                     if (a_phase != NULL)  *a_phase = s_phase;  if (a_judgement != NULL)  *a_judgement = s_judgement;  if (a_position != NULL)  *a_position = s_pos - 1;  return s_rce; }   <*/
#define  PARTIAL    return s_rce;
#define  UPDATE     if (a_phase != NULL)  *a_phase = s_phase;  if (a_judgement != NULL)  *a_judgement = s_judgement;  if (a_position != NULL)  *a_position = s_pos - 1;

char
ysec__prepare           (char *a_response, char *a_phase, char *a_judgement, char *a_position, char *a_user)
{
   /*---(default save backs)-------------*/
   if (a_phase     != NULL)  *a_phase     = '-';
   if (a_judgement != NULL)  *a_judgement = '-';
   if (a_position  != NULL)  *a_position  = 0;
   if (a_user      != NULL)  strlcpy (a_user, "", LEN_LABEL);
   /*---(initialize globals)-------------*/
   s_phase     = '-';
   s_judgement = 'i';
   s_rot       =   0;
   s_off       =   0;
   s_pos       =   0;
   s_rce       = -10;
   /*---(defense)------------------------*/
   --s_rce;  if (a_response  == NULL)  return s_rce;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__knock             (char *a_response)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_ticks     [LEN_LABEL] = "";
   char        a, b, c, d;
   int         l           =    0;
   /*---(update)-------------------------*/
   s_phase = 'k';
   /*---(prepare)------------------------*/
   strlcpy (x_ticks, a_response, 5);
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
   --s_rce;  if (l <= s_pos)   PARTIAL;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__prefix            (char a_type, char *a_rce, char *a_response, char *a_phase, char *a_judgement, char *a_position)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         = *a_rce;
   char        x_ticks     [LEN_LABEL] = "";
   char        a, b;
   int         l           =    0;
   /*---(update)-------------------------*/
   s_phase = 'p';
   UPDATE;
   /*---(prepare)------------------------*/
   strlcpy (x_ticks, a_response, 7);
   l = strlen (x_ticks);
   /*---(positions)----------------------*/
   switch (a_type) {
   case '4' : a =  6; b = 18;  break;
   case '6' : a = 10; b = 26;  break;
   }
   /*---(eval)---------------------------*/
   --rce;  ++s_pos;  if (l >= s_pos && x_ticks [s_pos - 1] != s [ a])  FAILURE;
   --rce;  if (l <= s_pos)   PARTIAL;
   --rce;  ++s_pos;  if (l >= s_pos && x_ticks [s_pos - 1] != s [ b])  FAILURE;
   /*---(saveback)-----------------------*/
   *a_rce = rce;
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__response_42byte   (char *a_response, char *a_phase, char *a_judgement, char *a_position, char *a_user)
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
   if (a_phase     != NULL)  *a_phase     = '-';
   if (a_judgement != NULL)  *a_judgement = '-';
   if (a_position  != NULL)  *a_position  = 0;
   if (a_user      != NULL)  strlcpy (a_user, "", LEN_LABEL);
   /*---(initialize globals)-------------*/
   s_phase     = '-';
   s_judgement = 'i';
   s_rot       =   0;
   s_off       =   0;
   s_pos       =   0;
   /*---(defense)------------------------*/
   --rce;  if (a_response  == NULL)  return rce;
   /*---(knock)--------------------------*/
   rc = ysec__knock (a_response);
   UPDATE;
   if (rc < 0)  return rc;
   /*---(preparation)--------------------*/
   /*> strlcpy (x_pref, a_response, 7);                                               <* 
    *> x_len = strlen (x_pref);                                                       <*/
   /*---(make sure exact can not match)--*/
   /*> strldchg (x_pref, '+' , '-' , LEN_LABEL);                                      <* 
    *> strldchg (x_pref, '\'', '-' , LEN_LABEL);                                      <*/
   /*---(transform)----------------------*/
   /*> strldchg (x_pref, '.' , '+' , LEN_LABEL);                                      <* 
    *> strldchg (x_pref, ' ' , '\'', LEN_LABEL);                                      <*/
   /*---(unit testing)-------------------*/
   /*> strldchg (x_pref, '¬' , '\'', LEN_LABEL);                                      <* 
    *> strldchg (x_pref, '·' , '\'', LEN_LABEL);                                      <*/
   /*---(knock)--------------------------*/
   /*> s_phase = 'k';                                                                    <* 
    *> UPDATE;                                                                           <* 
    *> --rce;  ++s_pos;  if (x_len >= s_pos && x_pref [s_pos - 1] != s [ 1])  FAILURE;   <* 
    *> --rce;  if (x_len <= s_pos)   PARTIAL;                                            <* 
    *> --rce;  ++s_pos;  if (x_len >= s_pos && x_pref [s_pos - 1] != s [ 4])  FAILURE;   <* 
    *> --rce;  if (x_len <= s_pos)   PARTIAL;                                            <* 
    *> --rce;  ++s_pos;  if (x_len >= s_pos && x_pref [s_pos - 1] != s [37])  FAILURE;   <* 
    *> --rce;  if (x_len <= s_pos)   PARTIAL;                                            <* 
    *> --rce;  ++s_pos;  if (x_len >= s_pos && x_pref [s_pos - 1] != s [40])  FAILURE;   <* 
    *> --rce;  if (x_len <= s_pos)   PARTIAL;                                            <*/
   /*---(prefix)-------------------------*/
   rc = ysec__prefix ('4', &rce, a_response, a_phase, a_judgement, a_position);
   if (rc < 0)  return rc;
   /*> s_phase = 'p';                                                                    <* 
    *> UPDATE;                                                                           <* 
    *> --rce;  ++s_pos;  if (x_len >= s_pos && x_pref [s_pos - 1] != s [ 6])  FAILURE;   <* 
    *> --rce;  if (x_len <= s_pos)   PARTIAL;                                            <* 
    *> --rce;  ++s_pos;  if (x_len >= s_pos && x_pref [s_pos - 1] != s [18])  FAILURE;   <*/
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
   rc = ysec__user (p, s_rot, x_user);
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
   s_judgement = 'Y';
   UPDATE;
   /*---(save back)----------------------*/
   if (a_user != NULL)  strlcpy (a_user, x_user, LEN_LABEL);
   /*---(complete)-----------------------*/
   return 0;
}

char
ysec__response_65byte   (char *a_response, char *a_phase, char *a_judgement, char *a_position, char *a_user)
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
   if (a_phase     != NULL)  *a_phase     = '-';
   if (a_judgement != NULL)  *a_judgement = '-';
   if (a_position  != NULL)  *a_position  = 0;
   if (a_user      != NULL)  strlcpy (a_user, "", LEN_LABEL);
   /*---(initialize globals)-------------*/
   s_phase     = '-';
   s_judgement = 'i';
   s_rot       =   0;
   s_off       =   0;
   s_pos       =   0;
   /*---(defense)------------------------*/
   --rce;  if (a_response  == NULL)  return rce;
   /*---(knock)--------------------------*/
   rc = ysec__knock (a_response);
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
   rc = ysec__user (p, s_rot, x_user);
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
   s_judgement = 'Y';
   UPDATE;
   /*---(save back)----------------------*/
   if (a_user != NULL)  strlcpy (a_user, x_user, LEN_LABEL);
   /*---(complete)-----------------------*/
   return 0;
}

char
ySEC_response           (char *a_response, char *a_phase, char *a_judgement, char *a_position, char *a_user)
{
   return ysec__response_42byte (a_response, a_phase, a_judgement, a_position, a_user);
}

char
ysec__user              (char *a_user, char a_rotate, char *a_true)
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
      snprintf (unit_answer, LEN_RECD, "CODED response   : phase %c, judge %c, s_rot %d, s_off %d, s_pos %2d", s_phase, s_judgement, s_rot, s_off, s_pos);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



