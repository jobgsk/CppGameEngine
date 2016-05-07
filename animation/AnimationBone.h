#ifndef ANIMATION_BONE_H_
#define ANIMATION_BONE_H_

//#include "../physics/core.h"
#include "../physics/body.h"
#include "../graphics/render.h"

class AnimationBone
{
public:

	int m_id;
	std::string m_name;
	Matrix4 m_transformation;
	Matrix4 m_init_transformation;
	Render * m_render;
	
	AnimationBone()
	{

	};

	AnimationBone(float px, float py, float pz,
					float w, float vx, float vy, float vz, 
					int bid, std::string bname) :
		m_id(bid),
		m_name(bname)
	{
		RigidBody * b1 = new RigidBody();
		b1->setPosition(px, py, pz);

		Quaternion q1 = Quaternion(w, Vector3(vx, vy, vz));
		b1->setOrientation(q1);

		//b1->setMass(m_owner->m_body->getMass());
		//b1->setDamping(0.1, 0.001);
		b1->calculateDerivedData();
		//GameObject * bone1 = new GameObject(b1, new Render(), bid, bname);
		
		
		/*Vector3 pos = Vector3(px, py, pz);
		Quaternion q1 = Quaternion(w, Vector3(vx, vy, vz));
		
		m_init_transformation = Matrix4();
		m_init_transformation.setOrientationAndPos(q1, pos);
		*/
		b1->getTransform(&m_init_transformation);
		m_transformation = m_init_transformation;
	};

	virtual void render()
	{
		// Get the OpenGL transformation
		GLfloat mat[16];
		m_transformation.fillGLArray(mat);

		if (m_render)
		{
			glm::mat4 tras_mat = glm::make_mat4(mat);
			m_render->render(tras_mat);
		}
	}
};

#endif /* ANIMATION_BONE_H_ */
