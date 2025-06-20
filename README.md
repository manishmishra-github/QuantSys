# QuantSys

A modular low-latency trading simulator in C++, integrating:

- Custom allocator & logging framework
- FIX protocol via QuickFIX
- Plugin-based strategy engine
- Real-time Qt dashboard
- Cloud deployment with Docker + K8s
- Metrics + logs via Prometheus, Grafana

## Structure

- `/libs`: Common system utilities
- `/core`: Trading system components
- `/simulator`: Market data and feed mockers
- `/ui`: Frontend Qt GUI
- `/deployment`: Docker/K8s/CI scripts

## Build

```bash
mkdir build && cd build
cmake ..
make

