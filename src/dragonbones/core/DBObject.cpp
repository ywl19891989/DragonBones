/*
 * DBObject.cpp
 *
 *  Created on: 2014-2-25
 *      Author: Hali
 */

#include "DBObject.h"
#include "dragonbones/objects/DBTransform.h"
#include "dragonbones/utils/TransformUtil.h"
#include "dragonbones/Armature.h"
#include "dragonbones/Bone.h"
#include "dragonbones/Slot.h"
#include <math.h>

DBObject::DBObject() :
		fixedRotation(false), _scaleType(-1), _isColorChanged(false), _parent(NULL), _armature(NULL){
	// TODO Auto-generated constructor stub
	_global = new DBTransform();
	_origin = new DBTransform();
	_offset = new DBTransform();
	_tween = new DBTransform();
	_tween->scaleX = _tween->scaleY = 0;

	_globalTransformMatrix = new Matrix();

	_visible = true;
}

DBObject::~DBObject() {
	// TODO Auto-generated destructor stub
}

/**
 * This DBObject instance global transform instance.
 * @see dragonBones.objects.DBTransform
 */
DBTransform* DBObject::getGlobal() {
	return _global;
}

/**
 * This DBObject instance origin transform instance.
 * @see dragonBones.objects.DBTransform
 */
DBTransform* DBObject::getOrigin() {
	return _origin;
}

/**
 * This DBObject instance offset transform instance.
 * @see dragonBones.objects.DBTransform
 */
DBTransform* DBObject::getOffset() {
	return _offset;
}

DBTransform* DBObject::getNode() {
	return _offset;
}

bool DBObject::getVisible() {
	return _visible;
}

void DBObject::setVisible(bool value) {
	_visible = value;
}

/**
 * Indicates the Bone instance that directly contains this DBObject instance if any.
 */
Bone* DBObject::getParent() {
	return _parent;
}

void DBObject::setParent(Bone* value) {
	_parent = value;
}

Armature* DBObject::getArmature() {
	return _armature;
}

void DBObject::setArmature(Armature* value) {
	if (_armature) {
		_armature->removeDBObject(this);
	}
	_armature = value;
	if (_armature) {
		_armature->addDBObject(this);
	}
}

/**
 * Cleans up any resources used by this DBObject instance.
 */
void DBObject::dispose() {
//	userData = NULL;
	_parent = NULL;
	_armature = NULL;
	_global = NULL;
	_origin = NULL;
	_offset = NULL;
	_tween = NULL;
	_globalTransformMatrix = NULL;
}

void DBObject::update() {
	_global->scaleX = (_origin->scaleX + _tween->scaleX) * _offset->scaleX;
	_global->scaleY = (_origin->scaleY + _tween->scaleY) * _offset->scaleY;

	if (_parent) {
		float x = _origin->x + _offset->x + _tween->x;
		float y = _origin->y + _offset->y + _tween->y;
		Matrix* parentMatrix = _parent->_globalTransformMatrix;

		_globalTransformMatrix->tx = _global->x = parentMatrix->a * x + parentMatrix->c * y + parentMatrix->tx;
		_globalTransformMatrix->ty = _global->y = parentMatrix->d * y + parentMatrix->b * x + parentMatrix->ty;

		if (fixedRotation) {
			_global->skewX = _origin->skewX + _offset->skewX + _tween->skewX;
			_global->skewY = _origin->skewY + _offset->skewY + _tween->skewY;
		} else {
			_global->skewX = _origin->skewX + _offset->skewX + _tween->skewX + _parent->_global->skewX;
			_global->skewY = _origin->skewY + _offset->skewY + _tween->skewY + _parent->_global->skewY;
		}

		if (_parent->scaleMode >= _scaleType) {
			_global->scaleX *= _parent->getGlobal()->scaleX;
			_global->scaleY *= _parent->getGlobal()->scaleY;
		}
	} else {
		_globalTransformMatrix->tx = _global->x = _origin->x + _offset->x + _tween->x;
		_globalTransformMatrix->ty = _global->y = _origin->y + _offset->y + _tween->y;

		_global->skewX = _origin->skewX + _offset->skewX + _tween->skewX;
		_global->skewY = _origin->skewY + _offset->skewY + _tween->skewY;
	}

	_globalTransformMatrix->a = _global->scaleX * cosf(_global->skewY);
	_globalTransformMatrix->b = _global->scaleX * sinf(_global->skewY);
	_globalTransformMatrix->c = -_global->scaleY * sinf(_global->skewX);
	_globalTransformMatrix->d = _global->scaleY * cosf(_global->skewX);
}

