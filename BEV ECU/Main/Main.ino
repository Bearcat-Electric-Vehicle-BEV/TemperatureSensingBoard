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
double startTime;
double prechargeTime;
bool timerStarted=false;

//TODO create a potentiometer class that can be used for breaks, accel etc. Optionally an analog input class but that prob not needed
//upper bound of potentiometer
int upperBound = 940;
int lowerBound = 0;
int range = upperBound-lowerBound;
//outgoing signal table true means it should be High false means it should be low
bool ECUOk;
bool PRECHARGE_FINISHED;
bool READY_TO_GO;
void loop() {
  prechargeTime=2000;
  //this is just for debugging 
  currentState=currentState;
  //inside loop determine which function to jump into and if it returns false step to the next state for states that step to another one 
  switch(currentState){
    case INIT:
      if(carInit()){
        currentState=RESET;
        }
      break;
    case RESET:
      if(carReset()){
        currentState=HV_READY_WAIT;
        }
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
  //Output signals based on current signal table states
  //
}
bool carInit(){
  ECUOk=false;
  PRECHARGE_FINISHED=true;
  return true;
  }
bool carReset(){
  ECUOk=false;
  PRECHARGE_FINISHED=true;
  //todo reset memory when memory is implemented
  return true;
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
  }
bool HVReadyWait(){
  return false;
  }
bool prechargeWait(){
  //Timer for precharge time needed
  if(!timerStarted){
    startTime=millis();}
  else if(timerStarted&&millis()-startTime<=prechargeTime){
    PRECHARGE_FINISHED=true;
    return false;
    }
  else{
    timerStarted=false;
    PRECHARGE_FINISHED=false;
    return true;
    }
  }
  
bool readyToGoWait(){
    // put your main code here, to run repeatedly:
  val = analogRead(17);
  val = val-lowerBound;
  return false;
  val = val/range;
  val = val*100;
   Serial.println("AccelPedal1 Percentage"+(String)val);
   delay(250);
   return false;
  }
