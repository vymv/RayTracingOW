#pragma once
#include <iostream>
#include <cstdio>
float drand48()
{
	return rand() / (RAND_MAX + 1.0);
}