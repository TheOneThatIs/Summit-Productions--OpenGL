#pragma once
#include<string>



namespace toti {
	class Texture {
		unsigned int rendererID;
		std::string filepath;
		unsigned char* localBuffer;
		int width, height, bitsPerPixel;

	public:
		Texture(const std::string& path);
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
	};
}