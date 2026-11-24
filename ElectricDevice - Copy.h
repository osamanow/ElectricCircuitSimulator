#pragma once
#include "ElectricNode.h"
#include <iostream>
class ElectricDevice {
	ElectricNode* Node1;
	ElectricNode* Node2;
public:
	ElectricDevice(ElectricNode* , ElectricNode* );
	
	void SetStartNode(ElectricNode*);
	
	ElectricNode* GetStartNode() const ;
	
	void SetEndNode(ElectricNode*);
	
	ElectricNode* GetEndNode() const ;

	virtual float ConnectParallel(ElectricDevice*);
	
	virtual float ConnectSeries(ElectricDevice*,ElectricNode* =nullptr);

	virtual bool IsParallel(ElectricDevice*) const;

	virtual void PrintInfo()  const =0;
	virtual ~ElectricDevice();

};