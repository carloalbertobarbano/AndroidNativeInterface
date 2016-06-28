#include "AndroidSensorManager.h"

int main(int argc, char **argv) {
  AndroidDevice::AndroidSensorManager *sensorManager = new AndroidDevice::AndroidSensorManager();
  int res = 0;
  std::vector<float> distance = sensorManager->readGenericSensor(ASENSOR_TYPE_PROXIMITY, &res);
  
  if(res > 0)
  	printf("{\n\t'distance': '%f'\n}\n\n", distance[0]);
  else
	printf("{\n\t'distance': 'nan'\n}\n\n");
	
  return 0;
}
