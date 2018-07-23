#include"Texture.hpp"
#include"Engine\Util\HelperFuntions.hpp"
#include"Engine\Vendor\STB Image\STB_Image.h"


namespace toti {
	Texture::Texture(const std::string& path) : rendererID(0), filepath(path), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0) {
		stbi_set_flip_vertically_on_load(1); // OpenGL expects to read the textures from the bottom-right rather than the top-left like pngs are saved, so we have to flip the image backwards.
		localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4); // This function reads the texture and sets width, height and bitsPerPixel accordingly

		callGL(glGenTextures(1, &rendererID));
		callGL(glBindTexture(GL_TEXTURE_2D, rendererID));

		callGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // Linear filter
		callGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		callGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		callGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		callGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
		callGL(glBindTexture(GL_TEXTURE_2D, 0));

		if (localBuffer)
			stbi_image_free(localBuffer);
	}

	Texture::~Texture(){
		callGL(glDeleteTextures(1, &rendererID));
	}




	void Texture::bind(unsigned int slot) const {
		callGL(glActiveTexture(GL_TEXTURE0 + slot))
		callGL(glBindTexture(GL_TEXTURE_2D, rendererID));
	}
	void Texture::unbind() const {
		callGL(glBindTexture(GL_TEXTURE_2D, 0));
	}
}