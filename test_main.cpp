// test_main.cpp — comprehensive test for the Electric circuit classes.
// Compile INSTEAD of main.cpp:
//   g++ -std=c++11 ElectricNode.cpp ElectricDevice.cpp Resistor.cpp Capacitor.cpp test_main.cpp -o tests
#include "ElectricNode.h"
#include "Resistor.h"
#include "Capacitor.h"
#include <iostream>

static int passed = 0, failed = 0;

#define CHECK(desc, expr) do { \
	if (expr) { std::cout << "  [PASS] " << desc << "\n"; passed++; } \
	else      { std::cout << "  [FAIL] " << desc << "\n"; failed++; } \
} while (0)

// float comparison with tolerance (0.05 etc. are not exact in binary)
static bool approx(double a, double b) { double d = a - b; return d < 0 ? -d < 1e-6 : d < 1e-6; }

int main() {
	std::cout << "===== 1. ElectricNode basics =====\n";
	{
		ElectricNode n;
		Resistor r(nullptr, nullptr, 1);
		CHECK("new node starts at 0 devices", n.GetNumOfDevices() == 0);
		n.AddDevice(&r);
		CHECK("AddDevice registers the device", n.GetNumOfDevices() == 1);
		n.RemoveDevice(&r);
		CHECK("removing the ONLY device -> 0 (single-device case)", n.GetNumOfDevices() == 0);
		n.RemoveDevice(&r);
		CHECK("removing an ABSENT device changes nothing", n.GetNumOfDevices() == 0);
		n.RemoveDevice(nullptr);
		CHECK("removing nullptr is safe", n.GetNumOfDevices() == 0);
		bool cycles = true;
		for (int i = 0; i < 50; i++) { n.AddDevice(&r); if (n.GetNumOfDevices() != 1) cycles = false; n.RemoveDevice(&r); if (n.GetNumOfDevices() != 0) cycles = false; }
		CHECK("50 add/remove cycles stay consistent", cycles);
	}
	std::cout << "===== 2. Growth (capacity doubling) =====\n";
	{
		ElectricNode n;
		Resistor* rs[100];
		for (int i = 0; i < 100; i++) rs[i] = new Resistor(nullptr, nullptr, 1);
		for (int i = 0; i < 100; i++) n.AddDevice(rs[i]);
		CHECK("100 adds -> count 100 (grew 1..128)", n.GetNumOfDevices() == 100);
		for (int i = 0; i < 100; i++) n.RemoveDevice(rs[i]);
		for (int i = 0; i < 100; i++) delete rs[i];
		CHECK("100 removes -> count 0", n.GetNumOfDevices() == 0);
		n.AddDevice(rs[0]);
		CHECK("re-add after full drain works", n.GetNumOfDevices() == 1);
	}
	std::cout << "===== 3. Resistor parallel / series =====\n";
	{
		ElectricNode A, B;
		Resistor r1(&A, &B, 5), r2(&A, &B, 5);
		float v = r1.ConnectParallel(&r2);
		CHECK("R||R returns (5*5)/(5+5) = 2.5", approx(v, 2.5));
		CHECK("merged value stored in the other device", approx(r2.GetResistance(), 2.5));
		CHECK("merged device detached from its nodes", A.GetNumOfDevices() == 1 && B.GetNumOfDevices() == 1);

		Resistor s1(&A, &B, 2), s2(&A, &B, 3);
		float vs = s1.ConnectSeries(&s2);
		CHECK("R series R returns 2+3 = 5", approx(vs, 5.0));
		CHECK("series value stored in Sd", approx(s2.GetResistance(), 5.0));

		Resistor rx(nullptr, nullptr, 4);
		CHECK("ConnectParallel(nullptr) is safe, returns -1", rx.ConnectParallel(nullptr) == -1.0f);
	}
	std::cout << "===== 4. Capacitor parallel / series =====\n";
	{
		Capacitor c1(nullptr, nullptr, 0.05), c2(nullptr, nullptr, 0.05);
		float v = c1.ConnectParallel(&c2);
		CHECK("C||C returns 0.05+0.05 = 0.1", approx(v, 0.1));

		Capacitor s1(nullptr, nullptr, 0.001), s2(nullptr, nullptr, 0.05);
		float vs = s1.ConnectSeries(&s2);
		CHECK("C series C returns (0.001*0.05)/0.051", approx(vs, 0.001 * 0.05 / 0.051));
	}
	std::cout << "===== 5. Mixed types =====\n";
	{
		ElectricNode E, F;
		Resistor rx(&E, &F, 10);
		Capacitor cx(&E, &F, 0.01);
		float v = rx.ConnectParallel(&cx);
		CHECK("R||C ConnectParallel returns -1 (no merge)", v == -1.0f);
		CHECK("R and C share both nodes (really parallel)", rx.IsParallel(&cx));

		// series with the DEFAULT otherend = nullptr (must not crash, must attach to Sd's end node)
		Capacitor cs(&E, &F, 0.02);
		Resistor m(nullptr, nullptr, 4);
		float vs = m.ConnectSeries(&cs, nullptr);      // mixed: Resistor with Capacitor
		CHECK("ConnectSeries with default otherend is safe, returns -1", vs == -1.0f);
		CHECK("device attached to Sd's end node", m.GetEndNode() == &F);
		CHECK("node F now holds all attached devices (rx,cx,cs,m)", F.GetNumOfDevices() == 4);
	}
	std::cout << "===== 6. IsParallel =====\n";
	{
		ElectricNode G, H, K;
		Resistor p1(&G, &H, 1), p2(&G, &H, 1), p3(&H, &G, 1);
		CHECK("same direction (G->H vs G->H)", p1.IsParallel(&p2));
		CHECK("reversed orientation (G->H vs H->G)", p1.IsParallel(&p3));
		Resistor far_away(&K, &H, 1);
		CHECK("different nodes -> not parallel", !p1.IsParallel(&far_away));
		Resistor unconnected(nullptr, nullptr, 1);
		CHECK("unconnected device is never parallel", !p1.IsParallel(&unconnected));
		Capacitor pc(&G, &H, 0.01);
		CHECK("mixed types can be parallel too", p1.IsParallel(&pc));
	}
	std::cout << "\n=================================\n";
	std::cout << "RESULT: " << passed << " passed, " << failed << " failed\n";
	return failed == 0 ? 0 : 1;
}
