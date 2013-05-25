#ifndef ENGINE_H_
#define ENGINE_H_

#include "../base/types/types.h"
#include "../viewport/glutmanager.h"
#include "../viewport/glutviewport.h"
#include "../viewport/glrenderviewport3D.h"
#include "../viewport/glrenderviewport2D.h"

#include <map>

BEGIN_PV_NAMESPACE

/**
 * @file
 *  Central Viewer API creation and management singleton.
 *
 * The engine object manages lifecycle of multiple viewports and provides methods
 * for scene creation.
 //!
 */
class Engine {

public:

	//!Get singleton instance
	static Engine& getInstance();

	/**
	 * Viewport API
	 */

	//! Creates a 3D viewport
	Int create3DViewport(String name,IVec2& position, IVec2& viewSize);

	//! Creates a 2D viewport
	Int create2DViewport(String name,IVec2& position, IVec2& viewSize);

	//! Returns viewport
	GLRenderViewport3D* viewport(String name);

	//! Returns viewport
	GLRenderViewport3D* viewport(Int id);

	//! Returns viewport
	GLRenderViewport3D* activeViewport();

	//! Returns viewport
	vector<GLRenderViewport3D*>::iterator viewports();

	//! Enables the gl main loop
	void startMainLoop();

	//! Captures a viewport screenshot
	Bool renderViewportCapture(int viewport);

protected:
private:

	//! the instance
	static Engine* instance;

	//! Private Constructor
	Engine();

	//! viewport counter
	UInt m_vpCnt;

	//! active viewport
	GLRenderViewport3D* m_activeViewport;

	//! 3d viewport id map
	map<UInt,GLRenderViewport3D*> m_3dviewportIdMap;

	//! 3d viewport name map
	map<String,GLRenderViewport3D*> m_3dviewportNameMap;

	//! 2d viewport id map
	map<UInt,GLRenderViewport2D*> m_2dviewportIdMap;

	//! 2d viewport name map
	map<String,GLRenderViewport2D*> m_2dviewportNameMap;

};

END_PV_NAMESPACE

#endif /* ENGINE_H_ */
