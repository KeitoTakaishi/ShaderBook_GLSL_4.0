#include "MatrixUtil.h"

ofMatrix4x4 getViewMatrix(ofVec3f eye, ofVec3f up, ofVec3f center) {
	float eyeX = eye[0], eyeY = eye[1], eyeZ = eye[2],
		upX = up[0], upY = up[1], upZ = up[2],
		centerX = center[0], centerY = center[1], centerZ = center[2];

	//if (eyeX == centerX && eyeY == centerY && eyeZ == centerZ) { return this.identity(dest); }
	float x0, x1, x2, y0, y1, y2, z0, z1, z2, l;
	z0 = eyeX - center[0]; z1 = eyeY - center[1]; z2 = eyeZ - center[2];
	l = 1 / sqrt(z0 * z0 + z1 * z1 + z2 * z2);
	z0 *= l; z1 *= l; z2 *= l;
	x0 = upY * z2 - upZ * z1;
	x1 = upZ * z0 - upX * z2;
	x2 = upX * z1 - upY * z0;
	l = sqrt(x0 * x0 + x1 * x1 + x2 * x2);
	if (!l) {
		x0 = 0; x1 = 0; x2 = 0;
	}
	else {
		l = 1 / l;
		x0 *= l; x1 *= l; x2 *= l;
	}
	y0 = z1 * x2 - z2 * x1; y1 = z2 * x0 - z0 * x2; y2 = z0 * x1 - z1 * x0;
	l = sqrt(y0 * y0 + y1 * y1 + y2 * y2);
	if (!l) {
		y0 = 0; y1 = 0; y2 = 0;
	}
	else {
		l = 1 / l;
		y0 *= l; y1 *= l; y2 *= l;
	}
	ofMatrix4x4 view = ofMatrix4x4(
		x0, y0, z0, 0.0,
		x1, y1, z1, 0.0,
		x2, y2, z2, 0.0,
		-(x0 * eyeX + x1 * eyeY + x2 * eyeZ), -(y0 * eyeX + y1 * eyeY + y2 * eyeZ), -(z0 * eyeX + z1 * eyeY + z2 * eyeZ), 1.0
	);

	return view;
}

//--------------------------------------------------------------
ofMatrix4x4 getProjMatrix(float fov, float aspect, float n, float f) {
	float r = 1 / tan(fov * PI / 360);
	float _far = f;
	float _near = n;
	float d = _far - _near;
	ofMatrix4x4 proj = ofMatrix4x4(
		r / aspect, 0.0, 0.0, 0.0,
		0.0, r, 0.0, 0.0,
		0.0, 0.0, -(_far + _near) / d, -1.0,
		0.0, 0.0, -(_far * _near * 2) / d, 0.0
	);
	return proj;
}