#include "tunnel.h"

void Tunnel::set(float radius, int tunnelSegments, float segmentDistance, int segmentPoints, int baseFrameOffset) {

	// set the object variables
	this->radius = radius;
	this->tunnelSegments = tunnelSegments;
	this->segmentDistance = segmentDistance;
	this->bassFrameOffset = baseFrameOffset;

	segmentPoints = segmentPoints + 1;
	if (segmentPoints < 3) segmentPoints = 3;
	if (tunnelSegments < 2) tunnelSegments = 2;

	this->segmentPoints = segmentPoints;

	lineColor.set(255, 255, 255, 255);

	bassBuffer.setup(tunnelSegments * baseFrameOffset + lerpOffset + 1);

	ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLE_STRIP;

	ofMesh mesh;
	mesh.setMode(mode);
	getMesh() = mesh;

	buildTunnel();

}

void Tunnel::buildTunnel() {

	ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLE_STRIP;

	ofMesh mesh;
	mesh.setMode(mode);

	float height = (tunnelSegments - 1) * segmentDistance * 2;

	float angleIncRadius = -1 * (glm::two_pi<float>() / ((float)segmentPoints - 1.f));
	float heightInc = segmentDistance;

	float minTexYNormalized = 0;
	float maxTexYNormalized = 1.f;

	ofPoint vert;
	ofVec2f tcoord;

	// cylinder vertices //
	for (int iy = 0; iy < tunnelSegments; iy++) {
		for (int ix = 0; ix < segmentPoints ; ix++) {

			//newRad = ofMap((float)iy, 0, heightSegments-1, 0.0, radius);
			vert.x = cos(ix * angleIncRadius) * radius;
			vert.y = heightInc * float(iy);
			vert.z = sin(ix * angleIncRadius) * radius;

			tcoord.x = float(ix) / (float(segmentPoints) - 1.f);
			tcoord.y = 1.f - ofMap(iy, 0, tunnelSegments - 1, minTexYNormalized, maxTexYNormalized);

			mesh.addTexCoord(tcoord);
			mesh.addVertex(vert);
			mesh.addColor(lineColor);

		}
	}

	for (int y = 0; y < tunnelSegments - 1; y++) {
		for (int x = 0; x < segmentPoints ; x++) {
			mesh.addIndex((y) * segmentPoints + x);
			mesh.addIndex((y + 1) * segmentPoints + x);
		}
	}

	getMesh() = mesh;

}

void Tunnel::buildTunnelInc(int index) {

	ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLE_STRIP;

	ofMesh mesh;
	mesh.setMode(mode);

	float height = (tunnelSegments - 1) * segmentDistance * 2;

	float angleIncRadius = -1 * (glm::two_pi<float>() / ((float)segmentPoints - 1.f));
	float heightInc = segmentDistance;

	float minTexYNormalized = 0;
	float maxTexYNormalized = 1.f;

	ofPoint vert;
	ofVec2f tcoord;

	int totalSegmentsToDraw = (index / segmentPoints) + 1;

	if (!(totalSegmentsToDraw >= tunnelSegments + 1)) {

		// cylinder vertices //
		for (int iy = 0; iy < totalSegmentsToDraw; iy++) {

			int pointsToDraw = (index / segmentPoints) + (index % segmentPoints);

			if (pointsToDraw == segmentPoints - 1) {
				pointsToDraw++;
			}

			for (int ix = 0; ix < pointsToDraw; ix++) {

				//newRad = ofMap((float)iy, 0, heightSegments-1, 0.0, radius);
				vert.x = cos(ix * angleIncRadius) * radius;
				vert.y = heightInc * float(iy);
				vert.z = sin(ix * angleIncRadius) * radius;

				tcoord.x = float(ix) / (float(segmentPoints) - 1.f);
				tcoord.y = 1.f - ofMap(iy, 0, tunnelSegments - 1, minTexYNormalized, maxTexYNormalized);

				mesh.addTexCoord(tcoord);
				mesh.addVertex(vert);
				mesh.addColor(lineColor);

			}
		}

		for (int y = 0; y < totalSegmentsToDraw - 1; y++) {

			int pointsToDraw = (index / segmentPoints) + (index % segmentPoints);

			if (pointsToDraw == segmentPoints - 1) {
				pointsToDraw++;
			}

			for (int x = 0; x < pointsToDraw; x++) {
				mesh.addIndex((y)*segmentPoints + x);
				mesh.addIndex((y + 1) * segmentPoints + x);
			}
		}

		getMesh() = mesh;

	}
	else {
		buildTunnel();
	}

}

