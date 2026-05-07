# SOS - Simple Orbit Simulator

## Description
A simple, lightweight C++-based orbital mechanics simulator. It was developed as a training project in physics, mathematics, and object-oriented programming in C++.

![Trajectory Exaple](docs/trajectoryExample.png)

## Current State
Development of the core physics engine and architecture.

## Architecture description:

### Core Classes
1) `SpaceObject` - Base class for all objects in the Simulation.
    - `FixedObject` - "Steady" objects or origins, like the Sun in a Solar System model or Earth in an Earth-Moon-Spaceship system.
    - `FreeObject` - All other objects which can move based on physics.
    - *[perspective]* `ActiveObject` - Objects which can move using their own thrust.
2) *[dev]* `Simulation` - The class that contains the simulation loop and objects.
3) `SimpleVector` - Core 2D vector math and logic.
4) *[perspective]* `CollisionReport` - Class to detect and handle collisions.
5) *[perspective]* `Graphics` - The visual part of the simulation.
6) *[dev]* `Logger` - Save the results of simulation

```mermaid
classDiagram

    SpaceObject <|-- FixedObject
    SpaceObject <|-- FreeObject
    Simulation "1" -- "*" SpaceObject : contains

    SpaceObject *-- SimpleVector : composition
    Simulation o-- SpaceObject : aggregation
    
    class Simulation {
        - objects: std::vector<SpaceObject*>
        - tick: int = 0
        + addObject(SpaceObject&: object) void
        + removeObject(SpaceObject&: object) void
        + calculateSystem() void
        + checkCollisions() CollisionReport
        + nextStep() void
    }

    class SpaceObject {
        # id: int ~readOnly, unique~
        # position: SimpleVector
        # mass: double
        # appliedForce: SimpleVector
        + calculateAppliedForce(const SpaceObject&: object) ~isAbstract~
        + recalculatePos() ~isAbstract~
        + getPosition() SimpleVector
        + getAppliedForce() SimpleVector 
        + getMass() double
    }

    class FixedObject {
        
    }

    class FreeObject {
        # acceleration: SimpleVector
        # velocity: SimpleVector
        + recalculateVelocity() SimpleVector
    }

    class SimpleVector {
        - x: double
        - y: double
        + getX() double
        + getY() double
        + setX(x: double) *SimpleVector
        + setY(y: double) *SimpleVector
        + abs() double
        + operator+(vec&: SimpleVector) SimpleVector
        + operator+=(vec&: SimpleVector) void
        + operator-(vec&: SimpleVector) SimpleVector
        + operator-=(vec&: SimpleVector) void
        + operator*(double scalar) SimpleVector
        + operator*=(double scalar) void
        + $getUnitVector() SimpleVector
    }

    class CollisionReport {
        - object_1: SpaceObject*
        - object_2: SpaceObject*
        - coordinates: SimpleVector
        + getObject1() SpaceObject
        + getObject2() SpaceObject
        + getCoordinates() SimpleVector
        + printReport() void
    }

    class Physics {
        <<namespace>>
        + GRAVITATIONAL_CONSTANT double
        + calculateGravitationalForce(m1, m2, dist) double
    }
```

## Process

Currently outlining the "Idea" Flowchart for the main engine loop:

```mermaid
flowchart TD
    %% Nodes
        A(Start)
        B[[Create Simulation-Object]]
        C[[Create and add SpaceObject's]]
        IF1{Simulation running}
        IF1_A[For all SpaceObject's: calculateAppliedForce other objects]
        IF1_B[[For all SpaceObject's: recalculatePosition]]
        IF1_B1[[Collision processing]]
        IF1_C[[Graphics update, logging, etc.]]
        D(End)
    %% Connections
        A --> B --> C --> IF1
        IF1 --yes--> IF1_A
        IF1_C --> IF1
        subgraph End
            D
        end
        IF1 -- no --> D
        subgraph Simulation::run
            IF1
            subgraph Simulation::nextStep
                IF1_A --> IF1_B --> IF1_B1 --> IF1_C
            end
        end
```