#pragma once
#include "ElectricDevice.h"
class Capacitor :public ElectricDevice {
	double  capacitance;
public:
	Capacitor(ElectricNode*, ElectricNode*, float);
	void SetCapacitance(double);
	double GetCapacitance() const;

	float ConnectParallel(ElectricDevice*);

	float ConnectSeries(ElectricDevice*, ElectricNode* = nullptr);

	void PrintInfo()  const;




};