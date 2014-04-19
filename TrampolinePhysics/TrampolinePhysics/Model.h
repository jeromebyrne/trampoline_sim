#ifndef MODEL_H
#define MODEL_H

#define MAX_VERTICES 256

class Model
{
	Vector3 m_vertices[MAX_VERTICES];

protected:
	GLUquadricObj* m_obj;//used to draw shapes
	Vector3 m_position;
	int m_texture;

public:
	Model(float x = 0, float y = 0, float z = 0, float width = 10, float height = 10, float breadth = 10, int texture = 0);
	~Model(void);

	float m_width;
	float m_height;
	float m_breadth;

	inline Vector3 Position()
	{
		return m_position;
	}
	inline void SetPosition(Vector3 value)
	{
		m_position = value;
	}

	virtual void Draw();

	inline Vector3 * Vertices()
	{
		return &m_vertices[0];
	}
};

#endif
