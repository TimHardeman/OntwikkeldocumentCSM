#include "hwlib.hpp"
#include "rtos.hpp"

enum eButtonID = {AanUitID};

class DockingControl : public rtos::task<>{
	enum state_t = {IDLE, DRIVINGBACKTODOCKINGSTATION, DOCKED};
	enum substateDocked_t = {EMPTYINGBAG, CHARGINGBATTERY};
	
private:
	state_t state = IDLE;
	substateDocked_t substateDocked = EMPYTINGBAG;
	
	rtos::timer timer;
	rtos::flag  flagDocked;
	rtos::flag  flagAanUit;
	rtos::clock clock;
	
	besturingControl& BesturingControl;
	Button Aan/UitKnop;
	batterijSensor BatterijSensor;
	ultrasoonSensor UltrasoonSensor;
	dockingStation Dockingstation;
	display& Display;
	
	DockingControl(besturingControl& BesturingControl, display& Display, buttonHandler& ButtonHandler):
					besturingControl(BesturingControl),
					display(Display)
					{ButtonHandler.addButton(AanUitKnop);
					 Aan/UitKnop.addButtonListener(this);
					 clock.start(5000000);}
					 
public:
	void buttonPressed(buttonID:eButtonID){if(buttonID = AanUitID){flagAanUit.set}};
	void roombaDocked(){flagDocked.set};
	
private:
	void main(){
		for(;;){
			switch(state)
			{
				case IDLE:
				    timer.start(Instellingen.getTime);
					auto idleWait = wait(flagAanUit, timer, clock, flagDocked);
					if(idlewait = flagAanUit){
						state = DRIVINGBACKTODOCKINGSTATION;
					}
					else if(idlewait = timer){
						state = DRIVINGBACKTODOCKINGSTATION;
					}
					else if(idlewait = clock){
						Display.showMessage(UltrasoonSensor.getbag());
						Display.showMessage(BatterijSensor.getBattery());
						
						if(UltrasoonSensor.getBag() > 80 || BatterijSensor.getBattery() < 20){
							state = DRIVINGBACKTODOCKINGSTATION;
						}
					}
					else if(idlewait = flagDocked){
						state = DOCKED;
						if(UltrasoonSensor.getBag() > 80){
							substateDocked = EMPTYINGBAG;
						}
						else substateDocked = CHARGINGBATTERY;
					}
					
				case DRIVINGBACKTODOCKINGSTATION:
					BesturingControl.goToDockingStation();
					
					auto drivingWait = wait(flagDocked);
					if(drivingWait = flagDocked){
						state = DOCKED;
						if(UltrasoonSensor.getBag() > 80){
							substateDocked = EMPTYINGBAG;
						}
						else substateDocked = CHARGINGBATTERY;
					}
					
				case DOCKED:
					switch(substateDocked)
					{
						case EMPTYINGBAG:
							auto bagWait = wait(clock);
							if(bagWait = clock){
								if(UltrasoonSensor.getbag() = 0){
									substateDocked = CHARGINGBATTERY;
								}
							}
							
						case CHARGING BATTERY:
							Dockingstation.chargeBattery();
							auto batteryWait = wait(clock);
							if(batteryWait = clock){
								if(UltrasoonSensor.getBattery() = 100){
									Dockingstation.stopChargingBattery();
									state = IDLE;
								}
							}
					}
			}
		}
	}
}
