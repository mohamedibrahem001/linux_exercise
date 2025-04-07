/**
 * @file echo_dev.c
 * @author Mohamed Ibrahem (mohamed.ibrahem2608@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-04-05
 * this program is a simple implementation of the echo command
 * in the shell. it takes a string as an argument and prints it to the standard
 * output.
 * @copyright Copyright (c) 2025
 *
 */
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STDIN_FILE_DESC 0
#define STDOUT_FILE_DESC 1
#define STDERR_FILE_DESC 2

int main(int argc, char *argv[]) {

  int output_fd; /** output file descriptor**/
  /** check if the user passed --help argument to the program */
  if (strcmp(argv[1], "--help") == 0) {
    char msg[] = "Usage :\n  \'echo \"message\" \'  \n";
    write(STDOUT_FILE_DESC, msg, sizeof(msg));
    exit(EXIT_FAILURE);
  }
  /** check if the user passed any arguments to the program */
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      output_fd = write(STDOUT_FILE_DESC, argv[i], strlen(argv[i]));
      if (output_fd == -1) {
        exit(EXIT_FAILURE);
      }
      /**add space if the element is not the last one  */
      if (i < argc - 1) {
        write(STDOUT_FILE_DESC, " ", 1);
        if (output_fd == -1) {
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  /** add new line at the end of the output */
  output_fd = write(1, "\n", 1);

  exit(EXIT_SUCCESS);
}
