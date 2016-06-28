#include "AndroidSensorManager.h"

int main(int argc, char **argv) {
  AndroidDevice::AndroidSensorManager *sensorManager = new AndroidDevice::AndroidSensorManager();
  int res = 0;
  std::vector<float> magnetic = sensorManager->readGenericSensor(ASENSOR_TYPE_MAGNETIC_FIELD, &res);
  
  if(res > 0)
  	printf("{\n\t'x': '%f',\n\t'y': '%f',\n\t'z': '%f'\n}\n\n", magnetic[0], magnetic[1], magnetic[2]);
  else
	printf("{\n\t'x': 'nan',\n\t'y': 'nan',\n\t'z': 'nan'\n}\n\n");
	
  return 0;
}
