/*
 * preferences.cpp
 *
 *  Created on: Aug 28, 2021
 *      Author: rasheek
 */


#include <Preferences.h>

#include "provisioning.h"

bool task_provisioning_class::is_provisioned() {
	bool prov =  prefs.getBool("prov",false);
	return prov;
};
void task_provisioning_class::init() {
	prefs.begin("system");
//	printf("Preferences loaded");
}










