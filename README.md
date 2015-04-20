# oculus-camera

The following is an Oculus VR camera implementation built for the Arnold renderer, a Monte-Carlo unidirectional path-tracer developed by Solid Angle. The implementation is simple, basically two cameras offsetted by a distance with an specific 360º projection.

For more information about this camera:
http://www.pedrofe.com/oculus-camera/

##Instructions to compile the camera:
- ##Windows:
 -  Set the environment variable ARNOLD_PATH to the folder where the Arnold SDK is located. If you have installed Arnold in this folder:

   `C:\solidangle\releases\Arnold-X.X.X.X-windows`
   
   You will set ARNOLD_ PATH to that folder using this command:
   
   `set ARNOLD_PATH="C:\solidangle\releases\Arnold-X.X.X.X-windows"`
  - Then, we will open a Visual Studio command prompt and execute the following command:
 
   `cl /LD /I %ARNOLD_PATH%\include /EHsc OculusCamera.cpp /link /LIBPATH:%ARNOLD_PATH%\lib ai.lib`

- ##OS X
 - Assuming you have installed Arnold in this folder:

   `/Users/userName/solidangle/Arnold-X.X.X.X-darwin`

   Open a terminal and set ARNOLD_ PATH to that folder using this command:

   `export ARNOLD_PATH=/Users/userName/solidangle/Arnold-X.X.X.X-darwin`
  - Then, execute the following command to compile the camera shader:

   `gcc -I$ARNOLD_PATH/include -L$ARNOLD_PATH/bin -lai -dynamiclib OculusCamera.cpp -o OculusCamera.dylib`
   
##Installation Instructions:

- Place the resulting `oculusCamera` binary and the `oculusCamera.mtd` files in this folder: %MTOA_PATH%\shaders\
- Place the `aiOculusCameraTemplate.py` ?le in %MTOA_PATH%\scripts\mtoa\ui\ae\ folder
