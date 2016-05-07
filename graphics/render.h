#ifndef RENDER_H_
#define RENDER_H_

#include <iostream>
#include "Graphics.h"
#include "StaticModelLoader.h"

class Render {
protected:

public:

	GLuint vertices_coord_buffer;
	GLuint texture_coord_buffer;
	GLuint normals_coord_buffer;
	GLuint color_buffer;

	//int vertices_coord_buffer;
	//int normals_coord_buffer;
	//int texture_coord_buffer;

	//GLuint Buffers[3];
	//GLuint * Buffers;

	GLuint * TextureBuffer;
	
	//unsigned int *indexes;
	GLfloat *vertices;
	GLfloat *normalVectorData;
	GLfloat *textureCoordinates;
	GLfloat *colorData;

	int f_num;
	//radius	
	float rx;
	float ry;
	float rz; 

	Render()
	{
		//Buffers = new GLuint[3];
		//glGenBuffers(3, Buffers);
	};

	virtual void render(glm::mat4 mat) = 0;

	/*
		geometry buffer
	*/
	void VertexBuferCreate()
	{
		glGenBuffers(1, &vertices_coord_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertices_coord_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * f_num, vertices, GL_STATIC_DRAW);
		glBindAttribLocation(Graphics::program, 0, "vPosition");
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
	};

