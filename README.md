# Logistic Rover

# Primary

## Overview

This code is designed to control the movement of a rover with four motors using an Arduino. The rover's direction and speed are controlled by joystick input, and it includes features for obstacle avoidance through sensor monitoring.

## Functionality

### Initialization

The `init` method sets up the necessary pin modes for motor control and initializes the data buffer used for communication.

### Motor Control

The rover can move in various directions:

- `moveUp()`, `moveDown()`, `moveLeft()`, `moveRight()`: Direct the rover to move in specific directions.
- `rotateClockwise()`, `rotateCounterClockwise()`: Rotate the rover in the indicated direction.
- `stopAllMotors()`: Halt all motor movement.

### Lift Motor Control

The `liftMotorControl` method adjusts the lift motor based on joystick input, allowing the rover to lift or lower certain components.

### Speed Calculations

#### Scaling

The `scaleSpeed` method adjusts joystick input to set motor speeds within a defined range.

#### Calculating Motor Speeds

The `calculateMotorSpeeds` method determines motor speeds based on joystick input, taking into account direction and sensor data for obstacle avoidance.

### Speed Modifiers

The `speedModifier` method adjusts motor speeds based on joystick input and axis information, providing flexibility in rover movement.

### Mixing Functions

Several mixing functions (`mixDownLeft`, `mixDownRight`, `mixUpLeft`, `mixUpRight`) modify motor speeds for specific directional combinations, enhancing the rover's maneuverability.

### Motor Control and Monitoring

- `motorControl`: Coordinates lift motor control and calculates motor speeds based on received data.
- `monitor`: Updates sensor instructions for obstacle avoidance, ensuring the rover adapts its movement based on the environment.

## Usage

1. **Initialization**: Include the `MotorSettings.h` header in your main Arduino sketch and instantiate the `Rover` class.

2. **Setup**: Call the `init` method to set up the rover.

3. **Control**: Use the various methods in the `Rover` class to control the rover's movement based on joystick input.

4. **Customization**: Customize the code to fit your specific rover hardware and control requirements.

## Debugging

Enable `DIRECTION_DEBUG_ENABLED` and `LIFT_DEBUG_ENABLED` for additional debugging information if needed.


# Secondary

## Overview

This code facilitates the control of a motor, particularly designed for managing the lifting mechanism of a component. The code includes functionality for initializing the motor, stopping its movement, and controlling its direction based on specific commands.

## Functionality

### Initialization

The `init` method initializes the motor by setting the pin modes for motor control. The default lift state is set to "DOWN."

### Motor Control

The motor can be controlled in various ways:

- `stop()`: Halts the motor's movement.
- `moveUp()`: Directs the motor to move in the upward direction.
- `moveDown()`: Directs the motor to move in the downward direction.
- `run()`: Activates the motor to run.

### Lift Control

The `set` method provides a higher-level control for the lifting mechanism. It accepts a direction parameter (`UP` or `DOWN`) and adjusts the motor's movement accordingly. The movement is constrained to a specific duration, followed by stopping the motor.

### Lift State

The variable `lift_state` keeps track of the current state of the lifting mechanism, indicating whether it is in the "UP" or "DOWN" position.

## Usage

1. **Initialization**: Include the `MotorSettings.h` header in your main Arduino sketch and instantiate the `Motor` class.

2. **Setup**: Call the `init` method to initialize the motor.

3. **Control**: Utilize the various methods in the `Motor` class to control the motor's movement based on specific commands.

4. **Lift Control**: For higher-level control of the lifting mechanism, use the `set` method, specifying the desired direction (`UP` or `DOWN`).

## Debugging

If needed, uncomment the `DEBUG_PORT` statements for debugging information. Additionally, you can modify the duration of motor movement in the `set` method to fit your specific requirements.
