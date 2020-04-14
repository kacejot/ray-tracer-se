#include "camera.h"

ray camera::cast_ray(double u, double v) {
    return ray{origin, lower_left_corner + u * horizontal + v * vertical - origin};
}
