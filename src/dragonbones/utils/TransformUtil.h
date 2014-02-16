/*
 * TransformUtil.h
 *
 *  Created on: 2014-2-16
 *      Author: Hali
 */

#ifndef TRANSFORMUTIL_H_
#define TRANSFORMUTIL_H_

class Matrix {
public:

	Matrix();

	float a, b, c, d, tx, ty;

	void set(float a, float b, float c, float d, float tx, float ty);
	void identity();
	void invert();
};

class DBTransform;
class TransformUtil {
public:
	TransformUtil();
	virtual ~TransformUtil();

	static void transformPointWithParent(DBTransform & transform, DBTransform& parent);

	static void transformToMatrix(DBTransform & transform, Matrix & matrix);

	static float formatRadian(float radian);

private:
	static const float HALF_PI;
	static const float DOUBLE_PI;

	static Matrix _helpMatrix;
};

#endif /* TRANSFORMUTIL_H_ */
