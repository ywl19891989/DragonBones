/*
 * TransformUtil.cpp
 *
 *  Created on: 2014-2-16
 *      Author: Hali
 */

#include "TransformUtil.h"
#include "dragonbones/objects/DBTransform.h"
#include <math.h>

const float TransformUtil::HALF_PI = M_PI * 0.5f;
const float TransformUtil::DOUBLE_PI = M_PI * 2.0f;

Matrix TransformUtil::_helpMatrix;

Matrix::Matrix(){
	identity();
}

void Matrix::set(float a, float b, float c, float d, float tx, float ty){
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->tx = tx;
	this->ty = ty;
}

void Matrix::identity(){
	set(1, 0, 0, 1, 0, 0);
}

void Matrix::invert() {

	float va = d / (a * d - b * c);
	float vb = b / (b * c - a * d);
	float vc = c / (b * c - a * d);
	float vd = a / (a * d - b * c);
	float vtx = (c * ty - d * tx) / (a * d - b * c);
	float vty = (a * ty - b * tx) / (b * c - a * d);

	set(va, vb, vc, vd, vtx, vty);
}

TransformUtil::TransformUtil() {
	// TODO Auto-generated constructor stub

}

TransformUtil::~TransformUtil() {
	// TODO Auto-generated destructor stub
}

void TransformUtil::transformPointWithParent(DBTransform & transform, DBTransform& parent) {
	transformToMatrix(parent, _helpMatrix);
	_helpMatrix.invert();

	float x = transform.x;
	float y = transform.y;

	transform.x = _helpMatrix.a * x + _helpMatrix.c * y + _helpMatrix.tx;
	transform.y = _helpMatrix.d * y + _helpMatrix.b * x + _helpMatrix.ty;

	transform.skewX = formatRadian(transform.skewX - parent.skewX);
	transform.skewY = formatRadian(transform.skewY - parent.skewY);
}

void TransformUtil::transformToMatrix(DBTransform & transform, Matrix & matrix) {
	matrix.a = transform.scaleX * cos(transform.skewY);
	matrix.b = transform.scaleX * sin(transform.skewY);
	matrix.c = -transform.scaleY * sin(transform.skewX);
	matrix.d = transform.scaleY * cos(transform.skewX);
	matrix.tx = transform.x;
	matrix.ty = transform.y;
}

float TransformUtil::formatRadian(float radian) {
	while (radian > M_PI) {
		radian -= DOUBLE_PI;
	}
	while (radian < -M_PI) {
		radian += DOUBLE_PI;
	}
	return radian;
}
