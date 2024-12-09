#pragma once
#include <of3dPrimitives.h>
#include "util/delayLine.h"
#include <ofMath.h>

class Tunnel : public of3dPrimitive {

public:

	void set(float radius, int tunnelSegments, float segmentDistance, int segmentPoints, int bassFrameOffset);

	void updateTunnel(float speed, double lastFrameTime, float x, float y, float bassGain);

	void buildTunnel();

	void buildTunnelInc(int index);

	void addSegment();

	void removeSegment();

	void rebuildSegments();

	void fadeInNewSegment(float tunnelIncrement, bool isNewSegmentFrame);

	void bassDistort();

	void lineColorBlack();

	void lineColorWhite();
	
private:

	ofVec2f segmentDrawFunction(int ix, float radius);

	float radius;
	int tunnelSegments;
	float segmentDistance;
	int segmentPoints;

	int lerpOffset = 6;
	int bassFrameOffset = 2;
	float bassThreshhold = 0.6;

	float localTunnelPosition = 0.f;

	ofColor lineColor;
	float colorFadeAmount;

	ofMesh baseMesh;

	DelayLine bassBuffer;
};
