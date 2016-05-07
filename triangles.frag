#version 430 core

in vec4 myColor;
in vec2 texCoord;
//in vec4 ambientLight;

out vec4 fColor;
//in float isFragColor;

uniform sampler2D texture;

void main()
{

	//if (isFragColor == 1)
	//	fColor = myColor;
	//else
	//fColor = texture2D(texture, texCoord);

	fColor = texture2D(texture, texCoord) * myColor;

	//fColor = texture2D(texture, texCoord) * ambientLight;
	//fColor = myColor;
	//fColor = ambientLight * myColor;
	//fColor = texture2D(texture, texCoord) * myColor * ambientLight;

}