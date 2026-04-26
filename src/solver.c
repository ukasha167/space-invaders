#include "solver.h"

void updateCamera(Camera3D* camera, Vector3 targetPos) {
    camera->position.z = targetPos.z + CAMERA_GAP;
    camera->target.z = targetPos.z - 5;
}

/*
 If you want the camera to have some weight.
 void UpdateCinematicCamera(Camera3D* cam, Vector3 targetPos) {
     Vector3 desiredPos = {
         targetPos.x + SHOULDER_OFFSET.x,
         targetPos.y + SHOULDER_OFFSET.y,
         targetPos.z + SHOULDER_OFFSET.z
     };

     float smoothness = 0.1f; // 0.1f is the smoothness. Lower = more "lag", Higher = tighter.
     cam->position.x += (desiredPos.x - cam->position.x) * smoothness;
     cam->position.y += (desiredPos.y - cam->position.y) * smoothness;
     cam->position.z += (desiredPos.z - cam->position.z) * smoothness;

     cam->target = targetPos;
 }
*/
