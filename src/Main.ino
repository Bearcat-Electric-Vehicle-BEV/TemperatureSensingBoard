/**
 * @file Main.ino
 * @author Marshal Stewart (stewa2m3@mail.uc.edu)
 * @brief 
 * @version v1.1
 * @date 2022-07-03
 * 
 * This is the main file for the BEV TeensyECU. It contains the setup and loop,
 * functions. The intention is for this file to be readable at a high level. 
 * For example a leadership member from another team should be able to read this
 * file and get a good understanding of what is going on. Then be able to 
 * navigate to the various source files for implementation concerns for things 
 * such as I2C or CAN function implementations. 
 *  
 * $$$$$$$\  $$$$$$$$\ $$\    $$\
 * $$  __$$\ $$  _____|$$ |   $$ |
 * $$ |  $$ |$$ |      $$ |   $$ |
 * $$$$$$$\ |$$$$$\    \$$\  $$  |
 * $$  __$$\ $$  __|    \$$\$$  /
 * $$ |  $$ |$$ |        \$$$  /
 * $$$$$$$  |$$$$$$$$\    \$  /   
 * \_______/ \________|    \_/    
 * Copyright University of Cincinnati 2022
 * 
 */

#include "bev_can.h"
#include "bev_logger.h"
#include "bev_etc.h"
#include "bev_state.h"
#include "bev_pins.h"
#include "bev_state.h"
#include "bev_faults.h"

#include <task.h>


/**
 * @brief FreeRTOS Idle Task Hook
 * Function runs as part of the IDLE task. Used to run
 * services that if starved would result in system failure. 
 * If starved indicates that the application is poorly 
 * designed. Scheduler shouldn't ever go beyond 65% utilization.
 * 
 * @note Unsupported for Teensy 4.1 FreeRTOS port, moved to state task
 */
// void vApplicationIdleHook(void)
// {
//     Serial.println("IDLE TASK");
//     ServiceCANIdle();
// }

/**
 * @brief Initialization
 * Setup I/O and system modules here before scheduler starts.
 */
void setup() {

  Serial.begin(9600); 
  delay(400);
  ChangeState(INIT);

  // Set Pin Modes
  pinMode(PIN_VEHICLE_PWR, INPUT);
  pinMode(PIN_Brake_Light, OUTPUT);
  pinMode(PIN_ECU_OK, OUTPUT);
  pinMode(PIN_PRECHARGE_FINISHED, INPUT);
  pinMode(PIN_READY_TO_GO, OUTPUT);
  pinMode(PIN_SHUTDOWN_TTL_OK, INPUT);
  pinMode(PIN_CAN_TRANS_STDBY, OUTPUT);
  pinMode(PIN_SDA, OUTPUT);
  pinMode(PIN_SCL, OUTPUT);
  pinMode(PIN_ACCEL_0, INPUT);
  pinMode(PIN_ACCEL_1, INPUT);
  pinMode(PIN_BRAKE_POS, INPUT);
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_RESET, INPUT);
  pinMode(PIN_FORWARD_SWITCH, INPUT);
  pinMode(PIN_FORWARD_ENABLE, OUTPUT);
 
  /* tranceiver enable pin */
  digitalWrite(PIN_CAN_TRANS_STDBY, LOW);

  CANInit();

  /// @todo Setup watchdog
  
  /// @todo Setup BRAKE interrupt
  // attachInterrupt(PIN_BRAKE_POS, null);

  attachInterrupt(PIN_SHUTDOWN_TTL_OK, ISR_SHUTDOWN_TTL_OK, RISING);

  /** 
   * @paragraph Static Allocation vs Dynamic Allocation
   * On embedded targets static allocation is typically favored, however with
   * the high stakes of a stack overflow causing the car to fail. The temptation
   * to go with heap allocation is real. Most definiently slower, however lowers
   * probability of stack overflow. With that being said, stack overflow checks
   * should be in place. There exist tools or methods to determine how much heap
   * is being used.
   */
  xTaskCreate(vStateMachine, "STATE", 2048, nullptr, 3, &pxStateMachineHandle);
  xTaskCreate(vETCTask, "ETC", 2048, nullptr, 5, &pxETCTaskHandle);
  xTaskCreate(vFaultManager, "FAULT", 2048, nullptr, 4, &pxFaultManagerHandle);

  /** @note Execution doesn't go beyond scheduler */
  vTaskStartScheduler();

  for(;;) {}

}

/** @note execution will never reach loop() once the scheduler has started */
void loop() {}
  
