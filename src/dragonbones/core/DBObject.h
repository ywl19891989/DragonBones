/*
 * DBObject.h
 *
 *  Created on: 2014-2-25
 *      Author: Hali
 */

#ifndef DBOBJECT_H_
#define DBOBJECT_H_

#include "DBMacros.h"
#include <string>

class Matrix;
class Bone;
class Armature;
class DBTransform;
class DBObject {
public:
	DBObject();
	virtual ~DBObject();

	/**
	 * The name of this DBObject instance's Armature instance.
	 */
	std::string name;

	/**
	 * An object that can contain any user extra data.
	 */
//	public var userData:Object;
	bool fixedRotation;

	DBTransform* getGlobal();
	DBTransform* getOrigin();
	DBTransform* getOffset();
	DBTransform* getNode();

	virtual bool getVisible();
	virtual void setVisible(bool value);

	/**
	 * Indicates the Bone instance that directly contains this DBObject instance if any.
	 */
	Bone* getParent();
	void setParent(Bone* value);

	/**
	 * The armature this DBObject instance belongs to.
	 */
	virtual Armature* getArmature();
	virtual void setArmature(Armature* value);

	virtual void dispose();
	virtual void update();

protected:
	int _scaleType;
	Matrix* _globalTransformMatrix;
	bool _isColorChanged;
	DBTransform* _global;
	DBTransform* _origin;
	DBTransform* _tween;
	DBTransform* _offset;

	bool _visible;
	Bone* _parent;

	Armature* _armature;
};

#endif /* DBOBJECT_H_ */
