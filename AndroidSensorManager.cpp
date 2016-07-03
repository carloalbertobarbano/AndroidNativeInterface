#include "AndroidSensorManager.h"
#include <ctime>
#include <chrono>

using namespace AndroidDevice;

AndroidSensorManager::AndroidSensorManager() {
	sensorManager = ASensorManager_getInstance();
	if(!sensorManager) {
		std::cout << "Cannot create SensorManager!" << std::endl;
		return;
	}

	state.looper = ALooper_forThread();
	if(!state.looper)
		state.looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

}

std::vector<float> AndroidSensorManager::readGenericSensor(int sensor, int *res) {
	std::vector<float> data;

	const ASensor *genericSensor = ASensorManager_getDefaultSensor(sensorManager, sensor);
	if(!genericSensor) {
		if(res)*res = SensorError::SENSOR_NOT_FOUND;
		return data;
	}

	ASensorEventQueue *sensorEventQueue = ASensorManager_createEventQueue(sensorManager, state.looper, LOOPER_ID_USER, NULL, NULL);
	ASensorEventQueue_enableSensor(sensorEventQueue, genericSensor);
	
	const clock_t begin_time = clock();
	while((float(clock() - begin_time)/CLOCKS_PER_SEC)*1000.0 <= 1000) { //Needed for not freezing the device, it the sensor doens't respond
		int ident;
		int events;
		struct android_poll_source *source;

		while((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {
			if(ident == LOOPER_ID_USER) {
				if(genericSensor != NULL) {
					ASensorEvent event;
					while(ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {
						switch(sensor) {
							case ASENSOR_TYPE_ACCELEROMETER:
							  data.push_back(event.acceleration.x);
							  data.push_back(event.acceleration.y);
							  data.push_back(event.acceleration.z);
							break;

							case ASENSOR_TYPE_GYROSCOPE:
							  data.push_back(event.vector.x);
							  data.push_back(event.vector.y);
							  data.push_back(event.vector.z);
							break;
							
							case ASENSOR_TYPE_MAGNETIC_FIELD: 
							  data.push_back(event.magnetic.x);
							  data.push_back(event.magnetic.y);
							  data.push_back(event.magnetic.z);
							break;

							case ASENSOR_TYPE_LIGHT:
							  data.push_back(event.light);
							break;
							
							case ASENSOR_TYPE_PROXIMITY:
							  data.push_back(event.distance);
							break;

							default: break;
						}
						
						if(res)*res = 1;
						return data;
					}
				}
			}
		}
	}
	
	if(res)*res = SensorError::SENSOR_FREEZE;
	return data;
}

