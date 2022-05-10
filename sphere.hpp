#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <iostream>
#include "object.hpp"

namespace raytrace{

class Sphere final : public Object {
private:
  float radius = 0;
public:
  Sphere() : Object() {};

  Sphere(float radius_, const vec3f center) : Object(1, &center) {
    radius = radius_;
  };

  Sphere(std::vector<vec3f> params_) : Object(params_) {};

  float get_radius(){
    return radius;
  }

  virtual vec3f get_center() override final{
    if (this->get_params().size() != 0){
      return this->get_params()[0];
    }
    else{
      std::cout << "ERROR: params not defined, (0, 0, 0) returned\n";
      return vec3f(0, 0, 0);
    }
  }

  virtual void output() override final{
    for (auto i: this->get_params()){
      i.output();
    }
    std::cout << radius << "\n";
  }

  virtual float to_intersection(const vec3f& ray_origin, const vec3f& ray_direction) override final{
    float b = 2 * dot(ray_direction, ray_origin - this->get_center());
    float c = (ray_origin - this->get_center()).magnitute2() - this->get_radius() * this->get_radius();
    float delta = b * b - 4 * c;
    if (delta > 0){
      float t1 = (-b + std::sqrt(delta)) / 2;
      float t2 = (-b - std::sqrt(delta)) / 2;
      if (t1 > 0 && t2 > 0){
        return std::min(t1, t2);
      }
    }
    return -1;
  }

  virtual vec3f normal_to_surface(const vec3f& intersection) override final{
    return (intersection - this->get_center()).normalized();
  }

};

}

#endif
