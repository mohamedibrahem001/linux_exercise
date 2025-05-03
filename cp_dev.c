/**
 * @file cp_dev.c
 * @author Mohamed Ibrahem (mohamed.ibrahem2608@gmail.com)
 * @brief 
 * This program copies the contents of one file to another.
 * It takes two command line arguments: the source file and the destination file.
 * If the source file does not exist or cannot be opened, an error message is printed.
 * If the destination file cannot be created or opened, an error message is printed.
 * The program reads the source file in chunks and writes the contents to the destination file.
 * If any error occurs during reading or writing, an error message is printed.
 * Finally, the program closes both files and exits.
 * Examaple usage: ./cp src_file dest_file
 * @version 0.1
 * @date 2025-05-03
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
int main(int argc, char *argv[])
{
	int input_fd;	/** input file descriptor**/
	int output_fd;	/** output file descriptor**/
	int open_flags = O_WRONLY | O_CREAT | O_TRUNC;	/** open flags**/

	mode_t file_perms = 777; /** file permissions**/
	ssize_t num_read;/** number of bytes read**/
	ssize_t num_written;/** number of bytes written**/
	char buf[BUF_SIZE];
	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		char *hlp = "invalid command\ncp src_file Dest_file \n";
		output_fd = write(1, hlp, strlen(hlp));
		if (ERROR_CANNT_OPEN == output_fd) {
			exit(EXIT_FAILURE);
		}
	}
	/** open the passed files to handle the full operations**/
	input_fd = open(argv[1], O_RDONLY);

	if (input_fd == -1) {
		char *hlp = "invalid src_file\n";
		output_fd = write(1, hlp, strlen(hlp));
		if (ERROR_CANNT_OPEN == output_fd) {
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
	output_fd = open(argv[2], open_flags, file_perms);
	if (output_fd == -1) {
		char *hlp = "invalid dest_file\n";
		output_fd = write(1, hlp, strlen(hlp));
		if (ERROR_CANNT_OPEN == output_fd) {
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
	/** read the file and write to the destination file**/
	while ((num_read = read(input_fd, buf, BUF_SIZE)) > 0) {
		/** write the read bytes to the destination file**/
		num_written = write(output_fd, buf, num_read);
		if (num_written != num_read) {
			char *hlp = "write error\n";
			output_fd = write(1, hlp, strlen(hlp));
			if (ERROR_CANNT_OPEN == output_fd) {
				exit(EXIT_FAILURE);
			}
			exit(EXIT_FAILURE);
		}
	}
	int close_fd=close(input_fd);
	if (close_fd == -1) {
		char *hlp = "close error\n";
		output_fd = write(1, hlp, strlen(hlp));
		if (ERROR_CANNT_OPEN == output_fd) {
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
	close_fd= close(output_fd);
	if (close_fd == -1) {
		char *hlp = "close error\n";
		output_fd = write(1, hlp, strlen(hlp));
		if (ERROR_CANNT_OPEN == output_fd) {
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
