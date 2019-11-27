#pragma once

#include <string>

namespace trace {


    struct Material {

		/// Name of material
		std::string name;
		
		/// Diffuse reflection
		float diffuse[4];			
		
		/// Ambient reflection
		float ambient[4];
		
		/// Specular reflection
		float specular[4];		
		
		/// Specular exponent
		float shininess;			

        // index of refraction
        float ior = 1.0f;

        float illum;

    };





}