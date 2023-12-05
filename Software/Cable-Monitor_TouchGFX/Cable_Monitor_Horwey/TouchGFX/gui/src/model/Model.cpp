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

