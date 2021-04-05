#include <iostream>
#include <cstdio>
#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "random.h"
#include "material.h"
using namespace std;
#pragma warning(disable:4996)
#define MAXFLOAT 9999999999.0





vec3 color(const ray& r,hitable *world,int depth)
{
	hit_record rec;
	//如果碰撞了，颜色和法线有关
	if (world->hit(r, 0.001, MAXFLOAT, rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		//否则显示蓝白色
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0); //-1,1 -> 0,0.5
		return vec3(1.0, 1.0, 1.0) * (1.0 - t) + vec3(0.5, 0.7, 1.0) * t;
	}

}
int main()
{
	freopen("output.ppm","w", stdout);
	int nx = 600;
	int ny = 300;
	int ns = 100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";
	//vec3 lower_left_corner(-2.0, -1.0, -1.0);
	//vec3 horizontal(4.0, 0.0, 0.0);
	//vec3 vertical(0.0, 2.0, 0.0);
	//vec3 origin(0.0, 0.0, 0.0);


	//创建hitable object
	float R = cos(M_PI / 4);
	hitable * list[5];
	//list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	//list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.3, 0.3, 0.3),0.3));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	hitable *world = new hitable_list(list, 5);

	//主要用于计算ray


	camera cam(vec3(0.2, 1, 0), vec3(0, 0, -1), vec3(0, 1, 0), 90, float(nx) / float(ny));

	for(int j= ny-1;j>=0;j--)
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			//s是做什么的呢，采样抗锯齿
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				//根据每个点的pos，计算每点color
				ray r = cam.get_ray(u, v); //结合camera属性，计算ray的起点，方向
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world,0);
			}

			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			cout << ir << " " << ig << " " << ib << endl;
		}
	return 0;
}