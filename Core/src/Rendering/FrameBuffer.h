#pragma once


class FrameBuffer
{
private:
	unsigned int id;
	unsigned int textureId;

	int width, height;
public:
	FrameBuffer(int width, int height);
	~FrameBuffer();

	void bind();
	void unbind();


	void update(int width, int height);

	int getWidth() { return width; }
	int getHeight() { return height; }

	unsigned int getTextureId() { return textureId; }
	unsigned int getId() { return id; }
};

