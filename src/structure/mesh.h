#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include "../base/math/vec3.h"

//! A geometry resource on memory.
class Mesh{
public:

	//! Constructor
	Mesh();

	//! Destructor
	~Mesh();


private:

	//! The point vector
	std::vector<FVec3> m_points;

	//! The normals vector
	std::vector<FVec3> m_normals;

	//! The id
	std::vector<IDVec3> m_ids;

};

#endif /* MESH_H_ */
