#include <iostream>
#include <vector>

#include <android/sensor.h>
#include <android/android_native_app_glue.h>


namespace AndroidDevice {
	enum SensorError {
		SENSOR_NOT_FOUND = -1,
		SENSOR_FREEZE = -2
	}

	class AndroidSensorManager {
		public : 
			AndroidSensorManager();
	
			std::vector<float> readGenericSensor(int sensor, int *res = NULL);	
			std::vector<float> readAccelerationSensor();
			std::vector<float> readGyroscope();
			std::vector<float> readMagneticSensor();
			float readProximitySensor();
			float readLightSensor();

		protected :
			ASensorManager *sensorManager;
			struct android_app state;
	};
}
