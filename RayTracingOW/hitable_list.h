#pragma once
#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list : public hitable {
public:
	hitable **list;
	int list_size;

	hitable_list() {}
	hitable_list(hitable **l, int n) { list = l; list_size = n; }

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	//根据t的大小判断远近
	double closest_so_far = t_max;
	for (int i = 0; i < list_size; i++) {
		//更远的碰撞点，就无需渲染了，调用子方法
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}


#endif