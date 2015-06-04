#ifndef _MODEL_H
#define _MODEL_H



#define MODEL_TYPE_V 0
#define MODEL_TYPE_VT 1
#define MODEL_TYPE_VTN 2

typedef struct tagVERTEX {
	float x, y, z;
} VERTEX;

typedef struct tagUV {
	float u, v;
} UV;

typedef struct tagNormal {
	float x, y, z;
} NORMAL;

typedef struct tagTRIANGLE {
	VERTEX vertex[3];
	UV uv[3];
	NORMAL normal[3];
} TRIANGLE;

class Model : public Object
{
public:
	Model();
	Model(const char*, int = MODEL_TYPE_VTN, bool compCollision = true);
	~Model();

	int GetModelType() const { return modelType; }
	void SetModelType(int);

	bool generateBoundingBox();
	virtual void draw();
	void drawNoTextures();
	void drawBoundingBox();

	Model* morph(Model*, float);
	void copyAllAttributes(Model*);

	std::vector <float> vertices;
	std::vector <float> uvs;
	std::vector <float> normals;

private:
	bool loadObj(const char*);
	void setupVAO();
	void setupVBO();

	void readLine(FILE *, char *);

	//std::vector <GLuint> indices;

	int modelType;
	bool isLoaded;

	cbmini::cbfw::VertexBuffer* vbo;

	std::vector <float> tempVertices;
	std::vector <float> tempUVs;
	std::vector <float> tempNormals;

	std::vector <float> tempIndices;
};

#endif
