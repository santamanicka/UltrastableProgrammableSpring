# Local Ultrastability in a Real Complex Dynamical System

Source code and data for the ECAL 2009 paper:

> **Manicka, S., Di Paolo, Ezequiel.** "Local Ultrastability in a Real Complex Dynamical System." *Proceedings of the European Conference on Artificial Life (ECAL)*, 2009.

## Overview

This project implements ultrastability-based adaptive control for a programmable spring actuator. The system uses Ashby-inspired ultrastability to achieve adaptive behavior in a real robot actuator, where the actuator learns to stabilize a see-saw platform with a metal ball acting as a permanent perturbation.

### Key Concepts

- **Programmable Spring**: A real actuator technology that allows real-time non-linear behavior programming via force profiles (force as a function of angle and velocity)
- **Local Ultrastability**: The actuator monitors its trajectory in phase space (angle vs. angular velocity) and when behavior in any zone deviates from equilibrium, the corresponding piece of the force profile is mutated
- **Phase Space Zones**: The phase space is divided into zones; zone occupancy counts are used to evaluate stability
- **Profile Mutation**: Force, positive damping, and negative damping profiles are mutated when the system detects instability in a zone

## Repository Structure

```
ecal2009_ultrastability/
├── pc_application/          # Borland C++ Builder host application
│   ├── BCB_PGM.CPP/h       # Main application (serial comms, mutation data collection,
│   │                        #   profile visualization, statistics)
│   ├── BCB_PRJ.cpp/BPR     # Project file and entry point
│   ├── Prof.hpp             # Profile object (ProObj) - force/damping tables
│   ├── ProfileDefines.h     # Microcontroller variable/pointer definitions
│   ├── ProfileEditUnit.*    # Profile editor GUI
│   ├── ProfileGeneratorUnit.* # Profile generator (function-based profile creation)
│   ├── ProfileInteractionEditUnit.* # Profile interaction/switching editor
│   ├── ProfileSwitchEditUnit.*  # Profile switch trigger editor
│   ├── ThresholdGroup*.*    # Threshold group settings and editor
│   ├── ForceSurfaceUnit.*   # Force surface (3D) visualization
│   ├── ModulatorsEditUnit.* # Scale, bias, and oscillator modulator editor
│   ├── OscillatorEditUnit.* # Oscillator parameter editor
│   ├── ScaleAndBiasUnit.*   # Scale and bias parameter editor
│   ├── MotorAndForceEditUnit.* # Motor and force control enable
│   ├── IOEditorUnit.*       # I/O configuration (serial, CAN, discrete)
│   ├── SerialEditUnit.*     # Serial port configuration editor
│   ├── SerialPortMonitorUnit.* # Serial port data monitor
│   ├── SerialThreadUnit1.*  # Serial communication thread
│   ├── CANEditorUnit.*      # CAN bus editor
│   ├── AnalogIOUnit.*       # Analog I/O configuration
│   ├── DigitalIOUnit.*      # Digital I/O configuration
│   ├── ActuatorCommandUnit.* # Actuator command interface
│   ├── ActuatorSettingsUnit.* # Actuator settings (node, profile, mode)
│   ├── DownloadProgressUnit.* # Profile download progress
│   ├── GroupTriggerUnit.*   # Group trigger configuration
│   ├── configunit.*         # Serial port configuration
│   ├── FSIO.*               # File stream I/O utilities
│   ├── Points.hpp           # Point class for graph drawing
│   ├── MultiGA.hpp          # Multi-function GA (scaffold)
│   └── DefaultProfileSettings.txt # Default profile configuration
│
├── firmware/                # PIC18F4680 microcontroller firmware
│   ├── AngleController.c/h  # Main firmware (sensor reading, profile iteration,
│   │                         #   serial communication)
│   ├── ProfileFunctions.h   # Core control loop: profile iteration, force
│   │                         #   calculation, angle modification, threshold
│   │                         #   checking, profile switching, oscillator
│   ├── SerialFunctions.h    # Serial packet parsing, profile upload/download,
│   │                         #   mutation data transmission
│   ├── FlashFunctions.h     # Flash memory management for profile storage
│   ├── FlashDefineList.h    # Flash memory address definitions
│   ├── PeripheralFunctions.h # Motor, force, DAC, sensor peripherals
│   ├── Variables.h          # Global variable declarations
│   ├── Multipliers.h        # Fixed-point multiplication tables
│   ├── Defines.h            # Hardware pin and constant definitions
│   └── 18F4680.h            # PIC18F4680 register definitions
│
├── matlab/                  # MATLAB scripts for paper figures
│   ├── fig1.m               # Zone count totals and std deviation over mutations
│   ├── fig2.m               # Phase space trajectories (angle vs velocity)
│   ├── fig3.m               # Mutation magnitude, count, and profile score
│   ├── fig4a.m              # Number of mutations vs non-mutations per iteration
│   ├── fig4b.m              # Mutated vs non-mutated angle positions
│   └── fig5.m               # 3D trajectory plot (time x angle x velocity)
│
├── data/                    # Experimental data (Analysis Run 12)
│   ├── ProfileEvaluation.txt  # Per-mutation zone counts, scores, avg angles/velocities
│   ├── MutationsMagnitude.txt # Total magnitude of force/damping mutations
│   ├── NumMutations.txt       # Count of mutated vs non-mutated angles per iteration
│   ├── MutatedAngles.txt      # Angle positions that were mutated
│   ├── NotMutatedAngles.txt   # Angle positions that were not mutated
│   ├── Force.txt              # Force mutation values
│   ├── PDamp.txt              # Positive damping mutation values
│   ├── NDamp.txt              # Negative damping mutation values
│   └── analysis_12a/          # Additional analysis run data
│
└── paper/                   # Publication
    ├── Local_Ultrastability_ECAL2009.pdf  # Published paper
    └── ECAL_Notes.txt        # Development notes and abstract drafts
```

