#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNor;
out vec3 lightIntensity;

struct Light {
	vec4 position;
	vec3 color;
}

struct Material {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float shininess;
}

uniform mat4 mvp;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform Material material;
uniform Light light;

void phongModel(vec4 pos, vec3 norm) {
	vec3 s = normalize(vec3(light.position - pos));
	vec3 v = normalize(-pos.xyz);
	vec3 r = reflect(-s, norm);

	float sn = max(dot(s,norm), 0.0);
	vec3 ambient = light.color * material.Ka;
	vec3 diffuse = sn * light.color * material.Kd;
	vec3 specular = vec3(0);

	float f = pow(max(dot(r,v),0.0), material.shininess);
	if (sn > 0) specular = light.color * material.Ks * f;

	return ambient + diffuse + specular;
}

void main()
{
	vec4 pos = modelViewMatrix * vec4(vPos, 1.0);
	vec3 norm = normalize(normalMatrix * vNor);
	lightIntensity = phongModel(pos, norm);
    gl_Position = mvp * vec4(vPos, 1.0);
}


