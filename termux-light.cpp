#include "AndroidSensorManager.h"

int main(int argc, char **argv) {
  AndroidDevice::AndroidSensorManager *sensorManager = new AndroidDevice::AndroidSensorManager();
  int res = 0;
  std::vector<float> light = sensorManager->readGenericSensor(ASENSOR_TYPE_LIGHT, &res);
  
  if(res > 0)
  	printf("{\n\t'light': '%f'\n}\n\n", light[0]);
  else
	printf("{\n\t'light': 'nan'\n}\n\n");
	
  return 0;
}