## Architecture

### System Overview

```
┌──────────────────────┐     Serial (RS232)      ┌──────────────────────┐
│   PC Application     │◄──────────────────────► │  PIC18F4680 Firmware │
│ (Borland C++ Builder)│                         │ (Programmable Spring)│
│                      │     Profile Upload      │                      │
│  - Profile Editor    │────────────────────────►│  - Force Profile     │
│  - Mutation Logger   │                         │    (64-point table)  │
│  - Phase Space Plot  │     Trace + Mutation    │  - Damping Profiles  │
│  - Statistics        │◄────────────────────────│  - Angle Sensor      │
│                      │         Data            │  - Velocity Calc     │
└──────────────────────┘                         │  - Threshold Logic   │
                                                 │  - Profile Switching │
                                                 └──────────┬───────────┘
                                                            │
                                                   Motor + Force Control
                                                            │
                                                            ▼
                                                 ┌──────────────────────┐
                                                 │   See-Saw Platform   │
                                                 │   with Metal Ball    │
                                                 │   (perturbation)     │
                                                 └──────────────────────┘
```

### Ultrastability Algorithm

1. The actuator iterates its force profile, reading angle and computing angular velocity
2. The trajectory in phase space (angle, angular velocity) is monitored
3. Phase space is divided into zones; zone occupancy is tracked
4. When occupancy across zones is uneven (indicating instability), the force profile values at the responsible angles are mutated (random perturbation within a mutation range)
5. The mutated profile is evaluated over subsequent iterations
6. The mutation range decreases over time as stability improves
7. The process repeats until the system converges to a stable behavior

### Key Parameters (from ECAL Notes)

- Initial mutation range (Z) = 100
- Alpha (W) = 30 degrees
- TVZ radius factor (X) = 2
- Mutation range factor (Y) = 80
- Number of analysis samples (V) = 250

## Build Requirements

### PC Application
- Borland C++ Builder 4+ (uses VCL framework)
- WSC serial communication library (WSC4C, not included - vendor library)

### Firmware
- CCS PIC C Compiler (for PIC18F4680)
- PIC programmer (e.g., PICkit)

### MATLAB Scripts
- MATLAB (any version supporting basic plotting)
- Update file paths in scripts from `D:\PSprings\...` to local data directory

## Historical Context

This work was conducted at the University of Sussex as part of a thesis on ultrastable robotics. It explores whether Ashby's concept of ultrastability -- originally proposed as a model of the nervous system -- can be applied to body/motion dynamics for adaptive behavior in physical robots. The programmable spring technology allowed real-time reprogramming of the actuator's force-angle-velocity relationship, making it a suitable platform for testing ultrastability in a real dynamical system.
