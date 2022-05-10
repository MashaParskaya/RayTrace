#ifndef BOX_HPP
#define BOX_HPP

#include <iostream>
#include "object.hpp"

namespace raytrace{

class Box final : public Object {
public:
  Box() : Object() {};

  Box(const vec3f first, const vec3f second) : Object(std::vector<vec3f>{first, second}) {};

  Box(std::vector<vec3f>& params_) : Object(params_) {};

  virtual vec3f get_center() override final{
    if (this->get_params().size() != 0){
      return (this->get_params()[0] + this->get_params()[1]) / 2;
    }
    else{
      std::cout << "ERROR: params not defined, (0, 0, 0) returned\n";
      return vec3f();
    }
  }

  virtual void output() override final{
    for (auto i: this->get_params()){
      i.output();
    }
  }

  bool has(const vec3f& point){
    bool answer = (this->get_params()[0].getX() - point.getX() < 1e-5 && this->get_params()[1].getX() - point.getX() > -1e-5 &&
                   this->get_params()[0].getY() - point.getY() < 1e-5 && this->get_params()[1].getY() - point.getY() > -1e-5 &&
                   this->get_params()[0].getZ() - point.getZ() < 1e-5 && this->get_params()[1].getZ() - point.getZ() > -1e-5);
    return answer;
  }

  virtual float to_intersection(const vec3f& ray_origin, const vec3f& ray_direction) override final{
    std::vector<float> possible_t = {};

    if (ray_direction.getX() != 0){
      float t1 = (this->get_params()[0].getX() - ray_origin.getX()) / ray_direction.getX();
      vec3f i1 = ray_origin + ray_direction * t1;
      if (this->has(i1) && t1 > 0){
            possible_t.push_back(t1);
      }
      float t2 = (this->get_params()[1].getX() - ray_origin.getX()) / ray_direction.getX();
      vec3f i2 = ray_origin + ray_direction * t2;
      if (this->has(i2) && t2 > 0){
            possible_t.push_back(t2);
      }
    }

    if (ray_direction.getY() != 0){
      float t1 = (this->get_params()[0].getY() - ray_origin.getY()) / ray_direction.getY();
      vec3f i1 = ray_origin + ray_direction * t1;
      if (this->has(i1) && t1 > 0){
            possible_t.push_back(t1);
      }
      float t2 = (this->get_params()[1].getY() - ray_origin.getY()) / ray_direction.getY();
      vec3f i2 = ray_origin + ray_direction * t2;
      if (this->has(i2) && t2 > 0){
            possible_t.push_back(t2);
      }
    }

    if (ray_direction.getZ() != 0){
      float t1 = (this->get_params()[0].getZ() - ray_origin.getZ()) / ray_direction.getZ();
      vec3f i1 = ray_origin + ray_direction * t1;
      if (this->has(i1) && t1 > 0){
            possible_t.push_back(t1);
      }
      float t2 = (this->get_params()[1].getZ() - ray_origin.getZ()) / ray_direction.getZ();
      vec3f i2 = ray_origin + ray_direction * t2;
      if (this->has(i2) && t2 > 0){
            possible_t.push_back(t2);
      }
    }

    if (possible_t.size() > 0){
      float mini = -1;
      for (auto t: possible_t){
        if (mini < 0 || t < mini){
          mini = t;
        }
      }
      return mini;
    }
    return -1;
  }

  virtual vec3f normal_to_surface(const vec3f& intersection) override final{
    if (fabs(intersection.getX() - this->get_params()[0].getX()) < 1e-5){
      return vec3f(-1, 0, 0);
    }
    else if (fabs(intersection.getY() - this->get_params()[0].getY()) < 1e-5){
      return vec3f(0, -1, 0);
    }
    else if (fabs(intersection.getZ() - this->get_params()[0].getZ()) < 1e-5){
      return vec3f(0, 0, -1);
    }
    else if (fabs(intersection.getX() - this->get_params()[1].getX()) < 1e-5){
      return vec3f(1, 0, 0);
    }
    else if (fabs(intersection.getY() - this->get_params()[1].getY()) < 1e-5){
      return vec3f(0, 1, 0);
    }
    else if (fabs(intersection.getZ() - this->get_params()[1].getZ()) < 1e-5){
      return vec3f(0, 0, 1);
    }
    std::cout << "ERROR: intersection does not belong to Box, (0, 0, 0) returned";
    return vec3f(0, 0, 0);
  }

};

}

#endif
