# traffic_Lightss

Developed a multithreaded traffic light simulation using modern C++.

## Features
- Two concurrent threads:
  - **Controller thread**: Implements a finite state machine to control North-South and East-West traffic lights.
  - **Monitor thread**: Continuously reads and displays the current signal state.
- Configurable timing using `std::chrono`.
- Thread-safe shared state using `std::atomic`.
- Graceful shutdown using an atomic stop flag and `join()`.

## Tech Stack
- C++17
- STL (`thread`, `chrono`, `atomic`)

## Concepts Demonstrated
- Multithreading
- Finite State Machine (FSM)
- Concurrency safety
- Time-based simulation
- Inter-thread communication through shared atomic state
