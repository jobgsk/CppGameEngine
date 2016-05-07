#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>

#include "AnimationFrame.h"

using namespace std;

class AnimationParser {
private:
	string _filename;
	float m_scale;
	Vector3 m_position;
	GameObject * m_owner;
public:
	AnimationParser(string filename, float scale, Vector3 pos, GameObject * owner) : 
		m_scale(scale), 
		m_position(pos),
		m_owner(owner)
	{
		_filename = filename;
	};

	std::vector<AnimationFrame*> load()
	{
		ifstream inFile;
		inFile.open(_filename, fstream::in);
		if (!inFile)
		{
			std::cout << "Cannot open map file!" << std::endl;
		}

		std::vector<AnimationFrame*> alist;

		std::string marker;
		std::string line;
		std::string marker1("animation"), marker2("bone"), marker3(" ");

		int bid, pid;
		std::string name;
		float len, px, py, pz, w, vx, vy, vz;
		while (std::getline(inFile, line)) 
		{
			std::istringstream iss(line);
			iss >> marker;

			if (marker.compare(marker3) == 0)
				continue;

			if (marker.compare(marker1) == 0) {
				iss >> bid;

				alist.push_back(new AnimationFrame(bid, m_owner));
				continue;
			}

			if (marker.compare(marker2) == 0) {
				iss >> bid >> name >> pid >> len >> px >> py >> pz >> w >> vx >> vy >> vz;
				if (alist.size() > 0)
				{
					//Quaternion q1 = Quaternion(w, Vector3(vx, vy, vz));
					//q1.rotateByVector(Vector3(0, tanks::grad_to_rad(90), 0));
					//q1.get_euler();

					alist[(alist.size() - 1)]->create_bone(
						bid, name, pid, len,
						px*m_scale + (float)m_position.x, 
						py*m_scale + (float)m_position.y, 
						pz*m_scale + (float)m_position.z,
						w, vx, vy, vz);
						//q1.alpha, q1.axis.x, q1.axis.y, q1.axis.z);
				}
					
				continue;
			}
		}
		inFile.close();
		return alist;
	};
};