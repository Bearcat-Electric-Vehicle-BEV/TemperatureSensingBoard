 enum ECUState {INIT,RESET,RESET_CONFIRM,ERROR_STATE,ROUTINE_CHECK,PRE_HV_CHECK,HV_READY_WAIT,PRECHARGE_WAIT,READY_TO_GO_WAIT};
 ECUState currentState;
//#define carInit();
//#define carReset();
//#define resetConfirm();
//#define error();
//#define routineCheck();
//#define preHVCheck();
//#define HVReadyWait();
//#define prechargeWait();
//#define readyToGoWait();

void setup() {
  //begins Serial connection for debugging can be removed for production
  Serial.begin(38400);
  //TODO implement watchdog 

  //Enum to describe the different states of the car 
  //Documentation on the states can be found at https://xiahualiu.github.io/posts/bev-tasks/
  //enum ECUState {INIT,RESET,RESET_CONFIRM,ERROR_STATE,ROUTINE_CHECK,PRE_HV_CHECK,HV_READY_WAIT,PRECHARGE_WAIT,READY_TO_GO_WAIT};
 //probably better variable name could be found but I am braindead and in ened so this is what you get
  currentState = INIT;
}

//mess rn
double val;
//TODO create a potentiometer class that can be used for breaks, accel etc. Optionally an analog input class but that prob not needed
//upper bound of potentiometer
int upperBound = 940;
int lowerBound = 0;
int range = upperBound-lowerBound;
void loop() {
  //this is just for debugging 
  currentState=currentState;
  //inside loop determine which function to jump into and if it returns false step to the next state for states that step to another one 
  switch(currentState){
    case INIT:
      carInit();
      break;
    case RESET:
      carReset();
      break;    
    
    case RESET_CONFIRM:
      resetConfirm();
      break;
    case ERROR_STATE:
      error();
      break;
    case ROUTINE_CHECK:
      routineCheck();
      break;
    case PRE_HV_CHECK:
      preHVCheck();
      break;
    case HV_READY_WAIT:
      HVReadyWait();
      break;
      
    case PRECHARGE_WAIT:
      prechargeWait();
      break;
      
    case READY_TO_GO_WAIT:
      readyToGoWait();
      break;
  }
}
void carInit(){
  return false;
  }
bool carReset(){
  return false;
  }
bool resetConfirm(){
  return false;
  }
bool error(){
  return false;
  }
bool routineCheck(){
  return false;
  }
bool preHVCheck(){
  return false;
  }
bool HVReadyWait(){
  return false;
  }
bool prechargeWait(){
  return false;
  }
  
bool readyToGoWait(){
    // put your main code here, to run repeatedly:
  val = analogRead(17);
  val = val-lowerBound;
  val = val/range;
  val = val*100;
   Serial.println("AccelPedal1 Percentage"+(String)val);
   delay(250);
   return false;
  }
