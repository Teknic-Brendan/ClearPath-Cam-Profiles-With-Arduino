/*
  ServoCAM.h - Library for interfacing with Clearpath motors using an Arduino- Version 1
  Teknic 2014 Brendan Flosenzier

  This library is free software; you can redistribute it and/or
  modify it.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

/* 
  
  A

  The functions for a pulse motor are:

   
 */
#ifndef ServoCAM_h
#define ServoCAM_h
#include "Arduino.h"
class ServoCAM
{
  public:
	ServoCAM();
	boolean profileFinished();
	void newMasterScale(double newMaster);
	void newSlaveScale(double newSlave);
	void zero();
	int command();
	double last_Master_Command();
	int	updateCAM(int MasterNextPosition);
	

	
protected:
double x_0, x_1, x_2, x_3, x_4;
double a_0, b_0, c_0, d_0, e_0, f_0;
double a_1, b_1, c_1, d_1, e_1, f_1;
double a_2, b_2, c_2, d_2, e_2, f_2;
double a_3, b_3, c_3, d_3, e_3, f_3;
 int Slave_Next_Commanded_Position;
 double Unitless_Master_Next_Position;
 double Unitless_Slave_Next_Position;
 int Slave_Commanded_Postion;
int StepsToSend=0;
double Slave_Scale;
double Master_Scale;

};
#endif

