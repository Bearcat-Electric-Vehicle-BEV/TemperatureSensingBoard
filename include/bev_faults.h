#ifndef BEV_FAULTS_H
#define BEV_FAULTS_H

#include <stdint.h>

#include "bev_state.h"
#include "bev_can.h"

extern TaskHandle_t pxFaultManagerHandle;

/**
 * @brief Fault Manager FreeRTOS Task and Handle
 */
void vFaultManager(__attribute__((unused)) void * pvParameters);

typedef struct {
	const char *string;
	bool critical;

} Fault_t;

/** @todo make static and hidden */
extern const Fault_t PM100DX_POST_FaultMap[32];
extern const Fault_t PM100DX_RUN_FaultMap[32];
extern const Fault_t OrionBMS2_DTCStatus1_FaultMap[16];
extern const Fault_t OrionBMS2_DTCStatus2_FaultMap[16];

/**
 * @brief Interface Class for Fault Manager
 */
class IFaultManager 
{
public:
	uint16_t *HighWord;
	uint16_t *LowWord;
	
	const Fault_t *FaultMap;

	code_t CheckFaults();
	virtual void ClearFaults() = 0;

private:
};

/**
 * @brief Implementation of IFaultManager for PM100DX
 * 
 */
class PM100DX_FaultManager : public IFaultManager
{
public:

	PM100DX_FaultManager(uint16_t *_HighWord, uint16_t *_LowWord, 
		const Fault_t *_FaultMap);
	void ClearFaults();

private:
};

/**
 * @brief Implementation of IFaultManager for Orion BMS 2
 */
class OrionBMS2_FaultManager : public IFaultManager
{
public:

	OrionBMS2_FaultManager(uint16_t *_HighWord, uint16_t *_LowWord, 
		const Fault_t *_FaultMap);
	void ClearFaults();

private:

};

#endif  // BEV_FAULTS_H