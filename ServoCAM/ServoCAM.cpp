#include "Arduino.h"
#include "ServoCAM.h"
ServoCAM::ServoCAM()
{
	Slave_Commanded_Postion=0;
	Slave_Next_Commanded_Position=0;
	Unitless_Master_Next_Position=0;
	Unitless_Slave_Next_Position=0;
	Slave_Scale = 5000;
	Master_Scale = 5000;
	//Inflection points (relative to Bagwidth)
	x_0=0;
	x_1=0.314903;
	x_2=0.659596;
	x_3=0.783857;
	x_4=1;
	

	a_0=0;
	b_0=1;
	c_0=0;
	d_0=106.7448;
	e_0=-423.721;
	f_0=430.5783;
	
	a_1=0.814903;
	b_1=1;
	c_1=-16.8072;
	d_1=-32.7587;
	e_1=260.2563;
	f_1=-274.444;
	
	a_2=0.159596;
	b_2=1;
	c_2=22.45299;
	d_2=-308.116;
	e_2=1645.351;
	f_2=-3300.96;
	
	a_3=0.333857;
	b_3=1;
	c_3=-3.30946;
	d_3=-498.745;
	e_3=3567.477;
	f_3=-6667.62;
	
	
}
/*		
	
*/
int ServoCAM::updateCAM(int MasterNextPosition)
{
  Unitless_Master_Next_Position=MasterNextPosition/Master_Scale;
  
  if(Unitless_Master_Next_Position<x_4){
	if(Unitless_Master_Next_Position>x_3){
		Unitless_Master_Next_Position-=x_3;
	Unitless_Slave_Next_Position=a_3+b_3*Unitless_Master_Next_Position+c_3*Unitless_Master_Next_Position*Unitless_Master_Next_Position+d_3*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position+e_3*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position+f_3*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position;
	Unitless_Master_Next_Position+=x_3;
	
	} 
	else{	  
		if(Unitless_Master_Next_Position>x_2){
			Unitless_Master_Next_Position-=x_2;
		Unitless_Slave_Next_Position=a_2 + b_2*Unitless_Master_Next_Position + c_2*Unitless_Master_Next_Position*Unitless_Master_Next_Position + d_2*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position + e_2*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position + f_2*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position;
		Unitless_Master_Next_Position+=x_2;
		}
		else{
			if(Unitless_Master_Next_Position>x_1){
				Unitless_Master_Next_Position-=x_1;
			Unitless_Slave_Next_Position=a_1 + b_1*Unitless_Master_Next_Position + c_1*Unitless_Master_Next_Position*Unitless_Master_Next_Position + d_1*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position + e_1*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position + f_1*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position;
			Unitless_Master_Next_Position+=x_1;
			}
			else{
				if(Unitless_Master_Next_Position>x_0){
					Unitless_Master_Next_Position-=x_0;
				Unitless_Slave_Next_Position=a_0 + b_0*Unitless_Master_Next_Position + c_0*Unitless_Master_Next_Position*Unitless_Master_Next_Position + d_0*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position + e_0*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position + f_0*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position*Unitless_Master_Next_Position;
				Unitless_Master_Next_Position+=x_0;
				}
				else{
				Unitless_Slave_Next_Position=0;
				}
  }	}	}	}	
  else{
	  Unitless_Slave_Next_Position=0;
  }
  Slave_Next_Commanded_Position=Unitless_Slave_Next_Position*Slave_Scale;
   StepsToSend=Slave_Next_Commanded_Position-Slave_Commanded_Postion;
  Slave_Commanded_Postion+=StepsToSend;
  
  return StepsToSend;
 
  }
  /*
  
  */
  boolean ServoCAM::profileFinished()
  {
	  if((double)Unitless_Master_Next_Position>x_4)
	  {
		  return true;
	  }
	  else{
		  return false;
	  }
  }
  /*
  
  */
  int ServoCAM::command()
  {
	  return Slave_Commanded_Postion;
  }
  /*
  
  */
  double ServoCAM::last_Master_Command()
  {
	  return Unitless_Master_Next_Position;
  }
  /*
  
  */
  void ServoCAM::newMasterScale(double newMaster)
  {
	  Master_Scale=newMaster;
  }
   /*
  
  */
  void ServoCAM::newSlaveScale(double newSlave)
  {
	  Slave_Scale=newSlave;
  }
  /*
  
  */
  void ServoCAM::zero()
  {
  Slave_Commanded_Postion=0;
	Slave_Next_Commanded_Position=0;
	Unitless_Master_Next_Position=0;
	Unitless_Slave_Next_Position=0;
  }