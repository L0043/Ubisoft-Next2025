#pragma once
#include <vector>
namespace Echo
{
    enum class MeshType
    {
        Rect,
		Circle,
        Triangle,
        Arrow
    };
	class Mesh
	{
	public:
        // this method will only work if all mesh's are created with 2 arguments, 
        // if I have time I would like to try improving this by creating a resourcesManager and loading all meshs, textures, etc from there
        // im not entirely sure what I should be calling these variables, for now they are arg1 and arg2
        Mesh(MeshType type, Vector2& position, Vector4& colour, float& rotation, float arg1, float arg2);
        Mesh(const Mesh& other);
        //Mesh& operator=(const Mesh& other);
        void operator=(const Mesh& other) 
        {
            m_Type = other.m_Type;
            m_Colour = other.m_Colour;
            m_Arg1 = other.m_Arg1;
            m_Arg2 = other.m_Arg2;
            m_Vertices = other.m_Vertices;
            m_Position = other.m_Position;
        };
		~Mesh();
        void CreateRect(float width, float height);
        void CreateCircle(float radius, int segments);
        void CreateTriangle(float width, float height);
        void CreateArrow(float arg1, float arg2);
        void SetPosition(Vector2& position) { m_Position = position; }
        void SetRotation(float& rot) { m_Rotation = rot; }
        void SetColour(Vector4& colour) { m_Colour = colour; }
        void Draw();
        void UpdateMesh(float arg1, float arg2);
        MeshType GetType() const { return m_Type; };
        std::vector<Vector2> GetVertices() const { return m_Vertices; };
        float GetArg1() const { return m_Arg1; };
        float GetArg2() const { return m_Arg2; };
	private:
        std::vector<Vector2> m_Vertices;
        MeshType m_Type;
        float m_Arg1;
        float m_Arg2;
        // storing a reference to the position of the object that the mesh is attached to
        // this is so that the mesh can be drawn in the correct position with ease
        Vector2& m_Position;
        // the same with colour
        Vector4& m_Colour;
        // and rotation
        float& m_Rotation;
	};
}