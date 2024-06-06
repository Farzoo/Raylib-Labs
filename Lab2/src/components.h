#ifndef LABPROJECTS_COMPONENTS_H
#define LABPROJECTS_COMPONENTS_H

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "object.h"

typedef struct TransformComp {
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
} TransformComp;


#endif //LABPROJECTS_COMPONENTS_H
