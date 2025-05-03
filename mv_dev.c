/**
 * @file mv_dev.c
 * @author Mohamed Ibrahem (mohamed.ibrahem2608@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-04-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <fcntl.h>
#include <stdlib.h>

#include "string.h"
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
#define ERROR_CANNT_OPEN -1
#define ERROR_CANNT_CLOSE -1
#define ERROR_CANNT_REMOVE -1

int main(int argc, char *argv[]) { 
	
	if ((argc != 3 || strcmp(argv[1], "--help") == 0)) {
		char *hlp = "invalid command\nmv src_file dest_file \n";
		write(1, hlp, strlen(hlp));
		exit(EXIT_FAILURE);
	
	}
	
	int input_fd;	/** input file descriptor**/
	int output_fd;	/** output file descriptor**/
	int open_flags = O_WRONLY | O_CREAT | O_TRUNC;	/** open flags**/
	mode_t file_perms = 777; /** file permissions**/
	ssize_t num_read;/** number of bytes read**/
	ssize_t num_written;/** number of bytes written**/
	char buf[BUF_SIZE];
	/** open the passed files to handle the full operations**/
	input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1) {
		char *hlp = "invalid src_file\n";
		write(1, hlp, strlen(hlp));
		exit(EXIT_FAILURE);
	}
	output_fd = open(argv[2], open_flags, file_perms);
	if (output_fd == -1) {
		char *hlp = "invalid dest_file\n";
		write(1, hlp, strlen(hlp));
		exit(EXIT_FAILURE);
	}
	/** read the file and write to the destination file**/
	while ((num_read = read(input_fd, buf, sizeof(buf))) > 0) {
		/** write the read bytes to the destination file**/
		num_written = write(output_fd, buf, num_read);
		if (num_written != num_read) {
			char *hlp = "write error\n";
			write(1, hlp, strlen(hlp));
			exit(EXIT_FAILURE);
		}
	}
	/** close the file descriptors**/
	if (close(input_fd) == -1) {
		char *hlp = "close error\n";
		write(1, hlp, strlen(hlp));
		exit(EXIT_FAILURE);
	}
	if (close(output_fd) == -1) {
		char *hlp = "close error\n";
		write(1, hlp, strlen(hlp));
		exit(EXIT_FAILURE);
	}
	/** remove the source file**/
	if (unlink(argv[1]) == -1) {
		char *hlp = "remove error\n";
		write(1, hlp, strlen(hlp));
		exit(EXIT_FAILURE);
	}
	char *hlp = "mv done\n";
	write(1, hlp, strlen(hlp));

	
	exit(EXIT_SUCCESS); }
