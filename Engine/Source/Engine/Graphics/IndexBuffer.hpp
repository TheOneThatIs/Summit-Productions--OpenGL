#pragma once


namespace toti {

	class IndexBuffer {
	private:
		unsigned int rendererID;
		unsigned int numIndicies;

	public:
		IndexBuffer(const unsigned int* data, unsigned int numIndicies);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline unsigned int getNumIndicies() const { return numIndicies; }
	};

}