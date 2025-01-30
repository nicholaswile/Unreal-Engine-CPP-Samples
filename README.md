# Unreal-Engine-5-CPP-Samples
C++ samples for Unreal Engine 5 development. Includes my implementation of the <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5-5-documentation">Unreal Engine 5.5 documentation</a> programming tutorials, because I felt like there was a lack of resources available for developers who already are familiar with C++, and are looking for examples of how to use it in the context of Unreal. 

### Using these samples
Copy the desired header and C++ files into your UE5 project, rebuild the project, then open the project in the editor. The desired functionality should be added to the project. Each sample may require an initial scene setup before use.

## Samples

### Custom Actor Class: Transitioning Cameras
<img src="screenshots/UE5_CamControl.gif">

#### <a href="https://github.com/nicholaswile/Unreal-Engine-5-CPP-Samples/tree/main/cameratransitions">Code</a> | <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/quick-start-guide-to-implementing-automatic-camera-control-in-unreal-engine-cpp">Tutorial</a>

Add an instance of the custom class to the scene, then populate the struct with at least one camera in the scene. For each camera in the structure, specify a length of time for its transition duration.

### Custom Actor Class: Levitating Actor with Particle Effect
<img src="screenshots/UE5_CPP_Levitate.gif">

#### <a href="https://github.com/nicholaswile/Unreal-Engine-5-CPP-Samples/tree/main/levitating">Code</a> | <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-cpp-quick-start">Tutorial</a>

In the content browser, drag the Levitating Actor class from the C++ Classes folder into the scene.

### Custom Pawn Class: Player Input
<img src="screenshots/UE5_PlayerInput.gif">

#### <a href="https://github.com/nicholaswile/Unreal-Engine-5-CPP-Samples/tree/main/playerinput">Code</a> | <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/quick-start-guide-to-player-input-in-unreal-engine-cpp">Tutorial</a>

In the project settings, create input axis mappings for MoveX and MoveY, and input action mappings for Grow. This program binds those actions to a custom player pawn. Set a mesh such as a cylinder so the player is visible.