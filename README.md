This Project builds a Matlab C++ Interface based on a custom NITCam class that uses the NIT Library

Required Files:
NITLibrary_x64.dll and
NITLibrary_x64-3.2.1.lib

Workflow:
1. Start Matlab LiveScript: matlab/NITCam_Publishing_WorkFlow.mlx
2. Follow Instructions in LiveScript (add path, copy .dll into folder and load clib)
3. Add NITCamInterface.dll and NITLibrary_x64.dll to paths
4. Use example m-File for first steps 


# Compiler Settings: 
mex -setup
Microsoft Visual C++ 2019 
