// main.cpp — demo of the Electric circuit classes:
//   ElectricNode  : an electric node holding connected ElectricDevice pointers
//   ElectricDevice: abstract base (ConnectParallel / ConnectSeries / IsParallel)
//   Resistor, Capacitor : concrete devices with merge formulas
#include "Resistor.h"
#include "Capacitor.h"

// Reports how many devices are attached to a node
static void PrintNodeLoad(const char* name, const ElectricNode& n) {
	std::cout << name << " has " << n.GetNumOfDevices() << " device(s) connected\n";
}

// Scans an array of devices and reports which pairs are in parallel
static void FindParallel(ElectricDevice** arr, int n) {
	if (arr == nullptr) return;
	std::cout << "====== Finding Parallel Devices ======\n\n";
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i]->IsParallel(arr[j])) {
				Resistor* r1 = dynamic_cast<Resistor*>(arr[i]);
				Resistor* r2 = dynamic_cast<Resistor*>(arr[j]);
				Capacitor* c1 = dynamic_cast<Capacitor*>(arr[i]);
				Capacitor* c2 = dynamic_cast<Capacitor*>(arr[j]);

				if (r1 != nullptr && r2 != nullptr) {                      // R || R
					std::cout << r1->GetResistance() << " ohm Resistance is in parallel with "
						<< r2->GetResistance() << " ohm Resistance\n\n";
				}
				else if (c1 != nullptr && c2 != nullptr) {                 // C || C
					std::cout << c1->GetCapacitance() << " farad Capacitor is in parallel with "
						<< c2->GetCapacitance() << " farad Capacitor\n\n";
				}
				else if (c1 != nullptr && r2 != nullptr) {                 // C || R
					std::cout << c1->GetCapacitance() << " farad Capacitor is in parallel with "
						<< r2->GetResistance() << " ohm Resistance\n\n";
				}
				else if (r1 != nullptr && c2 != nullptr) {                 // R || C
					std::cout << r1->GetResistance() << " ohm Resistance is in parallel with "
						<< c2->GetCapacitance() << " farad Capacitor\n\n";
				}
			}
		}
	}
}

int main() {
	std::cout << "============ Building the circuit ============\n\n";
	ElectricNode V0, V1, V2, V3;

	ElectricDevice* R1 = new Resistor(&V1, &V0, 2);      // 2 ohm
	ElectricDevice* R2 = new Resistor(&V1, &V0, 3);      // 3 ohm  (parallel with R1)
	ElectricDevice* R3 = new Resistor(&V1, &V2, 5);      // 5 ohm
	ElectricDevice* C1 = new Capacitor(&V2, &V3, 0.001); // 0.001 farad
	ElectricDevice* C2 = new Capacitor(&V3, &V0, 0.05);  // 0.05 farad

	PrintNodeLoad("V0", V0); PrintNodeLoad("V1", V1);
	PrintNodeLoad("V2", V2); PrintNodeLoad("V3", V3);
	std::cout << "\n";

	std::cout << "============ Connecting devices ============\n\n";

	// Unconnected device R4 merged in parallel with R3:
	// equivalent resistance (5*5)/(5+5) = 2.5 ohm, stored in R3
	ElectricDevice* R4 = new Resistor(nullptr, nullptr, 5);
	std::cout << "Connecting R4 parallel to R3: "
		<< R4->ConnectParallel(R3) << " ohms\n\n";

	// Unconnected device C3 merged in parallel with C2:
	// equivalent capacitance 0.05 + 0.05 = 0.1 farad, stored in C2
	ElectricDevice* C3 = new Capacitor(nullptr, nullptr, 0.05);
	std::cout << "Connecting C3 parallel to C2: "
		<< C3->ConnectParallel(C2) << " farads\n\n";

	// Unconnected device R5 in SERIES with R3:
	// equivalent resistance 6 + 2.5 = 8.5 ohm, stored in R3
	ElectricDevice* R5 = new Resistor(nullptr, nullptr, 6);
	std::cout << "Connecting R5 in series with R3: "
		<< R5->ConnectSeries(R3) << " ohms\n\n";

	// Mixed types cannot merge electrically here: R4 simply connects
	// onto C2's nodes, making them really parallel ( ConnectParallel returns -1 )
	std::cout << "Connecting R4 parallel to C2 (mixed types): "
		<< R4->ConnectParallel(C2) << " (devices are now on the same nodes)\n\n";

	ElectricDevice* devices[] = { R1, R2, R3, R4, R5, C1, C2, C3 };
	FindParallel(devices, 8);

	std::cout << "============ Node loads after connecting ============\n\n";
	PrintNodeLoad("V0", V0); PrintNodeLoad("V1", V1);
	PrintNodeLoad("V2", V2); PrintNodeLoad("V3", V3);
	std::cout << "\n";

	// Cleanup: nodes do NOT own the devices, main() does
	delete R1; delete R2; delete R3; delete R4;
	delete R5; delete C1; delete C2; delete C3;
	R1 = R2 = R3 = R4 = R5 = nullptr;
	C1 = C2 = C3 = nullptr;

	std::cout << "Done.\n";
	return 0;
}
