## Navigating the OCCAM Codebase

### Key Files:
* **py/ocUtils.py**: defines the ocUtils helper class which is used to interact with the key C++ objects (VBMManager and SBMManager, the managers for the Variable-Based and State-Based OCCAM modes, respectively).
* **cpp/pyoccam.cpp**: provides the python bindings for the C++ objects via a series python/c API function calls.
* **cpp/occ.cpp**: high-level workflow control. Instantiate managers, initialize reporting parameters, call functions for computing key statistics, build and sort report.

### C++ Classes

### Python Example Workflow Files (install/cl/ and install/web/)
