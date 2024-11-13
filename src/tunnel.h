#pragma once
#include <of3dPrimitives.h>

class Tunnel : public of3dPrimitive {

public:

	void set(float radius, int tunnelSegments, float segmentDistance, int segmentPoints);

	void addSegment();

	void removeSegment();

private:

	float radius;
	int tunnelSegments;
	float segmentDistance;
	int segmentPoints;

	
};
