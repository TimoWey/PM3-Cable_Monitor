#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
#include <cmsis_os2.h>
#include "main.h"

extern "C"
{
	extern osMessageQueueId_t Sleep_TimeoutHandle;

}

#endif


Model::Model() : modelListener(0), Timeout_Value(60)
{

}

void Model::tick()
{
#ifndef SIMUULATOR
	if(osMessageQueueGetCount(Sleep_TimeoutHandle) > 0)								//if message recieved
	{
		static uint8_t Timeout_Value;
		if(osMessageQueueGet(Sleep_TimeoutHandle, &Timeout_Value, 0, 0) == osOK)	// if read successfully
		{


			modelListener->setTimeoutValue(Timeout_Value);
		}
	}
#endif
}
