#ifndef _aitag_vr_camera_h_
#define _aitag_vr_camera_h_

enum
{
   C4DAI_VR_CAMERA_MAIN_GRP                           = 2001,
   C4DAI_VR_CAMERA_MAIN_ATTRIBUTES_GRP                = 3001,
   C4DAI_VR_CAMERA_POLE_MERGEING_GRP                  = 4001,
   C4DAI_VR_CAMERA_EXTRAS_GRP                         = 5001,

   C4DAIP_VR_CAMERA_MODE                              = 173792984,
   C4DAIP_VR_CAMERA_PROJECTION                        = 306666048,
   C4DAIP_VR_CAMERA_EYESEPARATION                     = 983085124,
   C4DAIP_VR_CAMERA_EYETONECKDISTANCE                 = 1145693483,
   C4DAIP_VR_CAMERA_TOPMERGEMODE                      = 1474447029,
   C4DAIP_VR_CAMERA_TOPMERGEANGLE                     = 1426375091,
   C4DAIP_VR_CAMERA_TOPMERGEEXP                       = 2127097005,
   C4DAIP_VR_CAMERA_BOTTOMMERGEMODE                   = 2039415251,
   C4DAIP_VR_CAMERA_BOTTOMMERGEANGLE                  = 1404510063,
   C4DAIP_VR_CAMERA_BOTTOMMERGEEXP                    = 1239696373,
   C4DAIP_VR_CAMERA_MERGESHADER                       = 1387098378,
   C4DAIP_VR_CAMERA_POSITION                          = 1743593624,
   C4DAIP_VR_CAMERA_LOOK_AT                           = 1994118068,
   C4DAIP_VR_CAMERA_UP                                = 394236200,
   C4DAIP_VR_CAMERA_MATRIX                            = 298008712,
   C4DAIP_VR_CAMERA_NEAR_CLIP                         = 336802032,
   C4DAIP_VR_CAMERA_FAR_CLIP                          = 191358685,
   C4DAIP_VR_CAMERA_SHUTTER_START                     = 1436598367,
   C4DAIP_VR_CAMERA_SHUTTER_END                       = 1994337624,
   C4DAIP_VR_CAMERA_SHUTTER_TYPE                      = 1388080621,
   C4DAIP_VR_CAMERA_SHUTTER_CURVE                     = 1417678198,
   C4DAIP_VR_CAMERA_ROLLING_SHUTTER                   = 936499016,
   C4DAIP_VR_CAMERA_ROLLING_SHUTTER_DURATION          = 1494756781,
   C4DAIP_VR_CAMERA_FILTERMAP                         = 1290819591,
   C4DAIP_VR_CAMERA_HANDEDNESS                        = 1460672512,
   C4DAIP_VR_CAMERA_TIME_SAMPLES                      = 496014054,
   C4DAIP_VR_CAMERA_SCREEN_WINDOW_MIN                 = 1981900317,
   C4DAIP_VR_CAMERA_SCREEN_WINDOW_MAX                 = 1981900063,
   C4DAIP_VR_CAMERA_EXPOSURE                          = 279847458,
   C4DAIP_VR_CAMERA_NAME                              = 173771996,
   
   C4DAIP_VR_CAMERA_MODE__SIDE_BY_SIDE                = 0,
   C4DAIP_VR_CAMERA_MODE__OVER_UNDER                  = 1,
   C4DAIP_VR_CAMERA_MODE__UNDER_OVER                  = 2,
   C4DAIP_VR_CAMERA_MODE__LEFT_EYE                    = 3,
   C4DAIP_VR_CAMERA_MODE__RIGHT_EYE                   = 4,

   C4DAIP_VR_CAMERA_PROJECTION__LATLONG               = 0,
   C4DAIP_VR_CAMERA_PROJECTION__CUBE_MAP_NVIDIA       = 1,
   C4DAIP_VR_CAMERA_PROJECTION__CUBE_MAP_3X2          = 2,

   C4DAIP_VR_CAMERA_TOPMERGEMODE__OFF                 = 0,
   C4DAIP_VR_CAMERA_TOPMERGEMODE__LINEAR              = 1,
   C4DAIP_VR_CAMERA_TOPMERGEMODE__COS                 = 2,
   C4DAIP_VR_CAMERA_TOPMERGEMODE__SHADER              = 3,

   C4DAIP_VR_CAMERA_BOTTOMMERGEMODE__OFF              = 0,
   C4DAIP_VR_CAMERA_BOTTOMMERGEMODE__LINEAR           = 1,
   C4DAIP_VR_CAMERA_BOTTOMMERGEMODE__COS              = 2,
   C4DAIP_VR_CAMERA_BOTTOMMERGEMODE__SHADER           = 3,

   C4DAIP_VR_CAMERA_SHUTTER_TYPE__BOX                 = 0,
   C4DAIP_VR_CAMERA_SHUTTER_TYPE__TRIANGLE            = 1,
   C4DAIP_VR_CAMERA_SHUTTER_TYPE__CURVE               = 2,

   C4DAIP_VR_CAMERA_ROLLING_SHUTTER__OFF              = 0,
   C4DAIP_VR_CAMERA_ROLLING_SHUTTER__TOP              = 1,
   C4DAIP_VR_CAMERA_ROLLING_SHUTTER__BOTTOM           = 2,
   C4DAIP_VR_CAMERA_ROLLING_SHUTTER__LEFT             = 3,
   C4DAIP_VR_CAMERA_ROLLING_SHUTTER__RIGHT            = 4,

   C4DAIP_VR_CAMERA_HANDEDNESS__RIGHT                 = 0,
   C4DAIP_VR_CAMERA_HANDEDNESS__LEFT                  = 1,
};

#endif

