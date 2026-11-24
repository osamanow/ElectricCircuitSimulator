#include "Resistor.h"
Resistor::Resistor(ElectricNode* N1, ElectricNode* N2, float Res) 
	:ElectricDevice(N1, N2) {
	if (Res > 0) resistance = Res; else resistance = 0;
}

void Resistor::SetResistance(double res) { if (res > 0)  resistance = res; else resistance = 0; }
double Resistor::GetResistance() const { return resistance; }

float Resistor::ConnectParallel(ElectricDevice* Pd)
{
	if (Pd == nullptr)return -1;

	//Check If Device is Resistor
	Resistor* chres = dynamic_cast<Resistor*> (Pd);
	if (chres != nullptr) {
		float R1 = this->GetResistance();
		float R2 = chres->GetResistance();
		float newres = (R1 * R2) / (R1 + R2);
		
		chres->SetResistance(newres);
	
		//Removing Resistance from its original nodes
		if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
		if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);

		return newres;
	}
	ElectricNode* sn = Pd->GetStartNode();
	ElectricNode* en = Pd->GetEndNode();
	if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
	if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);

	this->SetStartNode(sn);
	this->SetEndNode(en);

	return -1;

}

float Resistor::ConnectSeries(ElectricDevice* Sd, ElectricNode* otherend)
{
	if (Sd == nullptr)return -1;

	//Check If Device is Resistor
	Resistor* chres = dynamic_cast<Resistor*> (Sd);
	if (chres != nullptr) {
		float R1 = this->GetResistance();
		float R2 = chres->GetResistance();

		float newres = R1 + R2;

		//Removing Resistance from its original nodes
		chres->SetResistance(newres);
		if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
		if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);

		return newres;
	}
	
	ElectricNode* en = Sd->GetEndNode();

	if (GetStartNode() != nullptr) GetStartNode()->RemoveDevice(this);
	if (GetEndNode() != nullptr) GetEndNode()->RemoveDevice(this);

	this->SetStartNode(otherend);
	this->SetEndNode(en);
	
	return -1;
}

void Resistor::PrintInfo()  const{
	
	std::cout << "Resistance = " << GetResistance()
		<< " ohms , SN = " << GetStartNode() << " EN = " << GetEndNode() << std::endl <<std::endl;


}

