#pragma once
class ElectricDevice;
class ElectricNode {
	int no_of_connected;
	ElectricDevice** connected_Devices;
	int capacity;
public:
	ElectricNode();
	void AddDevice(ElectricDevice*);
	void RemoveDevice(ElectricDevice*);
	int GetNumOfDevices() const { return no_of_connected; }
	~ElectricNode();
};