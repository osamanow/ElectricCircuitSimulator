#pragma once
#include "ElectricDevice.h"
class Resistor :public ElectricDevice {
	 double  resistance;
public:
	Resistor(ElectricNode* , ElectricNode* , float );
	void SetResistance(double);
	double GetResistance() const;
	
	float ConnectParallel(ElectricDevice*);
	
	float ConnectSeries(ElectricDevice*, ElectricNode* = nullptr);

	void PrintInfo()  const ;




};