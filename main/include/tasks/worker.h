/*
 * worker.h
 *
 *  Created on: Oct 8, 2021
 *      Author: rasheek
 */

#ifndef MAIN_INCLUDE_TASKS_WORKER_H_
#define MAIN_INCLUDE_TASKS_WORKER_H_

class task_worker_class {
private:
	void _doWork();
	 TaskHandle_t _task_handle;
public:
	void init();


	// Enable the 60 second update clock
	void enable_clck();
	void task(void *parm);

	/** tick will be updated in runtime **/
	uint clk_act_tick;
	uint clk_act_heartbeat = 10000;
};



#endif /* MAIN_INCLUDE_TASKS_WORKER_H_ */
