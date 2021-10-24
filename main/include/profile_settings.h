/*
 * profile_settings.h
 *
 *  Created on: Sep 26, 2021
 *      Author: rasheek
 */

#ifndef MAIN_INCLUDE_PROFILE_SETTINGS_H_
#define MAIN_INCLUDE_PROFILE_SETTINGS_H_
/** Configuration for Output driver: **/
/** filesystem path for profiles: **/
/** Defaults: **/
char PROF_DEF_PATH[] = "/pr_builtIn/";
/** User-provided: **/
char PROF_USR_PATH[] = "/pr_user/";

/** Extension for profile files: **/
char PROF_EXT[] = ".json";

/** Default profile if none is stored in settings: **/
char PROF_DEF[] = "default";




#endif /* MAIN_INCLUDE_PROFILE_SETTINGS_H_ */
