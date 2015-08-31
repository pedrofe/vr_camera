# vr_camera #

The following is an VR camera implementation built for the Arnold renderer, a Monte-Carlo unidirectional path-tracer developed by Solid Angle. The implementation is simple, basically two cameras offset by a distance with an specific 360&deg; projection.

For more information about this camera:  
[http://www.pedrofe.com/oculus-camera/](http://www.pedrofe.com/oculus-camera/)

## Instructions to Compile the Camera ##

### Windows ###
 -  Set the environment variable ARNOLD_PATH to the folder where the Arnold SDK is located. If you have installed Arnold in this folder:

   `C:\solidangle\releases\Arnold-X.X.X.X-windows`

   You will set ARNOLD_ PATH to that folder using this command:

   `set ARNOLD_PATH="C:\solidangle\releases\Arnold-X.X.X.X-windows"`
  - Then, we will open a Visual Studio command prompt and execute the following command:

   `cl /LD /I %ARNOLD_PATH%\include /EHsc VRCamera.cpp /link /LIBPATH:%ARNOLD_PATH%\lib ai.lib`

### Mac ###

 - Assuming you have installed Arnold in this folder:

   `/Users/userName/solidangle/Arnold-X.X.X.X-darwin`

   Open a terminal and set ARNOLD_ PATH to that folder using this command:

   `export ARNOLD_PATH=/Users/userName/solidangle/Arnold-X.X.X.X-darwin`
  - Then, execute the following command to compile the camera shader:

   `gcc -I$ARNOLD_PATH/include -L$ARNOLD_PATH/bin -lai -dynamiclib VRCamera.cpp -o VRCamera.dylib`

## Installation Instructions ##

### MtoA ###

- Place the resulting `VRCamera` binary and the `VRCamera.mtd` files in this folder:  
 `%MTOA_PATH%\shaders\`
- Place the `aiVRCameraTemplate.py` file in the `%MTOA_PATH%\scripts\mtoa\ui\ae\` folder

### C4DtoA ###

#### Windows ####
- Place the resulting `VRCamera` binary and the `VRCamera.mtd` files in this folder:  
 `C:\Program Files\MAXON\CINEMA 4D <Version>\plugins\C4DtoA\shaders\`
- Place the C4DtoA `res` Cinema4D UI resource files in this folder:  
`C:\Program Files\MAXON\CINEMA 4D <Version>\plugins\C4DtoA\res\`

#### Mac ####
- Place the resulting `VRCamera` binary and the `VRCamera.mtd` files in this folder:  
 `/Applications/MAXON/CINEMA 4D <Version>/plugins/C4DtoA/shaders/`
- Place the C4DtoA `res` Cinema4D UI resource files in this folder:  
`/Applications/MAXON/CINEMA 4D <Version>/plugins/C4DtoA/res/`

### HtoA ###

- Place the resulting `VRCamera` binary and the `VRCamera.mtd` files in this folder:  
 `%ARNOLD_PLUGIN_PATH%\shaders\`

### SItoA ###

#### Windows ####
- Place the resulting `VRCamera` binary and the `VRCamera.mtd` files in this folder:  
 `<SITOA_INSTALL>\Application\Plugins\bin\nt-x86-64\`

#### Linux ####
 - Place the resulting `VRCamera` binary and the `VRCamera.mtd` files in this folder:  
`<SITOA_INSTALL>/Application/Plugins/bin/linux/`
