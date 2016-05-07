#ifndef MESH_FACTORY_H_
#define MESH_FACTORY_H_

#include "../graphics/render.h"
//class MeshRender;
class MeshFactory {

	static MeshRender *box1_render;
	static MeshRender *panel1_render;
	static MeshRender *plain_render;
	static MeshRender *ceiling_render;
	static MeshRender *bullet_render;

	static MeshRender *obese_male_body_render;
	static MeshRender *obese_male_bottom_left_hend_render;
	static MeshRender *obese_male_bottom_left_leg_render;
	static MeshRender *obese_male_bottom_right_hend_render;
	static MeshRender *obese_male_bottom_right_leg_render;
	static MeshRender *obese_male_head_render;
	static MeshRender *obese_male_top_left_hend_render;
	static MeshRender *obese_male_top_left_leg_render;
	static MeshRender *obese_male_top_right_hend_render;
	static MeshRender *obese_male_top_right_leg_render;

	static MeshRender *mm_body_render;
	static MeshRender *mm_bottom_left_hend_render;
	static MeshRender *mm_bottom_left_leg_render;
	static MeshRender *mm_bottom_right_hend_render;
	static MeshRender *mm_bottom_right_leg_render;
	static MeshRender *mm_head_render;
	static MeshRender *mm_top_left_hend_render;
	static MeshRender *mm_top_left_leg_render;
	static MeshRender *mm_top_right_hend_render;
	static MeshRender *mm_top_right_leg_render;

	static MeshRender *player_gun_render;
	static MeshRender *player_left_hend_render;
	static MeshRender *player_right_hend_render;

public:

	static MeshRender* getBox1(float scale)
	{
		if (!MeshFactory::box1_render) {
			MeshFactory::box1_render = new MeshRender(
				scale, "media/models/box", "box1.obj", "box1.mtl");
		}
		return MeshFactory::box1_render;
	};

	static MeshRender* getBullet(float scale, glm::vec4 collor)
	{
		if (!MeshFactory::bullet_render) {
			MeshFactory::bullet_render = new MeshRender(
				scale, "media/models/ball", "ball.obj", "ball.mtl");
		}
		return MeshFactory::bullet_render;
	};

	static MeshRender* getPanel1(float scale)
	{
		if (!MeshFactory::panel1_render) {
			MeshFactory::panel1_render = new MeshRender(
				scale, "media/models/panel1", "panel.obj", "panel.mtl");
		}
		return MeshFactory::panel1_render;
	};

	static MeshRender* getPlain(float scale)
	{
		if (!MeshFactory::plain_render) {
			MeshFactory::plain_render = new MeshRender(
				scale, "media/models/flore", "floor.obj", "floor.mtl");
		}
		return MeshFactory::plain_render;
	};

	static MeshRender* getCeiling(float scale)
	{
		if (!MeshFactory::ceiling_render) {
			MeshFactory::ceiling_render = new MeshRender(
				scale, "media/models/ceiling", "ceiling.obj", "ceiling.mtl");
		}
		return MeshFactory::ceiling_render;
	};


	/*
		Obese male
	*/
	static MeshRender* get_obese_male_body_render(float scale)
	{
		if (!MeshFactory::obese_male_body_render) {
			MeshFactory::obese_male_body_render = new MeshRender(
				scale, "media/models/ObeseMale/body", "body.obj", "body.mtl");
		}
		return MeshFactory::obese_male_body_render;
	};

	static MeshRender* get_obese_male_bottom_left_hend_render(float scale)
	{
		if (!MeshFactory::obese_male_bottom_left_hend_render) {
			MeshFactory::obese_male_bottom_left_hend_render = new MeshRender(
				scale, "media/models/ObeseMale/BottomLeftHend",	"BottomLeftHend.obj", "BottomLeftHend.mtl");
		}
		return MeshFactory::obese_male_bottom_left_hend_render;
	};

	static MeshRender* get_obese_male_bottom_left_leg_render(float scale)
	{
		if (!MeshFactory::obese_male_bottom_left_leg_render) {
			MeshFactory::obese_male_bottom_left_leg_render = new MeshRender(
				scale, "media/models/ObeseMale/BottomLeftLeg", "BottomLeftLeg.obj", "BottomLeftLeg.mtl");
		}
		return MeshFactory::obese_male_bottom_left_leg_render;
	};

	static MeshRender* get_obese_male_bottom_right_hend_render(float scale)
	{
		if (!MeshFactory::obese_male_bottom_right_hend_render) {
			MeshFactory::obese_male_bottom_right_hend_render = new MeshRender(
				scale, "media/models/ObeseMale/BottomRightHend", "BottomRightHend.obj",	"BottomRightHend.mtl");
		}
		return MeshFactory::obese_male_bottom_right_hend_render;
	};

	static MeshRender* get_obese_male_bottom_right_leg_render(float scale)
	{
		if (!MeshFactory::obese_male_bottom_right_leg_render) {
			MeshFactory::obese_male_bottom_right_leg_render = new MeshRender(
				scale, "media/models/ObeseMale/BottomRightLeg",	"BottomRightLeg.obj", "BottomRightLeg.mtl");
		}
		return MeshFactory::obese_male_bottom_right_leg_render;
	};

	static MeshRender* get_obese_male_head_render(float scale)
	{
		if (!MeshFactory::obese_male_head_render) {
			MeshFactory::obese_male_head_render = new MeshRender(
				scale, "media/models/ObeseMale/head", "head.obj", "head.mtl");
		}
		return MeshFactory::obese_male_head_render;
	};

