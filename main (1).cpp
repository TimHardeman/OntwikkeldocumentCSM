#include "hwlib.hpp"
#include "rtos.hpp"

// Keypad knoppen:
// De knop VeranderInstellingen geeft aan dat de gebruiker de Instellingen wilt veranderen.
// Met de knop opslaan kan de gebruiker de nieuwe instelling opslaan,
// en met de knop annuleren kan het proces worden geindigd waarbij de nieuwe instelling niet wordt opgeslagen.
// De overige knoppen op de keypad kan een waarde worden geselecteerd.
// Bijvoorbeeld als ID4Min40 wordt ingedrukt bij het veranderen van tijd betekent het 4 minuten, en bij snelheid 40%.
// ID30Min25 betekent 30 minuten en 25%, ID8Min80 betekent 8 min en 80%, etc.
enum eButtonID = {VeranderInstellingenID, OpslaanID, AnnulerenID,
				  ID0min0, ID1min10, ID2Min20, ID3Min30, ID4Min40, ID5Min50, ID6Min60, 
				  ID7Min70, ID8Min80, ID9Min90, ID10Min100, ID30Min25, ID60Min75};

class InstelControl : public rtos::task<>{
	enum state_t = {STANDBY, CHANGESPEED, CHANGETIME}
	
private:
	state_t state = STANDBY;
	rtos::channel bnPressedChannel;
	
	keypad InstellingenKeypad;
	instellingen Instellingen;
	display& Display;
	
	InstellingenControl(display& Display, buttonHandler& ButtonHandler):
					display(Display)
					{ButtonHandler.addButton(keypad);
					 InstellingenKeypad.addButtonListener(this);}
					 
public:
	void buttonPressed(buttonID:eButtonID){ bnPressedChannel.write(buttonID);
	
private:
	void main(){
		
		ebuttonID bnID;
		int speed;
		int time;
		
		for(;;){
			switch(state)
				{
				case STANDBY:
					Display.displayMessage(speed);
					Display.displayMessage(time);
					auto standbyWait = wait(bnPressedChannel);
						if(standbyWait = bnPressedChannel){
							bnID = bnPressedChannel.read();
							if(bnID = VeranderInstellingenID){
								state = CHANGESPEED;
							}
						}
					
				case CHANGESPEED:
					auto speedWait = wait(bnPressedChannel)
					if(speedWait = bnPressedChannel);
					bnID = bnPressedChannel.read();
					if(bnID = OpslaanID){
						Instellingen.setSpeed(speed);
						state = CHANGETIME;
					}
					else if(bnID = AnnulerenID){
						state = CHANGETIME;
					}
					else if(bnID = VeranderInstellingenID){
						speed = speed;
					}
					else if(bnID = ID0min0){speed = 0}
					else if(bnID = ID1min10){speed = 10}
					else if(bnID = ID2min20){speed = 20}
					else if(bnID = ID3min30){speed = 30}
					else if(bnID = ID4min40){speed = 40}
					else if(bnID = ID5min50){speed = 50}
					else if(bnID = ID6min60){speed = 60}
					else if(bnID = ID7min70){speed = 70}
					else if(bnID = ID8min80){speed = 80}
					else if(bnID = ID9min90){speed = 90}
					else if(bnID = ID10min100){speed = 100}
					else if(bnID = ID30min25){speed = 25}
					else if(bnID = ID60min75){speed = 75}
					
					case CHANGETIME:
					auto timeWait = wait(bnPressedChannel)
					if(timeWait = bnPressedChannel);
					bnID = bnPressedChannel.read();
					if(bnID = OpslaanID){
						Instellingen.setTime(Time);
						state = STANDBY
					}
					else if(bnID = AnnulerenID){
						state = STANDBY;
					}
					else if(bnID = VeranderInstellingenID){
						time = time;
					}
					else if(bnID = ID0min0){time = 0;}
					else if(bnID = ID1min10){time = 1;}
					else if(bnID = ID2min20){time = 2;}
					else if(bnID = ID3min30){time = 3;}
					else if(bnID = ID4min40){time = 4;}
					else if(bnID = ID5min50){time = 5;}
					else if(bnID = ID6min60){time = 6;}
					else if(bnID = ID7min70){time = 7;}
					else if(bnID = ID8min80){time = 8;}
					else if(bnID = ID9min90){time = 9;}
					else if(bnID = ID10min100){time = 10;}
					else if(bnID = ID30min25){time = 30;}
					else if(bnID = ID60min75){time = 60;}
			    }
		}
	}

