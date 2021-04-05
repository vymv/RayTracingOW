#pragma once
#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"


class sphere : public hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
	material *mat_ptr;
};


bool sphere::hit(const ray& r, const float t_min, const float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		//根1
		float temp = (-b - sqrt(discriminant)) / a;
		//在tmin tmax之内
		if (temp > t_min && temp < t_max) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		//根2
		temp = (-b + sqrt(discriminant)) / a;
		//在tmin tmax之内
		if (temp > t_min && temp < t_max) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}


#endif