#ifndef BEV_ETC_H
#define BEV_ETC_H

#include "bev_pins.h"
#include "bev_state.h"

#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>

#define ACCEL_MAX 1023

typedef uint16_t adc_t;
typedef int16_t torque_t;
	
enum PedalSourceTypes {
	DIGITAL 		= 0,
	ANALOG_0V_3V	= 1,
	ANALOG_3V_0V	= 2,
	ANALOG_0V_5V	= 3
};

/**
 * @brief Class Abstracting Pedal Interaction
 */
class Pedal
{
public:

    Pedal(pin_t pin, uint8_t src_type);
	
	adc_t ReadPedal(void);
	float GetRatio(void);
	uint32_t GetRatio_u32(void);
	bool Applied(void);

	float operator-(const Pedal &pedal);

private:
	/* pin number, prefers MACROS found in bev_pins.h */
	pin_t pin;

	/* Raw ADC tick reading (0-1023) */
	adc_t pos;
	
	/* ADC tick converted to 0-100% pedal position */
	float ratio;
	
	/* How the pin is interpreted Ex. digital or analog, 0-3.3V or 3.3-0V */
	uint8_t src_type;

};

extern code_t ETC(Pedal *pedal_0, torque_t *request);
extern TaskHandle_t pxETCTaskHandle;
void vETCTask(void * pvParameters);

#endif // BEV_ETC_H