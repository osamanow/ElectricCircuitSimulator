#include "ElectricDevice.h"
ElectricDevice::ElectricDevice(ElectricNode* N1, ElectricNode* N2) :Node1(N1), Node2(N2) { 
	if(N2!=nullptr)
	N2->AddDevice(this);
	if (N1 != nullptr)
	N1->AddDevice(this); 
}

void ElectricDevice::SetStartNode(ElectricNode* N1) { Node1 = N1; if (N1 != nullptr) Node1->AddDevice(this); }

ElectricNode* ElectricDevice::GetStartNode() const { return Node1; }

void  ElectricDevice::SetEndNode(ElectricNode* N2) { Node2 = N2; if (N2 != nullptr) Node2->AddDevice(this);
}

ElectricNode* ElectricDevice::GetEndNode() const { return Node2; }

float ElectricDevice::ConnectParallel(ElectricDevice* Pd) 
{
	if (Pd == nullptr)return -1;
	ElectricNode* sn = Pd->GetStartNode();
	ElectricNode* en = Pd->GetEndNode();
	if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
	if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);
	this->SetStartNode(sn);
	this->SetEndNode(en);

	return -1;
}

float ElectricDevice::ConnectSeries(ElectricDevice* Sd,ElectricNode* otherend)
{
	if (Sd == nullptr)return -1;
	ElectricNode* en = Sd->GetEndNode();
	if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
	if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);
		this->SetEndNode(en);
	this->SetStartNode(otherend);
	
	return -1;

}

bool ElectricDevice::IsParallel(ElectricDevice* chp) const 
{
	//Start and End node of the check if parallel with device
	ElectricNode* snchp = chp->GetStartNode();
	ElectricNode* enchp = chp->GetEndNode();
	//This device Start and End Nodes
	ElectricNode* snthp = this->GetStartNode();
	ElectricNode* enthp = this->GetEndNode();
	if (snchp == nullptr || enchp == nullptr || snthp == nullptr || enthp == nullptr) return false;//If any node is null return false

	if ((snchp == snthp && enchp == enthp )|| (snchp == enthp && enchp == snthp)) return true;
	return false;

}

ElectricDevice:: ~ElectricDevice(){}
