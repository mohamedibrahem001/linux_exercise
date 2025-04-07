/**
 * @file pwd_dev.c
 * @author Mohamed Ibrahem (mohamed.ibrahem2608@gmail.com)
 * @brief
 * This program implements a simple version of the Unix command "pwd" (print
 * working directory).
 * @version 0.1
 * @date 2025-04-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "string.h"
#include <stdlib.h>
#include <unistd.h>

#define STDIN_FILE_DESC 0
#define STDOUT_FILE_DESC 1
#define STDERR_FILE_DESC 2

#define MAX_SIZE 1024
char buffer[MAX_SIZE];

int main(int argc, char *argv[]) {
  int output_fd; /** output file descriptor**/
  /* check if there is any arguments passed   */
  if (argc > 1) {

    if (strcmp(argv[1], "--help") == 0) {
      char msg[] = "Usage :\n  \'pwd \'  \n";
      write(STDOUT_FILE_DESC, msg, sizeof(msg));
      exit(EXIT_FAILURE);
    }
  } else {
    /** get the current working directory  **/
    char *status = getcwd(buffer, MAX_SIZE);
    if (status == NULL) {
      write(STDOUT_FILE_DESC, "Error: getcwd failed\n", 20);
      exit(EXIT_FAILURE);
    }
    output_fd = write(STDOUT_FILE_DESC, buffer, strlen(buffer));
    if (output_fd == -1) {
      exit(EXIT_FAILURE);
    }
    write(STDOUT_FILE_DESC, " ", 1);
    if (output_fd == -1) {
      exit(EXIT_FAILURE);
    }

    output_fd = write(1, "\n", 1);
  }
  exit(EXIT_SUCCESS);
}