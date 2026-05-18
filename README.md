Big-Map Dijkstra Simulation Engine
A high-performance, real-time graph navigation and traffic simulation engine built natively in C++ using the Raylib graphics framework. Developed completely independently during my 2nd Year, 1st Semester to explore advanced data structures, shortest-path optimization heuristics, and interactive real-time visualizers outside the standard university curriculum.

🚀 Architectural Overview
This project implements an interactive visualization of Dijkstra’s Algorithm over a custom coordinate-mapped graph structure representing an urban routing topology. The system decouples algorithmic computation from the graphics rendering pipeline, using a multi-factored dynamic edge weight heuristic to calculate optimal travel paths in real time.

+-------------------------------------------------------------+
|                      User Interaction Layer                 |
|             (Real-time Start/End Node Selection)            |
+----------------------------------------------+--------------+
                                               |
                                               v
+-------------------------------------------------------------+
|                     Raylib Simulation Loop                  |
|          - Linear Interpolation (Lerp) Frame Updates         |
|          - Dynamic Screen Rendering Matrix                  |
+----------------------------------------------+--------------+
                                               |
                                               v
+-------------------------------------------------------------+
|                     Algorithmic Core                        |
|       - Min-Priority Queue Dijkstra (O((V + E) log V))       |
|       - Dynamic Edge Weighing Hysteresis                    |
+-------------------------------------------------------------+
🛠️ Technical Highlights & Core Competencies
1. Algorithmic Optimization

Time Complexity: Achieves O((V+E)logV) efficiency utilizing a min-heap priority queue implementation (std::priority_queue), ensuring responsive path recalculations even over large graphs.

Data Structures: Custom adjacency list structures utilizing spatial index caching with average O(1) lookups via std::unordered_map.

2. Math & Physics Simulations

Kinematic Translation Vectors: Real-time entity positioning is achieved using unit vector direction calculations paired with scalar magnitude clamping to simulate constant-velocity car translations over geometric paths.

Dynamic Weight Adaptation: The edge weights are calculated dynamically through a dynamic modifier function:

Weight=Distance×Traffic Factor
This allows the algorithm to pivot smoothly from purely spatial routing to traffic-congested network routing.

3. Software Engineering Best Practices

Decoupled State Machine: Built entirely around clean Object-Oriented Programming (OOP) paradigms (Edge, NodeDisplay, NavigationSystem).

Memory Efficiency: Heavy object graphs are safely handled via pointers and standard references (const auto &e) to minimize object duplication overhead during time-critical frame loop executions.

📊 Visual System Mechanics
Green Nodes: Active origin initialization vectors.

Red Nodes: Interactive target execution vectors.

Orange Paths: Calculated shortest paths based on active graph configurations.

Yellow Vector: Simulated moving agent traversing the active node array.

💻 Project Structure & Setup
Markdown
├── main.cpp                # Pure C++ Source Code / Simulation Core
├── include/                # Graphic Framework Dependencies (Raylib)
└── README.md               # Engineering Documentation
Prerequisites

A native C++20 standard supported compiler (GCC/Clang/MSVC)

Raylib development libraries setup on system paths

Building and Executing

To compile and link the engine binary from your terminal console:

Bash
# Using g++ to compile on Linux/macOS
g++ main.cpp -o map_simulation -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Execute the simulation engine
./map_simulation
📈 Future Scope & Research Extensions
[ ] A* Heuristic Integration: Implementing Manhattan or Euclidean distance vector heuristics to optimize search grids down to O(VlogV).

[ ] Live Matrix Telemetry: Generating real-time congestion mockups using asynchronous thread pools (std::async) to mimic chaotic modern urban traffic fields.

[ ] GIS Map Parsing: Building an integrated pipeline to read and translate actual spatial coordinate nodes directly from OpenStreetMap Open-Source XML documents (.osm).

🎓 Academic Takeaways
Developing this engine completely independent of my course assignments helped me build a deeper intuition for Computational Geometry, Graph Theory, and Low-Level Hardware Rendering Loops. It represents my core dedication to pursuing advanced studies in computer science, showcasing my ability to convert abstract mathematical formulations into tangible, high-performance software applications.
