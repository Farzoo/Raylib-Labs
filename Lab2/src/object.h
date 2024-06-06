#ifndef LABPROJECTS_OBJECT_H
#define LABPROJECTS_OBJECT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_COMPONENTS (32)

typedef struct ComponentRegistry {
    char *name;
    int id;
} ComponentRegistry;

static ComponentRegistry componentRegistry[MAX_COMPONENTS];
static int componentCount = 0;

#define USING_COMPONENT(type) \
    int COMPONENT_##type##_ID = __COUNTER__; \

static int register_component(const char *componentName) {
    int i;
    for (i = 0; i < componentCount; ++i) {
        if (strcmp(componentRegistry[i].name, componentName) == 0) {
            return componentRegistry[i].id;
        }
    }

    if (i >= MAX_COMPONENTS) {
        fprintf(stderr, "Maximum number of components reached\n");
        exit(1);
    }

    int newId = componentCount;
    componentRegistry[componentCount].name = strdup(componentName);
    componentRegistry[componentCount].id = newId;
    componentCount++;

    return newId;
}

static int objectId = 0;

typedef struct Object {
    int id;
    void *components[MAX_COMPONENTS];
} Object;

Object Create_Object() {
    Object obj = {
        .id = objectId++
    };
    for (int i = 0; i < MAX_COMPONENTS; ++i) {
        obj.components[i] = NULL;
    }
    return obj;
}

void *Add_Component(Object *obj, int componentId, void *component) {
    void *temp = obj->components[componentId];
    if (temp != NULL) {
        return temp;
    }
    obj->components[componentId] = component;
    return component;
}


#define ADD_COMPONENT_INIT(obj, type, ...) \
    ((type *)Add_Component((obj), COMPONENT_##type##_ID, &(type){__VA_ARGS__}))

#define ADD_COMPONENT_PTR(obj, type, ptr) \
    ((type *)Add_Component((obj), COMPONENT_##type##_ID, (void *)(ptr)))





#define GET_COMPONENT(obj, type) \
    ((type *)(obj)->components[COMPONENT_##type##_ID])


#endif //LABPROJECTS_OBJECT_H
