/* spec.c -- read neural network specification
 * copyright (c) 1999-2003 Peter van Rossum
 * $Id: spec.c,v 1.1 2003/09/11 19:22:46 petervr Exp $ */

#include <stdio.h>
#include<conio.h>

#define MAX_LINE_LENGTH   1000

/* Example for a network with 3 inputs and 2 outputs:
 *
 * Specification file:
 *
 * 3           - number of inputs
 * 2           - number of outputs
 * #
 * i0 i1 i2    \ input/target pair
 * t0 t1       /
 * #
 * i3 i4 i5    \ input/target pair
 * t2 t3       /
 * ...
 *
 * Result of calling read_specification:
 *
 * *no_of_inputs = 3
 *
 * *no_of_outputs = 2
 *
 * *no_of_pairs = number of input/target pairs read
 *
 * input[0] input[1] input[2]  input[3] input[4] input[5]  input[6]  ...
 * target[0] target[1]         target[2] target[3]         target[4] ...
 * \------------------------/  \------------------------/  \-------- ...
 *  input/target pair           input/target pair                    
 */

int
read_specification (const char *filename, int *no_of_inputs, int *no_of_outputs,
                    int *no_of_pairs, float *input, float *target)
{
  FILE *file;
  char line[MAX_LINE_LENGTH + 1], *index;
  float *in, *tar;
  int skipped, i;

  file = fopen (filename, "r");
  

  /* sanity check */
  if (file == NULL) {
    fprintf (stderr, "read_specification: can't open %s for reading\n",
             filename);
    return -1;
  }
  

  /* read number of inputs */
  do {
    fgets (line, MAX_LINE_LENGTH, file);
  } while (line[0] == '#');
  sscanf (line, "%i\n", no_of_inputs);

  /* read number of outputs */
  do {
    fgets (line, MAX_LINE_LENGTH, file);
  } while (line[0] == '#');
  sscanf (line, "%i\n", no_of_outputs);

  /* read pairs of data */
  *no_of_pairs = 0;
  in = input;
  tar = target;
  fgets (line, MAX_LINE_LENGTH, file);
  do {
    if (line[0] != '#') {
      /* inputs */
      index = line;
      for (i = 0; i < *no_of_inputs; i++) {
        sscanf (index, "%f%n", in++, &skipped);
        index += skipped;
      }
      /* targets */
      fgets (line, MAX_LINE_LENGTH, file);
      index = line;
      for (i = 0; i < *no_of_outputs; i++) {
        sscanf (index, "%f%n", tar++, &skipped);
        index += skipped;
      }
      /* next pair */
      (*no_of_pairs)++;
    }
    fgets (line, MAX_LINE_LENGTH, file);
  } while (!feof (file));
  return 0;
}
