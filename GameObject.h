#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "Settings.h"
#include "physics/body.h"
#include "physics/mhelp.h"
#include "physics/contacts.h"
#include "physics/collide_fine.h"

#include "factories/Meshes.h"
#include "graphics/render.h"

class BoxBody : public CollisionBox
{
public:
	BoxBody(RigidBody * b1, Vector3 hs)
	{
		body = b1;
		halfSize = hs;
	}
};

class SphereBody : public CollisionSphere
{
public:
	SphereBody(RigidBody * b1, float r)
	{
		body = b1;
		radius = r;
	}
};


class GameObject
{
public:

	int m_id;
	
	RigidBody * m_body;
	Render * m_render;
	Vector3 half_size;

	/*
		ai
	*/
	GameObject * m_target;

	enum ObjectState
	{
		ACTIVE,
		DESTROYED
	};
	ObjectState state;

	GameObject(): 
		state(ObjectState::ACTIVE)
	{

	};

	GameObject(RigidBody* b, Render* r, int i) :
		m_body(b), m_render(r), m_id(i), state(ObjectState::ACTIVE)
	{
	
	};

	virtual void update(float duration)
	{
		m_body->integrate(duration);
	};

	virtual void translate(bool up, float force)
	{
		Vector3 dir = get_dir();
		if (!up)
			dir.invert();

		dir *= force;
		m_body->setVelocity(dir);
	};

	virtual void rotate(bool up, float force)
	{
		Vector3 rot = Vector3(0, force, 0); //tanks::grad_to_rad(5)
		if (!up)
			rot.invert();

		m_body->setRotation(rot);
	};

	virtual void shoot() {};

	virtual void render()
	{
		// Get the OpenGL transformation
		GLfloat mat[16];
		m_body->getGLTransform(mat);

		glm::mat4 tras_mat = glm::make_mat4(mat);
		m_render->render(tras_mat);
	}

	Vector3 get_pos()
	{
		return m_body->getPosition();
	}

	Quaternion get_orient()
	{
		return m_body->getOrientation();
	}

	Vector3 get_dir()
	{
		Vector3 pos = m_body->getPosition();
		Quaternion orient = m_body->getOrientation();
		Matrix4 mat = Matrix4();
		mat.setOrientationAndPos(orient, pos);
		Vector3 dir = mat.transformDirection(Vector3(0, 0, 1));

		dir.normalise();
		return dir;
	}
};


/*class GameObject
{
public:
	
	int m_id;
	
	Render * m_render;
	glm::mat4 model_view;

	glm::vec3 m_position;
	glm::quat m_rotation;
	
	enum ObjectState
	{
		ACTIVE,
		DESTROYED,
		CHANGED,
		WAITING
	};
	ObjectState state;
	
	GameObject()
	{
		m_position = glm::vec3(0, 0, 0);
		m_rotation = glm::angleAxis(glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
		model_view = glm::mat4(1.0);
	};

	GameObject(glm::vec3 pos, float rot, Render* ren, int i) :
		m_render(ren), m_id(i)
	{
		m_position = pos;
		m_rotation = glm::angleAxis(glm::radians(rot), glm::vec3(0.f, 0.f, 1.f));
		update();
	};

	void translate(float tr)
	{
		glm::vec3 dir = get_dir();
		glm::vec3 trans = dir * tr;
		m_position += trans;
	}

	void rotate(float rt)
	{
		glm::quat rot = glm::angleAxis(glm::radians(rt), glm::vec3(0.f, 0.f, 1.f));
		m_rotation *= rot;
	}

	void update()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0), m_position);
		glm::mat4 rotate = glm::mat4_cast(m_rotation);
		model_view = translate * rotate;
	}

	virtual void render()
	{
		m_render->render(model_view);
	}

	glm::vec3 get_dir()
	{
		glm::vec3 base = glm::vec3(1, 0, 0);
		glm::vec3 res = glm::cross(m_rotation, base);
		return glm::normalize(res);
	}

	glm::vec3 get_pos()
	{
		return m_position;
	}
};
*/
#endif /* GAME_OBJECT_H_ */