	static MeshRender* get_obese_male_top_left_hend_render(float scale)
	{
		if (!MeshFactory::obese_male_top_left_hend_render) {
			MeshFactory::obese_male_top_left_hend_render = new MeshRender(
				scale, "media/models/ObeseMale/TopLeftHend", "TopLeftHend.obj", "TopLeftHend.mtl");
		}
		return MeshFactory::obese_male_top_left_hend_render;
	};

	static MeshRender* get_obese_male_top_left_leg_render(float scale)
	{
		if (!MeshFactory::obese_male_top_left_leg_render) {
			MeshFactory::obese_male_top_left_leg_render = new MeshRender(
				scale, "media/models/ObeseMale/TopLeftLeg", "TopLeftLeg.obj", "TopLeftLeg.mtl");
		}
		return MeshFactory::obese_male_top_left_leg_render;
	};

	static MeshRender* get_obese_male_top_right_hend_render(float scale)
	{
		if (!MeshFactory::obese_male_top_right_hend_render) {
			MeshFactory::obese_male_top_right_hend_render = new MeshRender(
				scale, "media/models/ObeseMale/TopRightHend", "TopRightHend.obj", "TopRightHend.mtl");
		}
		return MeshFactory::obese_male_top_right_hend_render;
	};

	static MeshRender* get_obese_male_top_right_leg_render(float scale)
	{
		if (!MeshFactory::obese_male_top_right_leg_render) {
			MeshFactory::obese_male_top_right_leg_render = new MeshRender(
				scale, "media/models/ObeseMale/TopRightLeg", "TopRightLeg.obj", "TopRightLeg.mtl");
		}
		return MeshFactory::obese_male_top_right_leg_render;
	};


	/*
		MM
	*/
	static MeshRender* get_mm_body_render(float scale)
	{
		if (!MeshFactory::mm_body_render) {
			MeshFactory::mm_body_render = new MeshRender(
				scale, "media/models/MM/body", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_body_render;
	};

	static MeshRender* get_mm_bottom_left_hend_render(float scale)
	{
		if (!MeshFactory::mm_bottom_left_hend_render) {
			MeshFactory::mm_bottom_left_hend_render = new MeshRender(
				scale, "media/models/MM/BottomLeftHend", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_bottom_left_hend_render;
	};

	static MeshRender* get_mm_bottom_left_leg_render(float scale)
	{
		if (!MeshFactory::mm_bottom_left_leg_render) {
			MeshFactory::mm_bottom_left_leg_render = new MeshRender(
				scale, "media/models/MM/BottomLeftLeg", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_bottom_left_leg_render;
	};

	static MeshRender* get_mm_bottom_right_hend_render(float scale)
	{
		if (!MeshFactory::mm_bottom_right_hend_render) {
			MeshFactory::mm_bottom_right_hend_render = new MeshRender(
				scale, "media/models/MM/BottomRightHend", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_bottom_right_hend_render;
	};

	static MeshRender* get_mm_bottom_right_leg_render(float scale)
	{
		if (!MeshFactory::mm_bottom_right_leg_render) {
			MeshFactory::mm_bottom_right_leg_render = new MeshRender(
				scale, "media/models/MM/BottomRightLeg", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_bottom_right_leg_render;
	};

	static MeshRender* get_mm_head_render(float scale)
	{
		if (!MeshFactory::mm_head_render) {
			MeshFactory::mm_head_render = new MeshRender(
				scale, "media/models/MM/head", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_head_render;
	};

	static MeshRender* get_mm_top_left_hend_render(float scale)
	{
		if (!MeshFactory::mm_top_left_hend_render) {
			MeshFactory::mm_top_left_hend_render = new MeshRender(
				scale, "media/models/MM/TopLeftHend", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_top_left_hend_render;
	};

	static MeshRender* get_mm_top_left_leg_render(float scale)
	{
		if (!MeshFactory::mm_top_left_leg_render) {
			MeshFactory::mm_top_left_leg_render = new MeshRender(
				scale, "media/models/MM/TopLeftLeg", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_top_left_leg_render;
	};

	static MeshRender* get_mm_top_right_hend_render(float scale)
	{
		if (!MeshFactory::mm_top_right_hend_render) {
			MeshFactory::mm_top_right_hend_render = new MeshRender(
				scale, "media/models/MM/TopRightHend", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_top_right_hend_render;
	};

	static MeshRender* get_mm_top_right_leg_render(float scale)
	{
		if (!MeshFactory::mm_top_right_leg_render) {
			MeshFactory::mm_top_right_leg_render = new MeshRender(
				scale, "media/models/MM/TopRightLeg", "mesh.obj", "mesh.mtl");
		}
		return MeshFactory::mm_top_right_leg_render;
	};

	/*
		Player
	*/
	static MeshRender* get_player_gun_render(float scale)
	{
		if (!MeshFactory::player_gun_render) {
			MeshFactory::player_gun_render = new MeshRender(
				scale, "media/models/Player/gun", "gun.obj", "gun.mtl");
		}
		return MeshFactory::player_gun_render;
	};

	static MeshRender* get_player_left_hend_render(float scale)
	{
		if (!MeshFactory::player_left_hend_render) {
			MeshFactory::player_left_hend_render = new MeshRender(
				scale, "media/models/Player/BottomLeftHend", "BottomLeftHend.obj", "BottomLeftHend.mtl");
		}
		return MeshFactory::player_left_hend_render;
	};

	static MeshRender* get_player_right_hend_render(float scale)
	{
		if (!MeshFactory::player_right_hend_render) {
			MeshFactory::player_right_hend_render = new MeshRender(
				scale, "media/models/Player/BottomRightHend", "BottomRightHend.obj", "BottomRightHend.mtl");
		}
		return MeshFactory::player_right_hend_render;
	};
};
#endif /* MESH_FACTORY_H_ */
