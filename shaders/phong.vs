#version 400

layout (location = 0) in vec3 VPos;
layout (location = 1) in vec3 VNor;
out vec3 LightIntensity;

struct Lights {
   vec4 Position; 
   vec3 color;
};


struct Materials {
   vec3 Ka; 
   vec3 Kd; 
   vec3 Ks; 
   float shininess; 
};

uniform Lights Light;
uniform Materials Material;
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
   vec3 norm = normalize( NormalMatrix * VNor);
   vec4 eye = ModelViewMatrix * vec4(VPos,1.0);

   vec3 s = normalize(vec3(Light.Position - eye));
   vec3 v = normalize(-eye.xyz);
   vec3 r = reflect (-s, norm);

   vec3 ambient = Light.color * Material.Ka;
   float sN = max( dot(s,norm), 0.0 );
   vec3 diffuse = Light.color * Material.Kd * sN;
   vec3 specular = vec3(0.0);

   if( sN > 0.0 ) 
		specular = Light.color * Material.Ks * pow( max( dot(r,v), 0.0 ), Material.shininess );
   LightIntensity = ambient + diffuse + specular;

   gl_Position = MVP * vec4(VPos,1.0);
}