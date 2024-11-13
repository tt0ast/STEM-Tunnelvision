#include "tunnel.h"

void Tunnel::set(float radius, int tunnelSegments, float segmentDistance, int segmentPoints) {

	// set the object variables
	this->radius = radius;
	this->tunnelSegments = tunnelSegments;
	this->segmentDistance = segmentDistance;
	this->segmentPoints = segmentPoints;

	ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLE_STRIP;

	ofMesh mesh;
	mesh.setMode(mode);

	segmentPoints = segmentPoints + 1;
	if (segmentPoints < 3) segmentPoints = 3;
	if (tunnelSegments < 2) tunnelSegments = 2;

	float height = (tunnelSegments - 1) * segmentDistance;

	float angleIncRadius = -1 * (glm::two_pi<float>() / ((float)segmentPoints - 1.f));
	float heightInc = segmentDistance;
	float halfH = height * .5f;

	float minTexYNormalized = 0;
	float maxTexYNormalized = 1.f;

	ofPoint vert;
	ofVec2f tcoord;

	// cylinder vertices //
	for (int iy = 0; iy < tunnelSegments; iy++) {
		for (int ix = 0; ix < segmentPoints ; ix++) {

			//newRad = ofMap((float)iy, 0, heightSegments-1, 0.0, radius);
			vert.x = cos(ix * angleIncRadius) * radius;
			vert.y = heightInc * float(iy) - halfH;
			vert.z = sin(ix * angleIncRadius) * radius;

			tcoord.x = float(ix) / (float(segmentPoints) - 1.f);
			tcoord.y = 1.f - ofMap(iy, 0, tunnelSegments - 1, minTexYNormalized, maxTexYNormalized);

			mesh.addTexCoord(tcoord);
			mesh.addVertex(vert);
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

void Tunnel::addSegment() {

	tunnelSegments++;
	int segmentPoints = this->segmentPoints;
	segmentPoints++;

	ofMesh mesh = getMesh();

	float height = (tunnelSegments - 1) * segmentDistance;

	float angleIncRadius = -1 * (glm::two_pi<float>() / ((float)segmentPoints - 1.f));
	float heightInc = segmentDistance;
	float halfH = height * .5f;

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
	}

	for (int x = 0; x < segmentPoints; x++) {
		mesh.addIndex((tunnelSegments - 2) * segmentPoints + x);
		mesh.addIndex((tunnelSegments - 1) * segmentPoints + x);
	}

	getMesh() = mesh;

}

void Tunnel::removeSegment() {

	ofMesh mesh = getMesh();
	mesh = mesh.getMeshForIndices((segmentPoints + 1) * 2, (segmentPoints + 1) * 2 * (tunnelSegments - 1));
	getMesh() = mesh;

	tunnelSegments--;

}