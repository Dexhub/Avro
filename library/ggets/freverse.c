/* File freverse.c - testing ggets */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ggets.h"

typedef struct node {
   struct node *next;
   char        *ln;
} node, *nodeptr;

/* ======================= */
/* reverse string in place */
/* return length of string */
size_t revstring(char *stg)
{
   char  *last, temp;
   size_t lgh;

   lgh = strlen(stg);
   if (lgh > 1) {
      last = stg + lgh;        /* points to '\0' */
      while (--last > stg) {
         temp = *stg; *stg++ = *last; *last = temp;
      }
   }
   return lgh;
} /* revstring */

/* ======================= */
/* reverse file            */
int main(void)
{
   char   *line;
   nodeptr root, temp;
   int     lncount, chcount;

   fprintf(stderr, "Reversing stdin to stdout\n");
   root = NULL;
   lncount = chcount = 0;
   while (0 == ggets(&line)) {
      if (NULL == (temp = malloc(sizeof *temp))) {
         fprintf(stderr, "Out of memory\n");
         return EXIT_FAILURE;
      }
      temp->next = root;
      chcount += revstring(line);
      lncount++;
      temp->ln = line;
      root = temp;
   }

   while (root) {
      (void)puts(root->ln);
      temp = root;
      root = root->next;
      free(temp->ln);
      free(temp);
   }
   fprintf(stderr, "%d chars in %d lines\n", chcount, lncount);
   return 0;
} /* main */
/* END freverse.c - testing ggets */
