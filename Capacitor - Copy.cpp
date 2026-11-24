#include "Capacitor.h"
Capacitor::Capacitor(ElectricNode* N1, ElectricNode* N2, float Cap)
	:ElectricDevice(N1, N2) {
	if (Cap > 0) capacitance = Cap; else capacitance = 0;
}

void Capacitor::SetCapacitance(double cap) { if (cap > 0)  capacitance = cap; else capacitance = 0; }

double Capacitor::GetCapacitance() const { return capacitance; }

float Capacitor::ConnectParallel(ElectricDevice* Pd)
{
	if (Pd == nullptr )return -1;

	//Check If Device is Capacitor
	Capacitor* chcap = dynamic_cast<Capacitor*> (Pd);
	if (chcap != nullptr) {
		float R1 = this->GetCapacitance();
		float R2 = chcap->GetCapacitance();

		float newcap = R1 + R2;

		//Removing Capacitance from its original nodes
		chcap->SetCapacitance(newcap);
		if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
		if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);

	
		return newcap;
	}
	ElectricNode* sn = Pd->GetStartNode();
	ElectricNode* en = Pd->GetEndNode();

	if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
	if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);

	this->SetStartNode(sn);
	this->SetEndNode(en);

	return -1;
	

}

float Capacitor::ConnectSeries(ElectricDevice* Sd, ElectricNode* otherend)
{
	if (Sd == nullptr )return -1;

	//Check If Device is Capacitor
	Capacitor* chcap = dynamic_cast<Capacitor*> (Sd);
	if (chcap != nullptr) {
		float R1 = this->GetCapacitance();
		float R2 = chcap->GetCapacitance();
		float newcap = (R1 * R2) / (R1 + R2);

		chcap->SetCapacitance(newcap);

		//Removing Capacitance from its original nodes
		if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
		if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);

		return newcap;
	}
	ElectricNode* en = Sd->GetEndNode();

	if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
	if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);
	this->SetStartNode(otherend);
	this->SetEndNode(en);

	return -1;
}

void Capacitor::PrintInfo()  const {

	std::cout << "Capacitance = " << GetCapacitance()
		<< " farad , SN = " << GetStartNode() << " EN = " << GetEndNode() << std::endl << std::endl;

}