void Tunnel::addSegment() {

	tunnelSegments++;

	ofMesh mesh = getMesh();

	float height = (tunnelSegments - 1) * segmentDistance;

	float angleIncRadius = -1 * (glm::two_pi<float>() / ((float)segmentPoints - 1.f));
	float heightInc = segmentDistance;

	std::size_t vertOffset = mesh.getNumVertices();

	float minTexYNormalized = 0;
	float maxTexYNormalized = 1.f;

	ofPoint vert;
	ofVec2f tcoord;

	for (int ix = 0; ix < segmentPoints; ix++) {

		vert.x = cos(ix * angleIncRadius) * radius;
		vert.y = heightInc + mesh.getVertex(vertOffset - 1).y;
		vert.z = sin(ix * angleIncRadius) * radius;

		tcoord.x = float(ix) / (float(segmentPoints) - 1.f);
		tcoord.y = 1.f - ofMap(tunnelSegments - 1, 0, tunnelSegments - 1, minTexYNormalized, maxTexYNormalized);

		mesh.addTexCoord(tcoord);
		mesh.addVertex(vert);
		mesh.addColor(ofColor(lineColor.r, lineColor.g, lineColor.b, 0));

	}

	for (int x = 0; x < segmentPoints; x++) {
		mesh.addIndex((tunnelSegments - 2) * segmentPoints + x);
		mesh.addIndex((tunnelSegments - 1) * segmentPoints + x);
	}

	getMesh() = mesh;
	baseMesh = mesh;

}

void Tunnel::removeSegment() {

	ofMesh mesh = getMesh();
	mesh = mesh.getMeshForIndices(segmentPoints * 2, segmentPoints * 2 * (tunnelSegments - 1));

	tunnelSegments--;

	getMesh() = mesh;
	baseMesh = mesh;

}

void Tunnel::rebuildSegments() {

	removeSegment();
	addSegment();

	ofMesh mesh = getMesh();
	std::vector<ofDefaultVertexType> vertices = mesh.getVertices();

	for (int i = 0; i < mesh.getNumVertices(); i++) {
		vertices[i].y -= segmentDistance;
	}

	mesh.getVertices() = vertices;

	getMesh() = mesh;
	baseMesh = mesh;

}

void Tunnel::fadeInNewSegment(float tunnelIncrement, bool isNewSegementFrame) {

	ofMesh mesh = getMesh();

	std::size_t numColors = mesh.getNumColors();
	ofColor currentColor = mesh.getColor(numColors - 1 - segmentPoints);

	if (!isNewSegementFrame) {

		if (currentColor.a < 255.f) {

			colorFadeAmount += (tunnelIncrement / segmentDistance) * 0.65; // fade in speed
			float alpha = 255.f * colorFadeAmount;

			if (alpha >= 255.f) {
				alpha = 255.f;
			}

			for (int i = 0; i < segmentPoints; i++) {
				mesh.setColor(numColors - 1 - segmentPoints - i,
					ofColor(currentColor.r, currentColor.g, currentColor.b, alpha));
			}

		}
	}

	else {

		colorFadeAmount = 0.0;

		for (int i = 0; i < segmentPoints; i++) {
			mesh.setColor(numColors - 1 - (segmentPoints * 2) - i,
				ofColor(currentColor.r, currentColor.g, currentColor.b, 255.f));
		}

	}

	getMesh() = mesh;

}

void Tunnel::bassDistort()
{

	int bassLerpIndex = ofGetFrameNum() % lerpOffset;

	ofMesh mesh = getMesh();

	for(int i = 0; i < tunnelSegments; i++) {

		float bassGain = bassBuffer.getSample((i * bassFrameOffset) + bassLerpIndex);
		float lastBassGain = bassBuffer.getSample((i * bassFrameOffset) + bassLerpIndex + lerpOffset);
		
		float distortedRadius = radius + (ofLerp(lastBassGain, bassGain, (bassLerpIndex + 1.f) / lerpOffset) * 2.f);

		for (int ix = 0; ix < segmentPoints; ix++) {

			int vertIndex = (segmentPoints * i) + ix;

			ofPoint vert = mesh.getVertex(vertIndex);
			ofVec2f distortedPoint = segmentDrawFunction(ix, distortedRadius);

			vert.x = distortedPoint.x;
			vert.z = distortedPoint.y;

			mesh.setVertex(vertIndex, vert);		
		}
	}

	getMesh() = mesh;
}

void Tunnel::lineColorBlack()
{

	lineColor.set(0, 0, 0, 255);

}

void Tunnel::lineColorWhite()
{

	lineColor.set(255, 255, 255, 255);

}

ofVec2f Tunnel::segmentDrawFunction(int ix, float radius)
{
	ofVec2f vector;

	float angleIncRadius = -1 * (glm::two_pi<float>() / ((float)segmentPoints - 1.f));

	vector.x = cos(ix * angleIncRadius) * radius;
	vector.y = sin(ix * angleIncRadius) * radius;

	return vector;
}

void Tunnel::updateTunnel(float speed, double lastFrameTime, float x, float y, float bassGain) {

	float tunnelIncrement = segmentDistance * (lastFrameTime * speed);
	localTunnelPosition += tunnelIncrement;

	if (localTunnelPosition > segmentDistance) {
		rebuildSegments();
		localTunnelPosition -= segmentDistance;
		fadeInNewSegment(tunnelIncrement, true);
	}

	else {
		fadeInNewSegment(tunnelIncrement, false);
	}

	if (bassGain < bassThreshhold) {
		bassGain = 0.f;
	}
	else {
		ofClamp(bassGain -= bassThreshhold, 0.f, 1.f);
	}

	bassBuffer.pushSample(bassGain);

	bassDistort();

	setPosition(x, y, localTunnelPosition);
}