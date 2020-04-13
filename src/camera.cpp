#include "camera.h"

ray camera::cast_ray(float u, float v) {
    return ray{origin, lower_left_corner + u * horizontal + v * vertical - origin};
}
