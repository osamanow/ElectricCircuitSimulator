#include"ElectricNode.h"

ElectricNode::ElectricNode() { 
	no_of_connected = 0;
	connected_Devices = new ElectricDevice * [1];
	capacity = 1;

}

void ElectricNode::AddDevice(ElectricDevice* add) { 
	if (add == nullptr)return;
	//Checking if max if reached
	if (no_of_connected == capacity) {
		capacity = (capacity==0)? 1:capacity*2;
	//Creating new array with incremented number of devices
	ElectricDevice** temp = new ElectricDevice* [capacity];
	for (int i = 0; i < no_of_connected; i++) {
		temp[i] = connected_Devices[i];
	}
	//Deleting original array to replace it with the incremented array
	delete[] connected_Devices;
	connected_Devices = temp;
	}
	//Adding the device in the last pointer
	connected_Devices[no_of_connected++] = add;

}
void ElectricNode::RemoveDevice(ElectricDevice* rd) {
	int index=-1;
	
	//finding the device
	if (rd == nullptr)return;
	for (int i = 0; i < no_of_connected; i++) {
		if (rd == connected_Devices[i]) {
			index = i;
			connected_Devices[i] = nullptr;
			break;
		}
	}
	if (index == -1)return;
	
	//Rearranging the array
	for (int i = index; i < no_of_connected-1; i++)	connected_Devices[i] = connected_Devices[i + 1];
	
	//Making the hole in the last slot
	connected_Devices[no_of_connected-1] = nullptr;
	
	//Shrinking Array size
	no_of_connected--;
		
	//Allocating new array
	if (no_of_connected > 0 && no_of_connected<capacity/4) {
		capacity = capacity / 2;
		ElectricDevice** temp = new ElectricDevice * [capacity];
		for (int i = 0; i < no_of_connected; i++) {
				temp[i] = connected_Devices[i];
		}
		delete[] connected_Devices;
		connected_Devices = temp;
		}
	
}
ElectricNode::~ElectricNode() {

	delete[] connected_Devices;
	connected_Devices = nullptr;
}
