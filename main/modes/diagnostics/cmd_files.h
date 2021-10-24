/*
 * cmd_files.h
 *
 *  Created on: Sep 1, 2021
 *      Author: rasheek
 */

#ifndef MAIN_MODES_DIAGNOSTICS_CMD_FILES_H_
#define MAIN_MODES_DIAGNOSTICS_CMD_FILES_H_


static int cmd_fs_mount(int argc, char **argv);
static int cmd_fs_size(int argc, char **argv);
static int cmd_fs_ls(int argc, char **argv);
void register_fs();

void _printDirectory();
#endif /* MAIN_MODES_DIAGNOSTICS_CMD_FILES_H_ */
