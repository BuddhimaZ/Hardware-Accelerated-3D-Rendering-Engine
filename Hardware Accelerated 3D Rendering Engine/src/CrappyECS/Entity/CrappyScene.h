#ifndef CRAPPYSCENE_H
#define CRAPPYSCENE_H

//Local Includes
#include "CrappyEntity.h"

class CrappyScene : public CrappyEntity {
public:
	CrappyScene();
	const void SetRenderer(const Renderer* pRenderer);

	void OnSceneStart() const;
	void OnSceneUpdate(const float& dt) const;

};

#endif // !CRAPPYSCENE_H
