# Electric Circuit Simulator

A small C++ project modeling an electric circuit built from **nodes** and
**devices** (resistors / capacitors), including series/parallel connection
logic and equivalent-value merging.

## Classes

| Class | Role |
|---|---|
| `ElectricNode` | Holds the list of devices connected to one node (dynamic pointer array with geometric growth: capacity doubles when full, shrinks when under a quarter used). |
| `ElectricDevice` | Abstract base class: start/end nodes, `ConnectParallel`, `ConnectSeries`, `IsParallel`, pure-virtual `PrintInfo`. |
| `Resistor` | `R∥R = R1·R2/(R1+R2)`, series `R1+R2`. |
| `Capacitor` | `C∥C = C1+C2`, series `C1·C2/(C1+C2)`. |

Devices do **not** belong to nodes: a device is registered on both of its end
nodes, and whoever creates it (`main`) also deletes it. Nodes only store
non-owning pointers.

## Files

```
ElectricNode.h / ElectricNode.cpp       node: connected devices, Add/Remove, capacity management
ElectricDevice.h / ElectricDevice.cpp   abstract device base
Resistor.h / Resistor.cpp               resistor device
Capacitor.h / Capacitor.cpp             capacitor device
main.cpp                                demo program
test_main.cpp                           self-check test suite (compile instead of main.cpp)
```

## Build & run

```bash
g++ -std=c++11 ElectricNode.cpp ElectricDevice.cpp Resistor.cpp Capacitor.cpp main.cpp -o circuit
./circuit
```

## Run the test suite

```bash
g++ -std=c++11 ElectricNode.cpp ElectricDevice.cpp Resistor.cpp Capacitor.cpp test_main.cpp -o tests
./tests          # prints PASS/FAIL per check, exit code 1 if anything failed
```

## Sample output

```
============ Connecting devices ============

Connecting R4 parallel to R3: 2.5 ohms

Connecting C3 parallel to C2: 0.1 farads

Connecting R5 in series with R3: 8.5 ohms
...
2 ohm Resistance is in parallel with 3 ohm Resistance

5 ohm Resistance is in parallel with 0.1 farad Capacitor
```
**
Main and ReadMe are AI Generated**

