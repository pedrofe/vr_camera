#include <ai.h>
#include <ai_cameras.h>
#include <ai_nodes.h>
#include <cstring>
#include <ai_metadata.h>
#include <ai_shaders.h>

AI_CAMERA_NODE_EXPORT_METHODS(VRCameraMethods);
namespace
{
#define _mode              (params[0].INT  )
#define _projection        (params[1].INT  )
#define _eyeSeparation     (params[2].FLT )
#define _eyeToNeckDistance (params[3].FLT )
#define _topMergeMode      (params[4].INT  )
#define _topMergeAngle     (params[5].FLT )
#define _topMergeExp       (params[6].FLT )
#define _bottomMergeMode   (params[7].INT  )
#define _bottomMergeAngle  (params[8].FLT )
#define _bottomMergeExp    (params[9].FLT )
#define _mergeShader       (params[10].FLT )

enum mode
{
   M_SBS = 0,
   M_OU,
   M_UO,
   M_LE,
   M_RE
};
const char* mode_list[] =
{
    "Side by Side",
    "Over Under",
    "Under Over",
    "Left Eye",
    "Right Eye",
    NULL
};

enum projection
{
   P_LATLONG = 0,
   P_CUBEMAP_NVD,
   P_CUBEMAP_3x2
};
const char* projection_list[] =
{
    "Latlong",
    "Cube Map (NVIDIA)",
    "Cube Map (3x2)",
    NULL
};

enum merge_mode
{
   M_OFF = 0,
   M_LINEAR,
   M_COS,
   M_SHADER
};
const char* merge_mode_list[] =
{
    "Off",
    "Linear",
    "Cos",
    "Shader",
    NULL
};

enum eye
{
   E_RIGHT_EYE = 0,
   E_LEFT_EYE
};

enum merge_zone
{
   Z_NONE = 0,
   Z_UP,
   Z_BOTTOM
};

struct CameraData
{
   AtShaderGlobals* sg;
};

};

