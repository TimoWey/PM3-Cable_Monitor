#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
#include <cmsis_os2.h>
#include "main.h"
extern "C"
{
	//extern osMessageQueueId_t TimeoutTaskHandle;
	extern osMessageQueueId_t TimeoutQueueHandle;
}
#endif



Model::Model() : modelListener(0), Timeout_Value(60)
{

}

/**
 * @brief Executes the tick operation of the Model.
 * 
 * This function is responsible for processing the timeout events in the Model.
 * It checks if there are any pending timeout events in the TimeoutQueueHandle,
 * and if so, it retrieves the timeout value and updates the modelListener with
 * the new timeout value.
 * 
 * @note This function is only executed when not running in the simulator.
 */
void Model::tick()
{
#ifndef SIMULATOR

	if(osMessageQueueGetCount(TimeoutQueueHandle) > 0)
	{
		if(osMessageQueueGet(TimeoutQueueHandle, &Timeout_Value, 0, 0) == osOK)
		{
			modelListener->setTimeoutValue(Timeout_Value);
		}
	}
#endif
}