	void VertexBuferActivate()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertices_coord_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
	}

	/*
	normals buffer
	*/
	void NormalsBuferCreate()
	{
		glGenBuffers(1, &normals_coord_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, normals_coord_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * f_num, normalVectorData, GL_STATIC_DRAW);
		glBindAttribLocation(Graphics::program, 1, "normalVector");
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(1);
	};

	void NormalsBuferActivate()
	{
		glBindBuffer(GL_ARRAY_BUFFER, normals_coord_buffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(1);
	}

	/*
		texture buffer
	*/
	void TextureBuferCreate()
	{
		glGenBuffers(1, &texture_coord_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, texture_coord_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * f_num, textureCoordinates, GL_STATIC_DRAW);
		glBindAttribLocation(Graphics::program, 2, "vTexCoord");
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(2);
	};

	void TextureBuferActivate()
	{
		glBindBuffer(GL_ARRAY_BUFFER, texture_coord_buffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(2);
	}

	/*
		color buffer
	*/
	void ColorBuferCreate()
	{
		glGenBuffers(1, &color_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * f_num, colorData, GL_STATIC_DRAW);
		glBindAttribLocation(Graphics::program, 3, "vertexColor");
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(3);
	};

	void ColorBuferActivate()
	{
		glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(3);
	}

	/*
		textures data
	*/
	virtual void TextureLoad() {};
	virtual void test() {};
};


class MeshRender : public Render {
public:
	ModernModelsStruct *m_mesh;
	std::string f_path;

	MeshRender(float scale, std::string fpath, std::string o, std::string m) : Render(),
		f_path(fpath)
	{
		
		//StaticModelLoader* loader = new StaticModelLoader("media/models/1/box1.obj", "media/models/1/box1.mtl");
		std::string fobj = fpath + "/" + o;
		std::string fmtl = fpath + "/" + m;
		StaticModelLoader* loader = new StaticModelLoader(fobj.c_str(), fmtl.c_str());
		m_mesh = ModernCopyModel(loader, scale);
		
		vertices = m_mesh->v_array;
		textureCoordinates = m_mesh->vt_array;
		normalVectorData = m_mesh->vn_array;
		f_num = m_mesh->f_num;

		rx = m_mesh->rx;
		ry = m_mesh->ry;
		rz = m_mesh->rz;

		TextureLoad();

		VertexBuferCreate();
		NormalsBuferCreate();
		TextureBuferCreate();
	}

	void render(glm::mat4 mat)
	{
		//glm::mat4 model_view = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
		//glUniformMatrix4fv(Graphics::location1, 1, GL_FALSE, &model_view[0][0]);

		glUniformMatrix4fv(Graphics::location1, 1, GL_FALSE, &mat[0][0]);

		VertexBuferActivate();
		NormalsBuferActivate();
		TextureBuferActivate();
		
		for (int i = 0; i < m_mesh->m_num; i++)
		{
			//std::cout << " text index " 
			//	<< vertices_coord_buffer
			//	<< " " << m_mesh->m_array[i].start_geometry_index
			//	<< " " << m_mesh->m_array[i].end_geometry_index
			//	<< std::endl;

			glBindTexture(GL_TEXTURE_2D, TextureBuffer[i]);
			//glDrawArrays(GL_TRIANGLES, 0, v_num);
			glDrawArrays(GL_TRIANGLES, m_mesh->m_array[i].start_geometry_index, m_mesh->m_array[i].end_geometry_index);
		}
		//glBindBuffer(GL_ARRAY_BUFFER, 0); // reset
	};

	/*
		textures data
	*/
	void TextureLoad()
	{
		TextureBuffer = new GLuint[m_mesh->m_num];
		//texture_num = m_mesh->m_num;
		glGenTextures(m_mesh->m_num, TextureBuffer);

		AUX_RGBImageRec *TextureImage[1]; // Create Storage Space For The Texture

		for (int i = 0; i < m_mesh->m_num; i++)
		{
			// Set The Pointer To NULL
			memset(TextureImage, 0, sizeof(void *) * 1);

			std::string ftext = f_path + "/" + m_mesh->m_array[i].map_kd;
			// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
			if (TextureImage[0] = LoadBMP(ftext.c_str()))
			{
				// Typical Texture Generation Using Data From The Bitmap
				glBindTexture(GL_TEXTURE_2D, TextureBuffer[i]);


				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
					TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

				// Specify filtering and edge actions
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


				if (TextureImage[0]->data)			// If Texture Image Exists
					free(TextureImage[0]->data);	// Free The Texture Image Memory
				free(TextureImage[0]);				// Free The Image Structure
			}
			else
			{
				std::cout << " bmp error " << std::endl;
			}
		}
	};

	void test()
	{
		int fn = 0;
		for (; fn < m_mesh->f_num; fn++)
		{
			std::cout << fn <<
				" v " << m_mesh->v_array[(fn * 3) + 0] <<
				" " << m_mesh->v_array[(fn * 3) + 1] <<
				" " << m_mesh->v_array[(fn * 3) + 2] <<

				" vt " << m_mesh->vt_array[(fn * 2) + 0] <<
				" " << m_mesh->vt_array[(fn * 2) + 1] <<

				" vn " << m_mesh->vn_array[(fn * 3) + 0] <<
				" " << m_mesh->vn_array[(fn * 3) + 1] <<
				" " << m_mesh->vn_array[(fn * 3) + 2]
				<< std::endl;
		}
		std::cout << " f_num " << m_mesh->f_num << " iv " << fn << std::endl;
	}
};

class CollorRender : public Render {
public:
	ModernModelsStruct *m_mesh;
	std::string f_path;

	CollorRender(float scale, std::string fpath, std::string o, std::string m, glm::vec4 color) : Render(),
		f_path(fpath)
	{

		//StaticModelLoader* loader = new StaticModelLoader("media/models/1/box1.obj", "media/models/1/box1.mtl");
		std::string fobj = fpath + "/" + o;
		std::string fmtl = fpath + "/" + m;
		StaticModelLoader* loader = new StaticModelLoader(fobj.c_str(), fmtl.c_str());
		m_mesh = ModernCopyModel(loader, scale, color);

		vertices = m_mesh->v_array;
		colorData = m_mesh->c_array;

		f_num = m_mesh->f_num;

		rx = m_mesh->rx;
		ry = m_mesh->ry;
		rz = m_mesh->rz;

		VertexBuferCreate();
		ColorBuferCreate();
	}

	virtual void render(glm::mat4 mat)
	{
		//glm::mat4 model_view = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
		//glUniformMatrix4fv(Graphics::location1, 1, GL_FALSE, &model_view[0][0]);

		glUniformMatrix4fv(Graphics::location1, 1, GL_FALSE, &mat[0][0]);
		glUniform1f(Graphics::location4, 1);

		VertexBuferActivate();
		ColorBuferActivate();
		glDrawArrays(GL_TRIANGLES, 0, f_num);

		glUniform1f(Graphics::location4, 0);
	};
};

#endif /* RENDER_H_ */