node_parameters
{
   AiParameterEnum("mode", 0, mode_list);
   AiParameterEnum("projection", 0, projection_list);
   AiParameterFlt("eyeSeparation", 0.65f);
   AiParameterFlt("eyeToNeckDistance", 0.65f);
   AiParameterEnum("topMergeMode", 2, merge_mode_list);
   AiParameterFlt("topMergeAngle", 0.0f);
   AiParameterFlt("topMergeExp", 1.0f);
   AiParameterEnum("bottomMergeMode", 2, merge_mode_list);
   AiParameterFlt("bottomMergeAngle", 0.0f);
   AiParameterFlt("bottomMergeExp", 1.0f);
   AiParameterRGB("mergeShader", 0.0f, 0.0f, 0.0f);
}
node_initialize
{
   CameraData *data = (CameraData*) AiMalloc(sizeof(CameraData));
   data->sg = AiShaderGlobals();
   data->sg->Rt   = AI_RAY_CAMERA;
   AiCameraInitialize(node, data);
}
node_update
{
   AiCameraUpdate(node, false);
}
node_finish
{
   CameraData* data = (CameraData *)AiCameraGetLocalData(node);
   if (data)
   {
      AiShaderGlobalsDestroy(data->sg);
      AiFree(data);
   }
   AiCameraDestroy(node);
}
camera_create_ray
{
   const AtParamValue* params = AiNodeGetParams(node);
    
   int mode = _mode;
   int projection = _projection;
   float eyeSeparation = _eyeSeparation;
   float eyeToNeckDistance = _eyeToNeckDistance;
   
   int topMergeMode = _topMergeMode;
   float topMergeAngle = _topMergeAngle * AI_PI / 180.0f;
   float topMergeExp = _topMergeExp;
   int bottomMergeMode = _bottomMergeMode;
   float bottomMergeAngle = _bottomMergeAngle * AI_PI / 180.0f;
   float bottomMergeExp = _bottomMergeExp;

   float mergeValue = _mergeShader;
   AtNode* mergeShader = AiNodeGetLink(node, "mergeShader");
    
   // TODO:
   //Check that topMergeExp and bottomMergeExp have correct values
   if(topMergeAngle > AI_PIOVER2)
      topMergeAngle = AI_PIOVER2;
   else if(topMergeAngle < -AI_PIOVER2)
      topMergeAngle = -AI_PIOVER2;
   if(bottomMergeAngle < -AI_PIOVER2)
      bottomMergeAngle = -AI_PIOVER2;
   else if(bottomMergeAngle > topMergeAngle)
      bottomMergeAngle = topMergeAngle;


   int currentEye = E_RIGHT_EYE;
   int mergeZone = Z_NONE;
   float sx = input->sx;
   float sy = input->sy;

   // These values are needed for every projection to be able to calculate
   //   the camera position due eye separation and pole merge
   float theta = 0.0f;
   float phi = 0.0f;
   float sin_theta = 0.0f;
   float cos_theta = 0.0f;
    
   ////////////////////////////////////////////////////
   // Stereoscopic mode.
   //  Decide what eye we are rendering. If needed update sx and sy.
   ////////////////////////////////////////////////////

   if(mode == M_SBS)
   {
      if(input->sx < 0)
      {
         currentEye = E_LEFT_EYE;
         sx = 2 * (input->sx + 0.5f);
      }
      else
      {
         currentEye = E_RIGHT_EYE;
         sx = 2 * (input->sx - 0.5f);
      }     
   }
   else if (mode == M_OU)
   {
      if(input->sy < 0)
      {
         currentEye = E_RIGHT_EYE;
         sy = 2 * (input->sy + 0.5f);
      }
      else
      {
         currentEye = E_LEFT_EYE;
         sy = 2 * (input->sy - 0.5f);
      }    
   }
   else if (mode == M_UO)
   {
      if(input->sy < 0)
      {
         currentEye = E_LEFT_EYE;
         sy = 2 * (input->sy + 0.5f);
      }
      else
      {
         currentEye = E_RIGHT_EYE;
         sy = 2 * (input->sy - 0.5f);
      }    
   }
   else if (mode == M_LE)
   {
      currentEye = E_LEFT_EYE;
   }
   else if (mode == M_RE)
   {
      currentEye = E_RIGHT_EYE;
   }
 
   ////////////////////////////////////////////////////
   // Proyection type
   ////////////////////////////////////////////////////

   if (projection == P_LATLONG)
   {
      // Calculate spherical angles
      theta = AI_PI      * sx;
      phi   = AI_PIOVER2 * sy;
        
      sin_theta = sinf(theta);
      cos_theta = cosf(theta);
      
      const float sin_phi = sinf(phi);
      const float cos_phi = cosf(phi);
      // normalized direction
      output->dir.x =  sin_theta * cos_phi;
      output->dir.y =  sin_phi;
      output->dir.z = -cos_theta * cos_phi;
   }
   else if(projection == P_CUBEMAP_NVD)
   {
      if (sx < -2*(1.0f / 3.0f))
      {
         // P_PX
         output->dir.x =  1.0f;
         output->dir.y =  -6*(sx+(5.0f/6.0f));
         output->dir.z =  sy;
      }
      else if (sx < -(1.0f / 3.0f))
      {
         // P_NX
         output->dir.x =  -1.0f;
         output->dir.y =  6*(sx+(3.0f/6.0f));
         output->dir.z =  sy;
      }
      else if (sx < 0.0f)
      {
         // P_PZ
         output->dir.x =  6*(sx+(1.0f/6.0f));
         output->dir.y =  -sy;
         output->dir.z =  1.0f;
      }
      else if (sx < (1.0f / 3.0f))
      {
         // P_NZ
         output->dir.x =  6*(sx-(1.0f/6.0f));
         output->dir.y =  sy;
         output->dir.z =  -1.0f;
      }
      else if (sx < (2.0f / 3.0f))
      {
         // P_PY
         output->dir.x =  6*(sx-(3.0f/6.0f));
         output->dir.y =  1.0f;
         output->dir.z =  sy;
      }
      else
      {
         // P_NY
         output->dir.x =  -6*(sx-(5.0f/6.0f));
         output->dir.y =  -1.0f;
         output->dir.z =  sy;
      }

      theta = atan2(output->dir.x,-output->dir.z);
      phi = AI_PIOVER2 - acos(output->dir.y / sqrt(output->dir.x * output->dir.x + output->dir.y * output->dir.y + output->dir.z * output->dir.z ));

      sin_theta = sinf(theta);
      cos_theta = cosf(theta);
   }
   else if(projection == P_CUBEMAP_3x2)
   {
      if (sy < 0.0f)
      {
         if (sx < -(1.0f / 3.0f))
         {
            // P_PX
            output->dir.x =  1.0f;
            output->dir.y =  2*(sy+0.5f);
            output->dir.z =  3*(sx+(2.0f/3.0f));
         }
         else if (sx < (1.0f / 3.0f))
         {
            // P_PZ
            output->dir.x =  -3*(sx);
            output->dir.y =  2*(sy+0.5f);
            output->dir.z =  1.0f;
         }
         else
         {
            // P_NX
            output->dir.x =  -1.0f;
            output->dir.y =  2*(sy+0.5f);
            output->dir.z =  -3*(sx-(2.0f/3.0f));
         }
      }
      else
      {
         if (sx < -(1.0f / 3.0f))
         {
            // P_NZ
            output->dir.x =  3*(sx+(2.0f/3.0f));
            output->dir.y =  2*(sy-0.5f);
            output->dir.z =  -1.0f;
         }
         else if (sx < (1.0f / 3.0f))
         {
            // P_PY
            output->dir.x =  -3*(sx);
            output->dir.y =  1.0f;
            output->dir.z =  -2*(sy-0.5f);
         }
         else
         {
            // P_NY
            output->dir.x =  -3*(sx-(2.0f/3.0f));
            output->dir.y =  -1.0f;
            output->dir.z =  2*(sy-0.5f);
         }
      }

      theta = atan2(output->dir.x,-output->dir.z);
      phi = AI_PIOVER2 - acos(output->dir.y / sqrt(output->dir.x * output->dir.x + output->dir.y * output->dir.y + output->dir.z * output->dir.z ));

      sin_theta = sinf(theta);
      cos_theta = cosf(theta);
   }
    

   ////////////////////////////////////////////////////
   // Update origin position usinf eye separation
   ////////////////////////////////////////////////////

   if(currentEye == E_LEFT_EYE)
   {
      output->origin.x = -0.5*eyeSeparation*cos_theta + eyeToNeckDistance*sin_theta;
      output->origin.z = -0.5*eyeSeparation*sin_theta - eyeToNeckDistance*cos_theta;
   }
   else
   {
      output->origin.x = 0.5*eyeSeparation*cos_theta + eyeToNeckDistance*sin_theta;
      output->origin.z = 0.5*eyeSeparation*sin_theta - eyeToNeckDistance*cos_theta;
   }
   

   ////////////////////////////////////////////////////
   // Merge poles to avoid artifacts
   ////////////////////////////////////////////////////

   // merge method:
   //  phi > 0:
   //    linear:
   //      (-2*phi + pi) / (pi - 2*offset)
   //    cos:
   //      ( cos( (phi - offset) * ( pi / (pi - 2*offset) ) ) ) ^ exp
   //  phi < 0:
   //    linear:
   //      (2*phi + pi) / (pi + 2*offset)
   //    cos:
   //      ( cos( (phi - offset) * ( -pi / (pi + 2*offset) ) ) ) ^ exp

   if(phi > topMergeAngle)
   {
      mergeZone = Z_UP;
   }
   else if(phi < bottomMergeAngle)
   {
      mergeZone = Z_BOTTOM;
   }


   float factor = 1.0f;
   if(((topMergeMode == M_LINEAR) && (mergeZone == Z_UP)) ||
      ((bottomMergeMode == M_LINEAR) && (mergeZone == Z_BOTTOM)))
   {
      if(mergeZone == Z_UP)
         factor = (-2.0f * phi + AI_PI) / (AI_PI - 2*topMergeAngle);
      else
         factor = (2.0f * phi + AI_PI) / (AI_PI + 2*bottomMergeAngle);
   }
   else if(((topMergeMode == M_COS) && (mergeZone == Z_UP)) ||
      ((bottomMergeMode == M_COS) && (mergeZone == Z_BOTTOM)))
   {
      if(mergeZone == Z_UP)
         factor = powf( MAX(0.0f, cosf( (phi - topMergeAngle) * (AI_PI / (AI_PI - 2.0f*topMergeAngle)) )), topMergeExp );
      else
         factor = powf( MAX(0.0f, cosf( (phi - bottomMergeAngle) * (-AI_PI / (AI_PI + 2.0f*bottomMergeAngle)) )), bottomMergeExp );
   }
   else if(((topMergeMode == M_SHADER) && (mergeZone == Z_UP)) ||
      ((bottomMergeMode == M_SHADER) && (mergeZone == Z_BOTTOM)))
   {
      if(mergeShader == NULL)
      {
         factor = mergeValue;
      }
      else
      {
         CameraData* data = (CameraData*) AiCameraGetLocalData(node);
         // copy and prepare the Shader Globals
         AtShaderGlobals sg = *(data->sg);
         sg.tid = tid;
         sg.u  = 0.5f * (theta / AI_PI + 1.0f);
         sg.v  = 0.5f * (phi / AI_PIOVER2 + 1.0f);
         
         AiShaderEvaluate(mergeShader, &sg);
         
         factor = sg.out.RGB.r;
      }
   }
   
   output->origin.x *= factor;
   output->origin.z *= factor;

}
node_loader
{
   if (i > 0)
      return false;
   node->methods      = VRCameraMethods;
   node->output_type  = AI_TYPE_NONE;
   node->name         = "vr_camera";
   node->node_type    = AI_NODE_CAMERA;
   strcpy(node->version, AI_VERSION);
   return true;
}
