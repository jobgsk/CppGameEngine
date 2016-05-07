#version 430 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 normalVector;
layout(location = 2) in vec2 vTexCoord;

layout(location = 3) in vec4 vertexColor;
layout(location = 4) in vec4 ambientCollor;

uniform mat4 model_matrix;
uniform mat4 camera_matrix;
uniform mat4 projection_matrix;

out vec4 myColor;
out vec2 texCoord;
out vec4 ambientLight;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct; 
uniform vec4 LightPosition;
uniform float Shininess;


uniform float is_color;
out float isFragColor;

void main()
{	
	vec4 v = vec4(vPosition, 1.0);
	gl_Position = projection_matrix * camera_matrix * model_matrix * v;
	//gl_Position = model_matrix * v;
	texCoord = vTexCoord;

	// Transform vertex  position into eye coordinates
    vec3 pos = (model_matrix * v).xyz;
	
    vec3 L = normalize( (model_matrix * LightPosition).xyz - pos );
    vec3 E = normalize( -pos );
    vec3 H = normalize( L + E );

    // Transform vertex normal into eye coordinates
    vec3 N = normalize( model_matrix * vec4(normalVector, 0.0) ).xyz;

    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct;

    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks * SpecularProduct;
    
    if( dot(L, N) < 0.0 ) {
		specular = vec4(0.0, 0.0, 0.0, 1.0);
    } 


	myColor = ambient + diffuse + specular;
    myColor.a = 1.0;

	//ambientLight = ambientCollor;
	//myColor = vertexColor;

	//isFragColor = is_color;
}
