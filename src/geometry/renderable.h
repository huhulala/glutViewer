#ifndef RENDERABLE_H_
#define RENDERABLE_H_

//! A geometry resource on the graphic card
class Renderable {
public:
	//! Constructor
	Renderable();

	//! Destructor
	virtual ~Renderable();

	virtual void drawGL() const;

};

#endif /* RENDERABLE_H_ */
