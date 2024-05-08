
#include <esp_now.h>
#include <WiFi.h>

/**
 * @brief IMU structure (only acceleration and gyroscope)
*/
typedef struct ImuMessage
{
	uint32_t deltaT;
	float accX;
	float accY;
	float accZ;
	float gyrX;
	float gyrY;
	float gyrZ;
} imuMessage;


imuMessage imu;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
	memcpy(&imu, incomingData, sizeof(imu));
	Serial.print(imu.deltaT);
	Serial.print(",");
	Serial.print(imu.accX);
	Serial.print(",");
	Serial.print(imu.accY);
	Serial.print(",");
	Serial.print(imu.accZ);
	Serial.print(",");
	Serial.print(imu.gyrX);
	Serial.print(",");
	Serial.print(imu.gyrY);
	Serial.print(",");
	Serial.print(imu.gyrZ);
	Serial.println("");
}

void setup()
{
	// Initialize Serial Monitor
	Serial.begin(115200);

	// Set device as a Wi-Fi Station
	WiFi.mode(WIFI_STA);

	// Init ESP-NOW
	if (esp_now_init() != ESP_OK)
	{
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	// Once ESPNow is successfully Init, we will register for recv CB to
	// get recv packer info
	esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
}
