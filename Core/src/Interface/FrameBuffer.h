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

	void Bind();
	void Unbind();


	void Update(int width, int height);

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	unsigned int GetTextureId() const { return textureId; }
	unsigned int GetId() const { return id; }
};

