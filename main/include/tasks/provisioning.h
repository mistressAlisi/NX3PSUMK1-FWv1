/*
 * system_settings.h
 *
 *  Created on: Aug 28, 2021
 *      Author: rasheek
 */

#ifndef MAIN_INCLUDE_PROVISIONING_H_
#define MAIN_INCLUDE_PROVISIONING_H_

#include <Preferences.h>

/** d9NX3 FW Provisioning (settings) and interaction class. **/
class task_provisioning_class {
private:

public:
	/**This is the actual preferences storage backend: **/
	Preferences prefs;
	/** Are we provisioned? true/false: **/
	bool is_provisioned();
	/** Init and startup function (C++ standard): **/
	void init();

};

#endif


